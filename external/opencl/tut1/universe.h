
#include "body.h"

struct Universe
{
	
	Body*	bodies;
	Pair*	pairs;
	
	int	num_bodies_;
	int	num_pairs_;
};

void universe_alloc(Universe* u, int num_bodies)
{
	u->num_bodies_ = num_bodies;
	u->num_pairs_ = (num_bodies * (num_bodies - 1)) / 2;

	u->bodies = (Body*)malloc(sizeof(Body) * u->num_bodies_);
	u->pairs = (Pair*)malloc(sizeof(Pair) * u->num_pairs_);

	int k = 0;

	for(int i = 0; i < num_bodies; i++)
	{
		for(int j = i + 1; j < num_bodies; j++)
		{
			u->pairs[k].b0 = i;
			u->pairs[k].b0 = j;

			u->bodies[i].pair = k;
			u->bodies[j].pair = k;

			k++;
		}
	}
}


