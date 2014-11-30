//#ifndef BODY_H
//#define BODY_H

#define NUM_BODIES (1024)
#define NUM_PAIRS (NUM_BODIES * (NUM_BODIES - 1) / 2)
#define NUM_STEPS  (1000)

#define GLOBAL_SIZE (128)
#define LOCAL_SIZE (4)
#define NUM_GROUPS (GLOBAL_SIZE / LOCAL_SIZE)


struct Body
{
	float	x[3];
	float	v[3];
	float	mass;
	float	radius;

	unsigned char	alive;
	unsigned char	num_collisions;
};

struct Map
{
	unsigned int	pair[NUM_BODIES][NUM_BODIES];
};

struct Pair
{
	int	b0;
	int	b1;
	
	float	u[3];
	float	d;
	float	f;

	unsigned char	alive;
	unsigned char	collision;
};

//#endif
