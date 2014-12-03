#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cstring>
#include <cassert>
#include <algorithm>

#include "body.h"
#include "kernel.h"
#include "universe.h"

void		print(float * a)
{
	printf("% 12f % 12f % 12f\n", a[0], a[1], a[2]);
}


Universe::Universe(): first_step_(0)
{
}
Body*		Universe::b(int t)
{
	assert(frames_.frames_.size() > (unsigned int)t);
	return frames_.frames_[t].b(0); // &_M_bodies[0] + (t * num_bodies_);
}
Body*		Universe::b(int t, int i)
{
	assert(frames_.frames_.size() > (unsigned int)t);
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
	//init_map_and_pairs(num_bodies, map_, pairs_);

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
	assert(frames_.frames_.size() > (unsigned int)t);
	return frames_.frames_[t].count_alive();
}
Frame &		Universe::get_frame(int t)
{
	assert(frames_.frames_.size() > (unsigned int)t);
	return frames_.frames_[t];
}
unsigned int	Universe::count_dead(int t)
{
	assert(frames_.frames_.size() > (unsigned int)t);
	return frames_.frames_[t].count_dead();
}
int		Universe::solve()
{
	// temp bodies
	
	//Body* bodies = new Body[num_bodies_];
	//memcpy(bodies, b(0), num_bodies_ * sizeof(Body));
	
	Frame f = get_frame(0);
	
	Pairs pairs;
	pairs.init(f);
	
	unsigned int flag_multi_coll = 0;
	float dt = 10.0;

	float time_sim = 0;
	
	unsigned int alive = count_alive(0);
	unsigned int dead = size(0) - alive;
	
	unsigned int one_tenth = size(0) / 10;
	unsigned int temp_dead = 0;
	
	unsigned int nc = 0;

	unsigned int step = first_step_;
	
	unsigned int number_removed = 0;
	
	float velocity_ratio_min = 0.1;
	float velocity_ratio[3];

	float duration_real = 0;

	printf("num_steps = %i\n", num_steps_);

	for(int t = 1; t < num_steps_; t++)
	{
		auto program_time_start = std::chrono::system_clock::now();

		step++;

		float eta = (duration_real == 0.0) ? 0.0 : (duration_real / (float)(t-1) * (num_steps_ - 1));

		time_sim += dt;
	
		if((t % (num_steps_ / 1)) == 0)
		{
			printf("%16s%16s%16s%16s%16s%16s%16s\n",
					"sim time",
					"step",
					"step inner",
					"alive",
					"dead",
					"temp_dead",
					"eta");
		}
		if((t % (num_steps_ / 10)) == 0)
		{
			printf("%16f%16i%16i%16i%16i%16i%16f\n",
					time_sim,
					step,
					t,
					alive,
					dead,
					temp_dead,
					eta
					);
		}
		
		if(temp_dead >= one_tenth)
		{
			//printf("one tenth\n");
		
			one_tenth = alive / 10;
			temp_dead = 0;

			if(1)
			{
				number_removed += f.reduce();
				pairs.init(f);
			}
		}

		/* Execute "step_pairs" kernel */
		step_pairs(f.b(0), &pairs.pairs_[0], pairs.size());



		/* Execute "step_bodies" kernel */


		std::fill_n(velocity_ratio, 3, 0);

		step_bodies(f.b(0), &pairs.pairs_[0], pairs.map_.ptr(), dt, f.size(), velocity_ratio);
		
		if(0)
		{
		if(
				(velocity_ratio[0] > velocity_ratio_min) ||
				(velocity_ratio[1] > velocity_ratio_min) ||
				(velocity_ratio[2] > velocity_ratio_min)
		  )
		{
			printf("velocity_ratio = % 12f % 12f % 12f\n",
					velocity_ratio[0],
					velocity_ratio[1],
					velocity_ratio[2]
					);

			dt *= 0.5;
		}
		}

		/* Execute "step_collisions" kernel */
		step_collisions(f.b(0), &pairs.pairs_[0], &flag_multi_coll, &nc, pairs.size());
		
		/* Execute "clear_bodies_num_collisions" kernel */
		clear_bodies_num_collisions(f.b(0), f.size());

		if(flag_multi_coll)
		{
			puts("resolve multi_coll");

			/* Execute "step_collisions" kernel on a single thread to resolve bodies with multiple collisions */
			step_collisions(f.b(0), &pairs.pairs_[0], &flag_multi_coll, &nc, pairs.size());
		}
		
		alive -= nc;
		dead += nc;
		temp_dead += nc;
		nc = 0;
		
		/* Reset flag_multi_coll */
		flag_multi_coll = 0;

		if((number_removed + f.count_dead()) != dead)
		{
			printf("1: %i %i\n", (number_removed + f.count_dead()), dead);
			exit(1);
		}

		/* Store data for timestep */
		//add_frame(num_bodies_);
		//memcpy(b(t), f.b(0), num_bodies_ * sizeof(Body));
		frames_.frames_.push_back(f);

		if(frames_.frames_.size() != (unsigned int)(t+1))
		{
			printf("error\nframes_.frames_.size() = %i\n(unsigned int)(t+1) = %i\n",
				(int)frames_.frames_.size(),
				(t+1));
		}

		assert(frames_.frames_[t].bodies_.size() == f.bodies_.size());
		
		if(count_dead(t) != f.count_dead())
		{
			printf("2: %i %i\n", count_dead(t), f.count_dead());
			exit(1);
		}
	

		if((number_removed + count_dead(t)) != dead)
		{
			printf("3: %i %i\n", (number_removed + count_dead(t)), dead);
			exit(1);
		}

		//f.print();
		
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - program_time_start);
		duration_real += (float)duration.count();
	}

	return 0;
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
std::string	Universe::getFilename()
{
	char buffer[8];
	sprintf(buffer, "%i", num_steps_ + first_step_);

	char fileName[128];
	strcpy(fileName, "data/data_");
	strcat(fileName, name_);
	strcat(fileName, "_");
	strcat(fileName, buffer);
	strcat(fileName, ".dat");

	return std::string(fileName);
}
void		Universe::write()
{
	auto filename = getFilename();

	pfile_ = fopen(filename.c_str(), "w");
	if(pfile_ == 0)
	{
		perror("fopen");
		exit(1);
	}
	filemode_ = FILEMODE_WRITE;

	fwrite(&num_steps_, sizeof(int), 1, pfile_);
	fwrite(&first_step_, sizeof(int), 1, pfile_);

	fwrite(&name_, 1, NAME_SIZE, pfile_);

	printf("name = %s\n", name_);

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

	fread(&name_, 1, NAME_SIZE, pfile_);

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
		
		//get_frame(0) = frames.frames_[num_steps_old - 1];
		frames_.frames_.push_back(frames.frames_[num_steps_old - 1]);

		//alloc(size(0), num_steps_);
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
	get_frame(t).mass_center(x, s);
	return 0;
}
void		Universe::stats()
{
	mass_center_.resize(num_steps_);
	
	float s[3];
	
	for(int t = 0; t < num_steps_; t++)
	{
		mass_center(t, &mass_center_[t].x, s);
		
		//print(s);
	}
}
unsigned int	Universe::size(unsigned int t)
{
	assert(t < frames_.frames_.size());
	return frames_.frames_[t].bodies_.size();
}



