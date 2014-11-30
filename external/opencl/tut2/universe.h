#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "body.h"

float radius(float m);


struct Universe
{
	Body*		b(int t)
	{
		return bodies + (t * num_bodies_);
	}
	Body&		b(int t, int i)
	{
		return bodies[t * num_bodies_ + i];
	}
	void		alloc(int num_bodies, int num_steps)
	{
		num_bodies_ = num_bodies;
		num_steps_ = num_steps;
		num_pairs_ = (num_bodies * (num_bodies - 1)) / 2;

		bodies = (Body*)malloc(sizeof(Body) * num_bodies_ * num_steps_);
		pairs = (Pair*)malloc(sizeof(Pair) * num_pairs_);

		// pair index
		int k = 0;
		
		
		for(int i = 0; i < num_bodies_; i++)
		{
			bodies[i].alive = 1;
			bodies[i].num_collisions = 0;
		}
		for(int i = 0; i < num_pairs_; i++)
		{
			pairs[i].alive = 1;
			pairs[i].collision = 0;
		}


		for(int i = 0; i < num_bodies; i++)
		{
			for(int j = i + 1; j < num_bodies; j++)
			{
				Pair * pp = pairs + k;
				pp->b0 = i;
				pp->b1 = j;
				
				map.pair[i * NUM_BODIES + j] = k;
				map.pair[i * NUM_BODIES + j] = k;

				k++;
			}
		}
	}

	void		random(float m)
	{
		int w = 1000;
		
		// universe mass
		float umass = num_bodies_ * m;
		
		for(Body * b = bodies; b < (bodies + num_bodies_); b++)
		{
			b->x[0] = (float)(rand() % w) - (float)w * 0.5;
			b->x[1] = (float)(rand() % w) - (float)w * 0.5;
			b->x[2] = (float)(rand() % w) - (float)w * 0.5;
			
			float r = sqrt(b->x[0] * b->x[0] + b->x[1] * b->x[1] + b->x[2] * b->x[2]);

			float rxz = sqrt(b->x[0] * b->x[0] + b->x[2] * b->x[2]);
			
			float v = sqrt(6.67384E-11 * umass / r) * 0.5;

/*			
			b->v[0] = 0;
			b->v[1] = 0;
			b->v[2] = 0;
			*/
			b->v[0] = -b->x[2] / rxz * v;
			b->v[1] = 0;
			b->v[2] = b->x[0] / rxz * v;

			b->mass = m;
			b->radius = radius(b->mass);
		}
	}
	void		free()
	{
		::free(bodies);
		::free(pairs);
	}
	void write()
	{
		FILE* fp = fopen("data.dat", "w");

		fwrite(&num_bodies_, sizeof(int), 1, fp);
		fwrite(&num_steps_, sizeof(int), 1, fp);
		
		fwrite(bodies, sizeof(Body), num_steps_ * num_bodies_, fp);
		
		fclose(fp);
	}
	int read()
	{
		FILE* fp = fopen("data.dat", "r");
		if(!fp) return 1;
		fread(&num_bodies_, sizeof(int), 1, fp);
		fread(&num_steps_, sizeof(int), 1, fp);

		alloc(num_bodies_, num_steps_);
		
		fread(bodies, sizeof(Body), num_steps_ * num_bodies_, fp);
		
		fclose(fp);
		return 0;
	}


	Body*		bodies;

	Map		map;
	Pair*		pairs;

	int		num_bodies_;
	int		num_pairs_;
	int		num_steps_;
};


#endif
