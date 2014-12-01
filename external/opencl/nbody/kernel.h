
int	get_num_groups(int);
int	get_group_id(int);
int	get_local_id(int);
int	get_local_size(int);
int	get_global_size(int);
float	rsqrt(float);
void step_bodies(
		struct Body * bodies,
		struct Pair * pairs,
		struct Map * map,
		float dt
		);

void step_pairs(
		struct Body * bodies,
		struct Pair * pairs
	       );
void step_collisions(
		struct Body* bodies, /* readonly */
		struct Pair* pairs,
		unsigned int * flag_multi_coll,
		unsigned int * nc
		);
void clear_bodies_num_collisions(
		struct Body * bodies
		);

