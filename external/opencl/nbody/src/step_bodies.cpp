#include <cmath>
#include <cstdio>
#include "body.h"
#include "kernel.h"
#include <cassert>

void step_bodies(
		    struct Body * bodies,
		    struct Pair * pairs,
		    unsigned int * map,
		    float dt,
		    unsigned int num_bodies,
		    float * velocity_ratio
		   )
{
	/* work group */
	int local_block = num_bodies / get_num_groups(0);
	
	unsigned int i_group0 = get_group_id(0) * local_block;
	unsigned int i_group1 = i_group0 + local_block;
	
	if(get_group_id(0) == (get_num_groups(0) - 1)) i_group1 = num_bodies;
	
	/* work item */
	int block = (i_group1 - i_group0) / get_local_size(0);
	
	unsigned int i_local0 = i_group0 + get_local_id(0) * block;
	unsigned int i_local1 = i_local0 + block;
	
	if(get_local_id(0) == (get_local_size(0) - 1)) i_local1 = i_group1;

	/*
	printf("local_block = %i\n", local_block);
	printf("block = %i\n", block);
	*/
/*
	printf("i_local0 = %i\n", i_local0);
	printf("i_local1 = %i\n", i_local1);
*/
	/* copy data for work group */
	//__local struct Pair local_pairs[NUM_PAIRS];
	//__local struct BodyMap local_bodymaps[NUM_BODIES / NUM_GROUPS];
	
	//event_t e0 = async_work_group_copy((__local char *)local_pairs, (char *)pairs, NUM_PAIRS * sizeof(struct Pair), 0);
	//wait_group_events(1, &e0);

	//event_t e1 = async_work_group_copy((__local char *)local_bodymaps, (char *)(bodymaps + i_group0), (i_group1 - i_group0) * sizeof(struct BodyMap), 0);
	//wait_group_events(1, &e1);

	/* */
	float f[3];

	//__local struct BodyMap * pbm = 0;
	//struct BodyMap * pbm = 0;

	Body * pb = 0;
	
	for(unsigned int b = i_local0; b < i_local1; b++)
	{
		//pbm = local_bodymaps + b;
		//pbm = bodymaps + b;

		pb = bodies + b;
	
		if(pb->alive == 0)
		{
			//puts("body dead");
			continue;
		}

		f[0] = 0;
		f[1] = 0;
		f[2] = 0;
		
		for(unsigned int i = 0; i < num_bodies; i++)
		{
			if(b == i) continue;

			//__local struct Pair * pp = &local_pairs[pbm->pair[p]];
			Pair * pp = pairs + map[b * num_bodies + i];

			if(pp->_M_alive == 0) continue;


			if(pp->b0 == b)
			{
				f[0] -= pp->u[0] * pp->f;
				f[1] -= pp->u[1] * pp->f;
				f[2] -= pp->u[2] * pp->f;
			}
			else if(pp->b1 == b)
			{
				f[0] += pp->u[0] * pp->f;
				f[1] += pp->u[1] * pp->f;
				f[2] += pp->u[2] * pp->f;
			}
			else
			{
				assert(0);
			}
		}

		float dv[3];
		dv[0] = dt * f[0] / pb->mass;
		dv[1] = dt * f[1] / pb->mass;
		dv[2] = dt * f[2] / pb->mass;

		float e = 0.01;

		float rat[3];
		rat[0] = fabs(dv[0] / pb->v[0]);
		rat[1] = fabs(dv[1] / pb->v[1]);
		rat[2] = fabs(dv[2] / pb->v[2]);
		
		// atomic
		if(std::isfinite(rat[0])) if(rat[0] > velocity_ratio[0]) velocity_ratio[0] = rat[0];
		if(std::isfinite(rat[1])) if(rat[1] > velocity_ratio[1]) velocity_ratio[1] = rat[1];
		if(std::isfinite(rat[2])) if(rat[2] > velocity_ratio[2]) velocity_ratio[2] = rat[2];
		
		if(0)
		{
			if(
					((std::isfinite(rat[0])) && (rat[0] > e)) ||
					((std::isfinite(rat[1])) && (rat[1] > e)) ||
					((std::isfinite(rat[2])) && (rat[2] > e))
			  )
			{
				printf("% 12f % 12f % 12f\n",
						rat[0],
						rat[1],
						rat[2]);
			}
		}

		pb->v[0] += dv[0];
		pb->v[1] += dv[1];
		pb->v[2] += dv[2];

		pb->x[0] += dt * pb->v[0];
		pb->x[1] += dt * pb->v[1];
		pb->x[2] += dt * pb->v[2];
	}
}