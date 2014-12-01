#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cstring>
#include <cassert>

#include "body.h"
#include "kernel.h"
#include "universe.h"

void		init_map_and_pairs(int nb, Map & map, std::vector<Pair> & pairs)
{
	int k = 0;
	
	map.alloc(nb);

	pairs.resize(nb * (nb - 1) / 2);

	for(int i = 0; i < nb; i++)
	{
		for(int j = i + 1; j < nb; j++)
		{
			
			pairs[k].b0 = i;
			pairs[k].b1 = j;
			
			map.pair_[i * nb + j] = k;
			map.pair_[j * nb + i] = k;

			k++;
		}
	}
}

Universe::Universe(): pairs_(0), first_step_(0)
{
}
Body*		Universe::b(int t)
{
	assert(frames_.size() > t);
	return frames_[t].b(0); // &_M_bodies[0] + (t * num_bodies_);
}
Body*		Universe::b(int t, int i)
{
	assert(frames_.size() > t);
	return frames_[t].b(i); //&_M_bodies[0] + (t * num_bodies_ + i);
}
void		Universe::alloc(int num_bodies, int num_steps)
{
	num_bodies_ = num_bodies;
	num_steps_ = num_steps;
	num_pairs_ = (num_bodies * (num_bodies - 1)) / 2;

	/* Allocate bodies */
	add_frame(num_bodies);

	//bodies_.resize(num_bodies_ * num_steps_);

	/* Allocate and initialize map and pairs */
	init_map_and_pairs(num_bodies, map_, pairs_);

}
unsigned int	count_alive(Body * b, int n)
{
	int na = 0;
	for(int i = 0; i < n; i++)
	{
		if(b[i].alive) na++;
	}
	return na;
}
unsigned int	Universe::count_alive(int t)
{
	int n = 0;
	for(int i = 0; i < num_bodies_; i++)
	{
		if(b(t,i)->alive) n++;
	}
	return n;
}
int		Universe::solve()
{
	// temp bodies
	Body* bodies = new Body[num_bodies_];
	memcpy(bodies, b(0), num_bodies_ * sizeof(Body));

	

	unsigned int flag_multi_coll = 0;
	float dt = 100.0;

	int total_coll = num_bodies_ - count_alive(0);

	unsigned int nc = 0;
	
	for(int t = 1; t < num_steps_; t++)
	{
		if((t % (num_steps_ / 100)) == 0)
		{
			printf("t = %6i nb = %6i\n", t, num_bodies_ - total_coll);
		}

		/* Execute "step_pairs" kernel */
		step_pairs(bodies, &pairs_[0]);

		/* Execute "step_bodies" kernel */
		step_bodies(bodies, &pairs_[0], &map_, dt);

		/* Execute "step_collisions" kernel */
		step_collisions(bodies, &pairs_[0], &flag_multi_coll, &nc);

		/* Execute "clear_bodies_num_collisions" kernel */
		clear_bodies_num_collisions(bodies);

		if(flag_multi_coll)
		{
			puts("resolve multi_coll");

			/* Execute "step_collisions" kernel on a single thread to resolve bodies with multiple collisions */
			step_collisions(bodies, &pairs_[0], &flag_multi_coll, &nc);
		}
		
		total_coll += (nc/2);
		nc = 0;
		
		/* Reset flag_multi_coll */
		flag_multi_coll = 0;

		if(count_alive(t) != (num_bodies_ - total_coll))
		{
			printf("%i %i\n", count_alive(t), (num_bodies_ - total_coll));
			exit(1);
		}
	

		/* Store data for timestep */
		//frames_.emplace_back();
		add_frame(num_bodies_);
		memcpy(b(t), bodies, num_bodies_ * sizeof(Body));

		if(count_alive(t) != (num_bodies_ - total_coll))
		{
			printf("%i %i\n", count_alive(t), (num_bodies_ - total_coll));
			exit(1);
		}
	}
}
void	Universe::add_frame(unsigned int n)
{
	frames_.emplace_back();
	frames_.back().alloc(n);
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

	fwrite(b(0), sizeof(Body), num_steps_ * num_bodies_, pfile_);

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
			fread(b(i), sizeof(Body), num_bodies_, pfile_);
		}

		// copy last to first
		memcpy(b(0), bodies + (num_steps_old - 1) * num_bodies_, num_bodies_ * sizeof(Body));

		delete[] bodies;
	}
	else
	{
		num_steps_ = num_steps_old;

		alloc(num_bodies_, num_steps_);

		for(int i = 0; i < num_steps_old; i++)
		{
			if((i % (num_steps_old / 10)) == 0) printf("t = %i\n", i);
			fread(b(i), sizeof(Body), num_bodies_, pfile_);
		}
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

	for(Body * pb = b(0); pb < (b(0) + num_bodies_); pb++)
	{
		pb->x[0] = (float)(rand() % w) - (float)w * 0.5;
		pb->x[1] = (float)(rand() % w) - (float)w * 0.5;
		pb->x[2] = (float)(rand() % w) - (float)w * 0.5;

		pb->v[0] = 0;
		pb->v[1] = 0;
		pb->v[2] = 0;

		pb->mass = m;
		pb->radius = radius(pb->mass);
	}
}
void		Universe::spin(float m)
{
	// give bodies xz velocity orbiting mass_center

	int w = 1000;

	// universe mass
	float umass = num_bodies_ * m;

	for(Body * pb = b(0); pb < (b(0) + num_bodies_); pb++)
	{
		pb->x[0] = (float)(rand() % w) - (float)w * 0.5;
		pb->x[1] = (float)(rand() % w) - (float)w * 0.5;
		pb->x[2] = (float)(rand() % w) - (float)w * 0.5;

		float r = sqrt(pb->x[0] * pb->x[0] + pb->x[1] * pb->x[1] + pb->x[2] * pb->x[2]);

		float rxz = sqrt(pb->x[0] * pb->x[0] + pb->x[2] * pb->x[2]);

		float v = sqrt(6.67384E-11 * umass / r) * 0.5;

		pb->v[0] = -pb->x[2] / rxz * v;
		pb->v[1] = 0;
		pb->v[2] = pb->x[0] / rxz * v;

		pb->mass = m;
		pb->radius = radius(pb->mass);
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





