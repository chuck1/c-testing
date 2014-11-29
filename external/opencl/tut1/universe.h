#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "body.h"

float radius(float m)
{
	return pow(m / 900.0 * 3.0 / 4.0 / M_PI, 0.3333333333);
}


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
		bodymaps = (BodyMap*)malloc(sizeof(BodyMap) * num_bodies_);
		pairs = (Pair*)malloc(sizeof(Pair) * num_pairs_);

		int k = 0;

		// pair index
		int p[num_bodies];
		for(int i = 0; i < num_bodies; i++) p[i] = 0;

		for(int i = 0; i < num_bodies; i++)
		{
			for(int j = i + 1; j < num_bodies; j++)
			{
				Pair * pp = pairs + k;
				pp->b0 = i;
				pp->b1 = j;

				bodymaps[i].pair[p[i]] = k;
				bodymaps[j].pair[p[j]] = k;

				bodymaps[i].f_sign[p[i]] = -1.0;
				bodymaps[j].f_sign[p[j]] =  1.0;

				p[i]++;
				p[j]++;

				k++;
			}
		}
	}

	void		random(float m)
	{
		for(Body * b = bodies; b < (bodies + num_bodies_); b++)
		{
			b->x[0] = (float)(rand() % 1000);
			b->x[1] = (float)(rand() % 1000);
			b->x[2] = (float)(rand() % 1000);

			b->v[0] = 0;
			b->v[1] = 0;
			b->v[2] = 0;

			b->mass = m;
			b->radius = radius(b->mass);
		}
	}
	void		free()
	{
		::free(bodies);
		::free(bodymaps);
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
	void read()
	{
		FILE* fp = fopen("data.dat", "r");

		fread(&num_bodies_, sizeof(int), 1, fp);
		fread(&num_steps_, sizeof(int), 1, fp);

		alloc(num_bodies_, num_steps_);
		
		fread(bodies, sizeof(Body), num_steps_ * num_bodies_, fp);
		
		fclose(fp);

	}


	Body*		bodies;

	BodyMap*	bodymaps;
	Pair*		pairs;

	int		num_bodies_;
	int		num_pairs_;
	int		num_steps_;
};



