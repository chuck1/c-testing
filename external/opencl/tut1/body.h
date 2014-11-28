
struct Body
{
	float x[3];
	float v[3];
	float mass;
	float radius;
	int pair;
};

struct Pair
{
	int	b0;
	int	b1;
	
	float	u[3];
	float	d;
	float	f;
};

