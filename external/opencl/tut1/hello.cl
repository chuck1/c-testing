
#include "body.h"



__kernel void step_bodies(
		    __global struct Body * bodies,
		    __global struct Pair * pairs,
		    __global struct BodyMap * bodymaps,
		    float dt
		   )
{
	float f[3];

	/* global index */
	
	int block = NUM_BODIES / get_global_size(0);
	
	int b0 = get_global_id(0) * block;
	int b1 = b0 + block;
	
	if(get_global_id(0) == (get_global_size(0) - 1)) b1 = NUM_BODIES;
	
	/* local index */

	int local_block = (b1 - b0) / get_local_size(0);
	
	int b_local0 = b0 + get_local_id(0) * local_block;
	int b_local1 = b_local0 + local_block;
	
	if(get_local_id(0) == (get_local_size(0) - 1)) b_local1 = b1;
	
	/* */

	__global struct BodyMap * pbm = 0;
	__global struct Body * pb = 0;
	
	for(int b = b_local0; b < b_local1; b++)
	{
		pbm = bodymaps + b;
		pb = bodies + b;
		
		f[0] = 0;
		f[1] = 0;
		f[2] = 0;
		
		for(int p = 0; p < (NUM_BODIES - 1); p++)
		{
			__global struct Pair * pp = &pairs[pbm->pair[p]];

			f[0] += pp->u[0] * pp->f * pbm->f_sign[p];
			f[1] += pp->u[1] * pp->f * pbm->f_sign[p];
			f[2] += pp->u[2] * pp->f * pbm->f_sign[p];
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
		    __global struct Body* bodies,
		    __global struct Pair* pairs
		    )
{

	int block = NUM_PAIRS / get_global_size(0);
	
	int p0 = get_global_id(0) * block;
	int p1 = p0 + block;
	
	if(get_global_id(0) == (get_global_size(0) - 1)) p1 = NUM_PAIRS;

	/* local index */
	
	int local_block = (p1 - p0) / get_local_size(0);
	
	int p_local0 = p0 + get_local_id(0) * local_block;
	int p_local1 = p_local0 + local_block;
	
	if(get_local_id(0) == (get_local_size(0) - 1)) p_local1 = p1;
	
	//barrier(CLK_LOCAL_MEM_FENCE);
	
	for(int p = p_local0; p < p_local1; p++)
	{
		__global struct Pair* pp = pairs + p;

		__global struct Body* b0 = &bodies[pp->b0];
		__global struct Body* b1 = &bodies[pp->b1];
		
		__global float * x0 = bodies[pp->b0].x;
		__global float * x1 = bodies[pp->b1].x;
	
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



