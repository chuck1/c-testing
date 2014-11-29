#include <math.h>
#include <stdlib.h>

#include "body.h"

struct Universe
{
	Body*	b(int t)
	{
		return bodies + t * num_bodies_;
	}


	Body*	bodies;

	BodyMap*	body_map;
	Pair*		pairs;
	
	int	num_bodies_;
	int	num_pairs_;
};

void universe_alloc(Universe* u, int num_bodies, int num_steps)
{
	u->num_bodies_ = num_bodies;
	u->num_pairs_ = (num_bodies * (num_bodies - 1)) / 2;

	u->bodies = (Body*)malloc(sizeof(Body) * u->num_bodies_ * num_steps);
	u->pairs = (Pair*)malloc(sizeof(Pair) * u->num_pairs_);

	int k = 0;

	// pair index
	int p[num_bodies];
	for(int i = 0; i < num_bodies; i++) p[i] = 0;
	
	for(int i = 0; i < num_bodies; i++)
	{
		for(int j = i + 1; j < num_bodies; j++)
		{
			u->pairs[k].b0 = i;
			u->pairs[k].b0 = j;

			u->bodies[i].pair[p[i]] = k;
			u->bodies[j].pair[p[j]] = k;

			u->bodies[i].f_sign[p[i]] = -1.0;
			u->bodies[j].f_sign[p[j]] =  1.0;
		
			p[i]++;
			p[j]++;
			
			k++;
		}
	}
}

float radius(float m)
{
	return pow(m / 900.0 * 3.0 / 4.0 / M_PI, 0.3333333333);
}


void universe_random(Universe* u, float m)
{
	for(Body * b = u->bodies; b < (u->bodies + u->num_bodies_); b++)
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

void universe_free(Universe* u)
{
	free(u->bodies);
	free(u->pairs);
}

