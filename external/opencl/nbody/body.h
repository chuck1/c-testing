#ifndef BODY_H
#define BODY_H

#define NUM_BODIES (512)
#define NUM_PAIRS (NUM_BODIES * (NUM_BODIES - 1) / 2)

#define GLOBAL_SIZE (128)
#define LOCAL_SIZE (8)
#define NUM_GROUPS (GLOBAL_SIZE / LOCAL_SIZE)


struct Body
{
	Body(): x{0,0,0}, v{0,0,0}, mass(0), radius(0), alive(1), num_collisions(0) {}
	
	float	x[3]; // 4 * 3 = 12
	float	v[3]; // 4 * 3 = 12
	float	mass; // 4
	float	radius; // 4
	// 12 + 12 + 4 + 4 = 32
	
	unsigned int	alive; // 4
	unsigned int	num_collisions; // 4
	
	// 40
	
};

struct Map
{
	unsigned int	pair[NUM_BODIES * NUM_BODIES];
};

struct Pair
{
	Pair(): b0(0), b1(0), u{0,0,0}, d(0), f(0), alive(1), collision(0) {}

	int	b0; // 4
	int	b1; // 4
	
	float	u[3]; // 12
	float	d; // 4
	float	f; // 4
	
	// 28

	unsigned int	alive; // 4
	unsigned int	collision; // 4

	// 36
	
};

#endif
