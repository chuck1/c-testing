
#include "body.h"


__kernel void clear_bodies_num_collisions(
		    __global struct Body * bodies
		    )
{
	/* global index */
	
	int block = NUM_BODIES / get_global_size(0);
	
	int b0 = get_global_id(0) * block;
	int b1 = b0 + block;
	
	if(get_global_id(0) == (get_global_size(0) - 1)) b1 = NUM_BODIES;
	
	//for(int b = b_local0; b < b_local1; b++)
	for(int b = b0; b < b1; b++)
	{
		bodies[b].num_collisions = 0;
	}
}
__kernel void step_bodies(
		    __global struct Body * bodies,
		    __global struct Pair * pairs,
		    __global struct Map * map,
		    float dt
		   )
{

	/* work group */
	int local_block = NUM_BODIES / get_num_groups(0);
	
	int i_group0 = get_group_id(0) * local_block;
	int i_group1 = i_group0 + local_block;
	
	if(get_group_id(0) == (get_num_groups(0) - 1)) i_group1 = NUM_PAIRS;
	
	/* work item */
	int block = (i_group1 - i_group0) / get_local_size(0);
	
	int i_local0 = i_group0 + get_local_id(0) * block;
	int i_local1 = i_local0 + block;
	
	if(get_local_id(0) == (get_local_size(0) - 1)) i_local1 = i_group1;

	/* copy data for work group */
	//__local struct Pair local_pairs[NUM_PAIRS];
	//__local struct BodyMap local_bodymaps[NUM_BODIES / NUM_GROUPS];
	
	//event_t e0 = async_work_group_copy((__local char *)local_pairs, (__global char *)pairs, NUM_PAIRS * sizeof(struct Pair), 0);
	//wait_group_events(1, &e0);

	//event_t e1 = async_work_group_copy((__local char *)local_bodymaps, (__global char *)(bodymaps + i_group0), (i_group1 - i_group0) * sizeof(struct BodyMap), 0);
	//wait_group_events(1, &e1);

	/* */
	float f[3];

	//__local struct BodyMap * pbm = 0;
	//__global struct BodyMap * pbm = 0;

	__global struct Body * pb = 0;
	
	for(int b = i_local0; b < i_local1; b++)
	{
		//pbm = local_bodymaps + b;
		//pbm = bodymaps + b;

		pb = bodies + b;
	
		if(!pb->alive) continue;

		f[0] = 0;
		f[1] = 0;
		f[2] = 0;
		
		for(int i = 0; i < NUM_BODIES; i++)
		{
			if(b == i) continue;

			float s = 1.0;
		
			//__local struct Pair * pp = &local_pairs[pbm->pair[p]];
			__global struct Pair * pp = pairs + map->pair[b][i];
			
			if(!pp->alive) continue;

			if(pp->b0 == b)
			{
				s = - 1.0;
			}

			f[0] += pp->u[0] * pp->f * s;
			f[1] += pp->u[1] * pp->f * s;
			f[2] += pp->u[2] * pp->f * s;
		}
		
		pb->v[0] += dt * f[0] / pb->mass;
		pb->v[1] += dt * f[1] / pb->mass;
		pb->v[2] += dt * f[2] / pb->mass;

		pb->x[0] += dt * pb->v[0];
		pb->x[1] += dt * pb->v[1];
		pb->x[2] += dt * pb->v[2];
	}
}

__kernel void step_pairs(
		    __global struct Body * bodies,
		    __global struct Pair * pairs
		    )
{
	/* work group */
	int local_block = NUM_PAIRS / get_num_groups(0);
	
	int i_group0 = get_group_id(0) * local_block;
	int i_group1 = i_group0 + local_block;
	
	if(get_group_id(0) == (get_num_groups(0) - 1)) i_group1 = NUM_PAIRS;
	
	/* work item */
	int block = (i_group1 - i_group0) / get_local_size(0);
	
	int i_local0 = i_group0 + get_local_id(0) * block;
	int i_local1 = i_local0 + block;
	
	if(get_local_id(0) == (get_local_size(0) - 1)) i_local1 = i_group1;

	/* copy data for work group */
	__local struct Body local_bodies[NUM_BODIES];

	event_t e = async_work_group_copy((__local char *)local_bodies, (__global char *)bodies, NUM_BODIES * sizeof(struct Body), 0);
	wait_group_events(1, &e);
	
	/* compute */
	for(int p = i_local0; p < i_local1; p++)
	{
		__global struct Pair* pp = pairs + p;

		if(!pp->alive) continue;

		__local struct Body* b0 = local_bodies + pp->b0;
		__local struct Body* b1 = local_bodies + pp->b1;

		if(!b0->alive)
		{
			pp->alive = 0;
			continue;
		}
		if(!b1->alive)
		{
			pp->alive = 0;
			continue;
		}
		
		__local float * x0 = b0->x;
		__local float * x1 = b1->x;
	
		float r[3];
		
		r[0] = x0[0] - x1[0];
		r[1] = x0[1] - x1[1];
		r[2] = x0[2] - x1[2];
	
		float d2 = r[0]*r[0] + r[1]*r[1] + r[2]*r[2];

		float dr = rsqrt(d2);

		pp->d = sqrt(d2);
	
		if(pp->d < (b0->radius + b1->radius))
		{
			pp->collision = 1;
			b0->num_collisions++;
			b1->num_collisions++;
		}

		pp->u[0] = r[0] * dr;
		pp->u[1] = r[1] * dr;
		pp->u[2] = r[2] * dr;
		
		pp->f = 6.67384E-11 * b0->mass * b1->mass / d2;
	}

}

/* dont use marcos here for global_size etc. */
__kernel void step_collisions(
		    __global struct Body* bodies, /* readonly */
		    __global struct Pair* pairs,
		    __global int * flag_multi_coll
		    )
{
	/* work group */
	int local_block = NUM_PAIRS / get_num_groups(0);
	
	int i_group0 = get_group_id(0) * local_block;
	int i_group1 = i_group0 + local_block;
	
	if(get_group_id(0) == (get_num_groups(0) - 1)) i_group1 = NUM_PAIRS;
	
	/* work item */
	int block = (i_group1 - i_group0) / get_local_size(0);
	
	int i_local0 = i_group0 + get_local_id(0) * block;
	int i_local1 = i_local0 + block;
	
	if(get_local_id(0) == (get_local_size(0) - 1)) i_local1 = i_group1;

	/* */
	for(int p = i_local0; p < i_local1; p++)
	{
		__global struct Pair* pp = pairs + p;

		if(!pp->alive) continue;

		__global struct Body* b0 = bodies + pp->b0;
		__global struct Body* b1 = bodies + pp->b1;

		if(!b0->alive)
		{
			pp->alive = 0;
			continue;
		}
		if(!b1->alive)
		{
			pp->alive = 0;
			continue;
		}

		/* modifying a body involved in multiple collisions could cause data race */
		if(b0->num_collisions > 1)
		{
			atomic_add(flag_multi_coll, 1);
			continue;
		}
		if(b1->num_collisions > 1)
		{
			atomic_add(flag_multi_coll, 1);
			continue;
		}

		__global float * x0 = bodies[pp->b0].x;
		__global float * x1 = bodies[pp->b1].x;

		if(pp->collision)
		{
			//if(b0 < b1)
			{
				//printf("collision\n");
				//num_collision++;
				
				//pairs.push_back(Pair(me,i));
				
				// total momentum
				float mom[3];
				mom[0] = b0->v[0] * b0->mass + b1->v[0] * b1->mass;
				mom[1] = b0->v[1] * b0->mass + b1->v[1] * b1->mass;
				mom[2] = b0->v[2] * b0->mass + b1->v[2] * b1->mass;

				// total mass
				float m = b0->mass + b1->mass;
	
				// mass-weighted average position
				float x[3];
				x[0] = (x0[0] * b0->mass + x1[0] * b1->mass) / m;
				x[1] = (x0[1] * b0->mass + x1[1] * b1->mass) / m;
				x[2] = (x0[2] * b0->mass + x1[2] * b1->mass) / m;
	
				x0[0] = x[0];
				x0[1] = x[1];
				x0[2] = x[2];
	
				// absorb mass
				b0->mass = m;
				b0->radius = pow(3.0 / 4.0 / 3.1415 * m / 900.0, 0.333333);
		
				/*
				printf("mass = %f radius = %f\n", m, u.r(t, me));
				printf("p = %f %f %f\n",
						u.p(t, me).x,
						u.p(t, me).y,
						u.p(t, me).z);
				*/
	
				// new velocity
				b0->v[0] = mom[0] / m;
				b0->v[1] = mom[1] / m;
				b0->v[2] = mom[2] / m;
	
				b1->alive = 0;
				pp->alive = 0;
			}

		}

	
		float r[3];
		
		r[0] = x0[0] - x1[0];
		r[1] = x0[1] - x1[1];
		r[2] = x0[2] - x1[2];
	
		float d2 = r[0]*r[0] + r[1]*r[1] + r[2]*r[2];

		float dr = rsqrt(d2);

		pp->d = sqrt(d2);
		
		pp->u[0] = r[0] * dr;
		pp->u[1] = r[1] * dr;
		pp->u[2] = r[2] * dr;
		
		pp->f = 6.67384E-11 * b0->mass * b1->mass / d2;
	}
}


