

struct Body
{
	//float3 x;
	float3 x;
	float v[3];
	float mass;
	float radius;
	int pair;
};

struct Pair
{
	int	b0;
	int	b1;
	
	//float3	u;
	float3	u;
	float	d;
	float	f;
};

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

	//float3 r;
	//float3 r = b0->x - b1->x;
	
	pairs[p].u = b0->x - b1->x;
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



