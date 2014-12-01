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
	assert(frames_.frames_.size() > t);
	return frames_.frames_[t].b(0); // &_M_bodies[0] + (t * num_bodies_);
}
Body*		Universe::b(int t, int i)
{
	assert(frames_.frames_.size() > t);
	return frames_.frames_[t].b(i); //&_M_bodies[0] + (t * num_bodies_ + i);
}
void		Universe::alloc(int num_bodies, int num_steps)
{
	//num_bodies_ = num_bodies;
	num_steps_ = num_steps;
	//num_pairs_ = (num_bodies * (num_bodies - 1)) / 2;

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
		if(b[i].alive == 1) na++;
	}
	return na;
}
unsigned int	count_dead(Body * b, int n)
{
	int na = 0;
	for(int i = 0; i < n; i++)
	{
		if(b[i].alive == 0) na++;
	}
	return na;
}
unsigned int	Universe::count_alive(int t)
{
	assert(frames_.frames_.size() > t);
	return frames_.frames_[t].count_alive();
}
Frame &		Universe::get_frame(int t)
{
	assert(frames_.frames_.size() > t);
	return frames_.frames_[t];
}
unsigned int	Universe::count_dead(int t)
{
	assert(frames_.frames_.size() > t);
	return frames_.frames_[t].count_dead();
}
int		Universe::solve()
{
	// temp bodies
	
	//Body* bodies = new Body[num_bodies_];
	//memcpy(bodies, b(0), num_bodies_ * sizeof(Body));
	
	Frame f = get_frame(0);
	
	
	unsigned int flag_multi_coll = 0;
	float dt = 100.0;

	int total_coll = size(0) - count_alive(0);

	unsigned int nc = 0;
	
	for(int t = 1; t < num_steps_; t++)
	{
		if((t % (num_steps_ / 10)) == 0)
		{
			printf("t = %6i nb = %6i\n", t, size(0) - total_coll);
		}

		/* Execute "step_pairs" kernel */
		step_pairs(f.b(0), &pairs_[0]);

		/* Execute "step_bodies" kernel */
		step_bodies(f.b(0), &pairs_[0], &map_, dt);

		/* Execute "step_collisions" kernel */
		step_collisions(f.b(0), &pairs_[0], &flag_multi_coll, &nc);

		/* Execute "clear_bodies_num_collisions" kernel */
		clear_bodies_num_collisions(f.b(0));

		if(flag_multi_coll)
		{
			puts("resolve multi_coll");

			/* Execute "step_collisions" kernel on a single thread to resolve bodies with multiple collisions */
			step_collisions(f.b(0), &pairs_[0], &flag_multi_coll, &nc);
		}
		
		total_coll += nc;
		nc = 0;
		
		/* Reset flag_multi_coll */
		flag_multi_coll = 0;

		if(f.count_dead() != total_coll)
		{
			printf("1: %i %i\n", f.count_dead(), total_coll);
			exit(1);
		}

		/* Store data for timestep */
		//add_frame(num_bodies_);
		//memcpy(b(t), f.b(0), num_bodies_ * sizeof(Body));
		frames_.frames_.push_back(f);

		assert(frames_.frames_.size() == (t+1));

		assert(frames_.frames_[t].bodies_.size() == f.bodies_.size());
		
		if(count_dead(t) != f.count_dead())
		{
			printf("2: %i %i\n", count_dead(t), f.count_dead());
			exit(1);
		}
	

		if(count_dead(t) != total_coll)
		{
			printf("3: %i %i\n", count_dead(t), total_coll);
			exit(1);
		}
	}
}
void	Universe::add_frame(unsigned int n)
{
	frames_.frames_.emplace_back();
	frames_.frames_.back().alloc(n);
}
void	Universe::rw_header()
{
	//operator&(num_bodies_);
	operator&(num_steps_);
	operator&(first_step_);
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
void		Universe::write()
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

	fwrite(&num_steps_, sizeof(int), 1, pfile_);
	fwrite(&first_step_, sizeof(int), 1, pfile_);

	fwrite(&name_, 32, 1, pfile_);

	frames_.write(pfile_);
	//fwrite(b(0), sizeof(Body), num_steps_ * num_bodies_, pfile_);

	fclose(pfile_);
	pfile_ = 0;
}
int		Universe::read(std::string fileName, int num_steps)
{
	pfile_ = fopen(fileName.c_str(), "r");
	if(!pfile_) return 1;

	int num_steps_old;

	fread(&num_steps_old, sizeof(int), 1, pfile_);
	fread(&first_step_, sizeof(int), 1, pfile_);

	fread(&name_, 32, 1, pfile_);

	printf("name = %s\n", name_);

	if(num_steps > 0)
	{
		// Read in order to continue simulation

		num_steps_ = num_steps;

		first_step_ += num_steps_;

		// temporary frames
		//Body * bodies = new Body[num_bodies_ * num_steps_old * sizeof(Body)];
		Frames frames;
		frames.read(pfile_);
		
		// copy last to first
		//memcpy(b(0), bodies + (num_steps_old - 1) * num_bodies_, num_bodies_ * sizeof(Body));
		get_frame(0) = frames_.frames_[num_steps_old - 1];

		alloc(size(0), num_steps_);
	}
	else
	{
		num_steps_ = num_steps_old;

		frames_.read(pfile_);

		alloc(size(0), num_steps_);
	}

	fclose(pfile_);
	pfile_ = 0;
	return 0;
}
int		Universe::mass_center(int t, float * x, float * s)
{

	float temp[3] = {0,0,0};

	float m = 0;

	for(int i = 0; i < size(t); i++)
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

		for(int i = 0; i < size(t); i++)
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

	for(Body * pb = b(0); pb < (b(0) + size(0)); pb++)
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
	float umass = size(0) * m;

	for(Body * pb = b(0); pb < (b(0) + size(0)); pb++)
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
unsigned int	Universe::size(unsigned int t)
{
	assert(t < frames_.frames_.size());
	return frames_.frames_[t].bodies_.size();
}




