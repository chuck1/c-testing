
#define NUM_BODIES (100)

struct Body
{
	//float3 x;
	float x[3];
	float v[3];
	float mass;
	float radius;

	int pair[NUM_BODIES - 1];
	float f_sign[NUM_BODIES - 1];
};

struct Pair
{
	int	b0;
	int	b1;
	
	//float3	u;
	float	u[3];
	float	d;
	float	f;
};

__kernel void step_bodies(
		    __global struct Body * bodies,
		    __global struct Pair * pairs,
		    __global float * dt
		   )
{
	float f[3];

	int block = NUM_BODIES / get_global_size(0);
	
	__global struct Body * b0 = &bodies[get_global_id(0) * block];
	__global struct Body * b1 = b0 + block;
	
	if(get_global_id(0) == (get_global_size(0) - 1)) b1 = &bodies[NUM_BODIES];

	__global struct Body * b = b0;
	
	for(; b < b1; b++)
	{
		f[0] = 0;
		f[1] = 0;
		f[2] = 0;
		
		for(int p = 0; p < (NUM_BODIES - 1); p++)
		{
			__global struct Pair * pp = &pairs[b->pair[p]];

			f[0] += pp->u[0] * pp->f * b->f_sign[p];
			f[1] += pp->u[1] * pp->f * b->f_sign[p];
			f[2] += pp->u[2] * pp->f * b->f_sign[p];
		}
		
		b->v[0] += *dt * f[0] / b->mass;
		b->v[1] += *dt * f[1] / b->mass;
		b->v[2] += *dt * f[2] / b->mass;

		b->x[0] += *dt * b->v[0];
		b->x[1] += *dt * b->v[1];
		b->x[2] += *dt * b->v[2];
	}
	
	
}

__kernel void hello(
		    __global char* string,
		    __global struct Body* bodies,
		    __global struct Pair* pairs,
		    __global int* num_pairs)
{

int block = *num_pairs / get_global_size(0);

int p0 = get_global_id(0) * block;
int p1 = p0 + block;

if(get_global_id(0) == (get_global_size(0) - 1)) p1 = *num_pairs;

//barrier(CLK_LOCAL_MEM_FENCE);


for(int p = p0; p < p1; p++)
{
	__global struct Body* b0 = &bodies[pairs[p].b0];
	__global struct Body* b1 = &bodies[pairs[p].b1];
	//float3 x0 = b0->x;
	//float3 x1 = b1->x;

	__global float * x0 = bodies[pairs[p].b0].x;
	__global float * x1 = bodies[pairs[p].b1].x;

	//float3 r;
	//float3 r = b0->x - b1->x;
	
	float r[3];
	
	r[0] = x0[0] - x1[0];
	r[1] = x0[1] - x1[1];
	r[2] = x0[2] - x1[2];

	float d2 = r[0]*r[0] + r[1]*r[1] + r[2]*r[2];

	pairs[p].d = sqrt(d2);
	
	pairs[p].u[0] = r[0] / pairs[p].d;
	pairs[p].u[1] = r[1] / pairs[p].d;
	pairs[p].u[2] = r[2] / pairs[p].d;
	
	pairs[p].f = 6.67384E-11 * b0->mass * b1->mass / d2;
}



string[0] = 'H';
string[1] = 'e';
string[2] = 'l';
string[3] = 'l';
string[4] = 'o';
string[5] = ',';
string[6] = ' ';
string[7] = 'W';
string[8] = 'o';
string[9] = 'r';
string[10] = 'l';
string[11] = 'd';
string[12] = '!';
string[13] = '\0';



}



