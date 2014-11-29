
#define NUM_BODIES (100)
#define NUM_PAIRS (NUM_BODIES * (NUM_BODIES - 1) / 2)
#define NUM_STEPS  (1000)

struct Body
{
	float	x[3];
	float	v[3];
	float	mass;
	float	radius;
};

struct BodyMap
{
	int	pair[NUM_BODIES-1];
	float	f_sign[NUM_BODIES-1];
};

struct Pair
{
	int	b0;
	int	b1;
	
	float	u[3];
	float	d;
	float	f;
};

