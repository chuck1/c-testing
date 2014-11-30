#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cstring>
#include <cassert>

#include "body.h"
#include "kernel.h"
#include "universe.h"

Universe::Universe(): bodies_(0), pairs_(0), first_step_(0)
{
}
Body*		Universe::b(int t)
{
	return &bodies_[0] + (t * num_bodies_);
}
Body*		Universe::b(int t, int i)
{
	return &bodies_[0] + (t * num_bodies_ + i);
}
void		Universe::alloc(int num_bodies, int num_steps)
{
	num_bodies_ = num_bodies;
	num_steps_ = num_steps;
	num_pairs_ = (num_bodies * (num_bodies - 1)) / 2;

	/* Allocate bodies */
	//bodies_ = new Body[sizeof(Body) * num_bodies_ * num_steps_];
	bodies_.resize(num_bodies_ * num_steps_);

	pairs_ = new Pair[sizeof(Pair) * num_pairs_];

	// pair index
	int k = 0;

	for(int i = 0; i < num_bodies_; i++)
	{
		bodies_[i].alive = 1;
		bodies_[i].num_collisions = 0;
	}
	for(int i = 0; i < num_pairs_; i++)
	{
		pairs_[i].alive = 1;
		pairs_[i].collision = 0;
	}


	for(int i = 0; i < num_bodies; i++)
	{
		for(int j = i + 1; j < num_bodies; j++)
		{
			Pair * pp = pairs_ + k;
			pp->b0 = i;
			pp->b1 = j;

			map_.pair[i * NUM_BODIES + j] = k;
			map_.pair[j * NUM_BODIES + i] = k;

			k++;
		}
	}
}

int		Universe::solve()
{
	Body* bodies = new Body[num_bodies_];
	memcpy(bodies, &bodies_[0], num_bodies_ * sizeof(Body));

	assert(pairs_);
	//assert(bodies_);

	unsigned int flag_multi_coll = 0;
	float dt = 100.0;

	for(int t = 1; t < num_steps_; t++)
	{
		if((t % (num_steps_ / 100)) == 0)
		{
			printf("t = %5i\n", t);
		}

		/* Execute "step_pairs" kernel */

		//ret = clEnqueueNDRangeKernel(command_queue, kernel_pairs, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
		step_pairs(bodies, pairs_);

		/* Execute "step_bodies" kernel */
		step_bodies(bodies, pairs_, &map_, dt);

		/* Execute "step_collisions" kernel */
		step_collisions(bodies, pairs_, &flag_multi_coll);

		/* Execute "clear_bodies_num_collisions" kernel */
		clear_bodies_num_collisions(bodies);

		if(flag_multi_coll)
		{
			puts("resolve multi_coll");

			/* Execute "step_collisions" kernel on a single thread to resolve bodies with multiple collisions */
			step_collisions(bodies, pairs_, &flag_multi_coll);
		}

		/* Reset flag_multi_coll */
		flag_multi_coll = 0;

		/* Store data for timestep */
		memcpy(b(t), bodies, num_bodies_ * sizeof(Body));
	}
}
void	Universe::rw_header()
{
	operator&(num_bodies_);
	operator&(num_steps_);
	operator&(first_step_);
}
void	Universe::write()
{
	char buffer[8];
	sprintf(buffer, "%i", num_steps_ + first_step_);

	char fileName[64];
	strcpy(fileName, "data_");
	strcat(fileName, name_);
	strcat(fileName, "_");
	strcat(fileName, buffer);
	strcat(fileName, ".dat");

	pfile_ = fopen(fileName, "w");
	if(pfile_ == 0)
	{
		perror("fopen");
		exit(1);
	}
	filemode_ = FILEMODE_WRITE;

	rw_header();

	fwrite(&name_, 32, 1, pfile_);

	fwrite(&bodies_[0], sizeof(Body), num_steps_ * num_bodies_, pfile_);

	fclose(pfile_);
	pfile_ = 0;
}
void	Universe::operator&(int i)
{
	assert(pfile_);
	if(filemode_ == FILEMODE_WRITE)
	{
		fwrite(&i, sizeof(int), 1, pfile_);
	}
	else if(filemode_ == FILEMODE_READ)
	{
		fread(&i, sizeof(int), 1, pfile_);
	}
	else
	{
		assert(0);
	}

}
int	Universe::read(std::string fileName, int num_steps)
{
	pfile_ = fopen(fileName.c_str(), "r");
	if(!pfile_) return 1;

	filemode_ = FILEMODE_READ;

	int num_steps_old;

	fread(&num_bodies_, sizeof(int), 1, pfile_);
	fread(&num_steps_old, sizeof(int), 1, pfile_);
	fread(&first_step_, sizeof(int), 1, pfile_);

	//rw_header();

	fread(&name_, 32, 1, pfile_);

	printf("name = %s\n", name_);

	if(num_steps > 0)
	{
		num_steps_ = num_steps;

		alloc(num_bodies_, num_steps_);

		first_step_ += num_steps_;

		// temporary array
		Body * bodies = new Body[num_bodies_ * num_steps_old * sizeof(Body)];

		printf("read %s\n", fileName.c_str());
		for(int i = 0; i < num_steps_old; i++)
		{
			if((i % (num_steps_old / 10)) == 0) printf("t = %i\n", i);
			fread(bodies + i * num_bodies_, sizeof(Body), num_bodies_, pfile_);
		}

		// copy last to first
		memcpy(&bodies_[0], bodies + (num_steps_old - 1) * num_bodies_, num_bodies_ * sizeof(Body));

		delete[] bodies;
	}
	else
	{
		num_steps_ = num_steps_old;

		alloc(num_bodies_, num_steps_);

		fread(&bodies_[0], sizeof(Body), num_steps_old * num_bodies_, pfile_);
	}

	fclose(pfile_);
	pfile_ = 0;
	return 0;
}
int		Universe::mass_center(int t, float * x, float * s)
{
	
	float temp[3] = {0,0,0};
	
	float m = 0;

	for(int i = 0; i < num_bodies_; i++)
	{
		Body * pb = b(t,i);

		temp[0] += pb->x[0] * pb->mass;
		temp[1] += pb->x[1] * pb->mass;
		temp[2] += pb->x[2] * pb->mass;

		m += pb->mass;
	}

	temp[0] /= m;
	temp[1] /= m;
	temp[2] /= m;

	if(x)
	{
		x[0] = temp[0];
		x[1] = temp[1];
		x[2] = temp[2];
	}

	// weighted std

	if(s)
	{
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;

		for(int i = 0; i < num_bodies_; i++)
		{
			Body * pb = b(t,i);

			temp[0] += pb->mass * pow(pb->x[0] - x[0], 2);
			temp[1] += pb->mass * pow(pb->x[1] - x[1], 2);
			temp[2] += pb->mass * pow(pb->x[2] - x[2], 2);
		}

		s[0] = sqrt(temp[0] / m);
		s[1] = sqrt(temp[1] / m);
		s[2] = sqrt(temp[2] / m);
	}
}
void		Universe::random(float m)
{
	int w = 1000;

	for(Body * b = &bodies_[0]; b < (&bodies_[0] + num_bodies_); b++)
	{
		b->x[0] = (float)(rand() % w) - (float)w * 0.5;
		b->x[1] = (float)(rand() % w) - (float)w * 0.5;
		b->x[2] = (float)(rand() % w) - (float)w * 0.5;

		b->v[0] = 0;
		b->v[1] = 0;
		b->v[2] = 0;

		b->mass = m;
		b->radius = radius(b->mass);
	}
}
void		Universe::spin(float m)
{
	// give bodies xz velocity orbiting mass_center

	int w = 1000;

	// universe mass
	float umass = num_bodies_ * m;

	for(Body * b = &bodies_[0]; b < (&bodies_[0] + num_bodies_); b++)
	{
		b->x[0] = (float)(rand() % w) - (float)w * 0.5;
		b->x[1] = (float)(rand() % w) - (float)w * 0.5;
		b->x[2] = (float)(rand() % w) - (float)w * 0.5;

		float r = sqrt(b->x[0] * b->x[0] + b->x[1] * b->x[1] + b->x[2] * b->x[2]);

		float rxz = sqrt(b->x[0] * b->x[0] + b->x[2] * b->x[2]);

		float v = sqrt(6.67384E-11 * umass / r) * 0.5;

		b->v[0] = -b->x[2] / rxz * v;
		b->v[1] = 0;
		b->v[2] = b->x[0] / rxz * v;

		b->mass = m;
		b->radius = radius(b->mass);
	}
}
void		Universe::stats()
{
	mass_center_.resize(num_steps_);

	for(int t = 0; t < num_steps_; t++)
	{
		mass_center(t, &mass_center_[t].x, (float*)0);
	}
}





