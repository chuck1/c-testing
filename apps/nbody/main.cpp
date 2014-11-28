<<<<<<< HEAD
#include <vector>
=======
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
#include <cstdlib>
#include <mpi.h>
#include <glm/glm.hpp>

#include "nbody.hpp"

Universe u;

float G = 6.674e-11;
float dt = 100.0;
<<<<<<< HEAD
int nb = 1000;
int ns = 20000;
int num_collision = 0;
float mass = 1e5;

std::vector<Pair> pairs;

//float min_d = FLT_MAX;

//float density = 7874; // iron
float density = 934; // water ice at 93 K

float radius(float m, float d)
{
	return pow(m / d * 3.0 / 4.0 / M_PI, 0.3333333333);
}

int	collide_pair(int t, int me, int i)
{
	if(!u.alive(t, i)) return 0;

	glm::vec3 r;
	float d;
	glm::vec3 p; //momentum	
	float m; // combined mass
	glm::vec3 x; // new position

	r = u.p(t, i) - u.p(t, me);
	d = glm::length(r);

	if(d < (u.r(t,me) + u.r(t,i)))
	{
		if(me < i)
		{
			//printf("collision\n");
			num_collision++;
			
			pairs.push_back(Pair(me,i));
			
			// total momentum
			p = u.v(t,me) * u.m(t,me) + u.v(t,i) * u.m(t,i);
			
			m = u.m(t,me) + u.m(t,i);

			// mass-weighted average position
			x = (u.p(t, me) * u.m(t, me) + u.p(t, i) * u.m(t, i)) / m;

			u.p(t, me) = x;

			// absorb mass
			u.m(t, me) = m;
			u.r(t, me) = radius(m, density);
	
			/*
			printf("mass = %f radius = %f\n", m, u.r(t, me));
			printf("p = %f %f %f\n",
					u.p(t, me).x,
					u.p(t, me).y,
					u.p(t, me).z);
			*/

			// new velocity
			u.v(t, me) = p / u.m(t, me);

			u.alive(t, i) = false;

			return 1;
		}
	}
	return 0;
}

int	collide(int t, int me)
{
	if(!u.alive(t, me)) return 0;

	int c = 0;

	for(int i = 0; i < me; i++)
	{
		c = collide_pair(t, me, i);
		
		if(c) return c;
	}

	for(int i = me + 1; i < u.num_bodies; i++)
	{
		c = collide_pair(t, me, i);
		
		if(c) return c;
	}

	return c;
}

void	update_pair(glm::vec3& a, int t, int me, int i)
{
	if(!u.alive(t-1, i)) return;

	glm::vec3 r;
	float d;

	r = u.p(t-1, i) - u.p(t-1, me);
	d = glm::length(r);

	/*	
		if(d < (u.r(t-1,me) + u.r(t-1,i)))
		{
		if(me < i)
		{
		}
		}
		*/
	
=======
int nb = 100;
int ns = 1000;
int num_collision = 0;

float min_d = FLT_MAX;

void	update_pair(glm::vec3& a, int t, int me, int i)
{
	glm::vec3 r;
	float d;

	r = u.p(t-1, i) - u.p(t-1, me);
	d = glm::length(r);

	if(d < (u.r(t-1,me) + u.r(t-1,i)))
	{
		//printf("collision\n");
		num_collision++;
	}

	min_d = std::min(min_d, d);

>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
	a += r * (float)(G * u.m(t-1, i) / pow(d,3.0f));
}

void	update(int me, float dt, int t)
{
<<<<<<< HEAD
	u.alive(t, me) = u.alive(t-1, me);

	if(!u.alive(t-1, me)) return;

	glm::vec3 a;


	for(int i = 0; i < me; i++) update_pair(a, t, me, i);

	for(int i = me + 1; i < u.num_bodies; i++) update_pair(a, t, me, i);

	u.v(t, me) = u.v(t-1, me) + a * dt;
	u.p(t, me) = u.p(t-1, me) + u.v(t, me) * dt;
	u.m(t, me) = u.m(t-1, me);
	u.r(t, me) = u.r(t-1, me);
=======
	glm::vec3 a;

	for(int i = 0; i < me; i++) update_pair(a, t, me, i);
	
	for(int i = me + 1; i < u.num_bodies; i++) update_pair(a, t, me, i);
	
	u.setv(t, me, u.v(t-1, me) + a * dt);
	u.setp(t, me, u.p(t-1, me) + u.v(t, me) * dt);
	u.setm(t, me, u.m(t-1, me));
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77

	if(me == 0)
	{
		//printf("%f\n", d);
		//printf("%f %f %f\n", u.p(t, me).x, u.p(t, me).y, u.p(t, me).z);
	}
}


int main(int argc, char ** argv)
{
	// data
	u.num_bodies = nb;
	u.num_step = ns;
	u.alloc();

	/*printf("init\n");*/

	MPI_Init(&argc,&argv);
	MPI_Barrier(MPI_COMM_WORLD);

	int world_size;
	int world_rank;

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


	/*printf("name\n");*/
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name( processor_name, &name_len );


	// 0 rank is master

	int block_size = u.num_bodies / world_size;

	int* start = new int[world_size];
	int* end = new int[world_size];

	for(int i = 0; i < world_size; i++)
	{
		start[i] = i * block_size;

		if(i == (world_size-1))
		{
			end[i] = u.num_bodies;
		}
		else
		{
			end[i] = (i + 1) * block_size;
		}
	}

	printf("Hello world from processor %s, rank %i of %i processors, block: %i to %i\n",
			processor_name,
			world_rank,
			world_size,
			start[world_rank],
			end[world_rank]);


	MPI_Status stat;

<<<<<<< HEAD
	// initial values
	int r = 1000;

=======
	int r = 1000;

	//float density = 7874; // iron
	float density = 934; // water ice at 93 K
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77

	for(int i = 0; i < u.num_bodies; i++)
	{
		//printf("%f\n", float(rand() % r));

<<<<<<< HEAD
		u.p(0, i) = glm::vec3(float(rand() % r), float(rand() % r), float(rand() % r));
		u.v(0, i) = glm::vec3();
		// mass
		u.m(0, i) = mass;
		// radius
		u.r(0, i) = radius(u.m(0, i), density);

		u.alive(0, i) = true;
	}

	// loop
	for(int t = 1; t < u.num_step; t++)
	{
		// at this point, master has complete dataset

		// on master, do collisions for previous timestep
		if(world_rank == 0)
		{
			pairs.clear();

			int c = 1;

			while(c > 0)
			{
				c = 0;
				for(int i = 0; i < u.num_bodies; i++)
				{
					c = collide(t-1, i);
					if(c > 0) break;
				}
				//printf("c = %i\n", c);
			}

			/*
			   for(int i = 0; i < u.num_bodies; i++)
			   {
			   collide(t-1, i);
			   }
			   */
			for(auto p : pairs)
			{
			//	printf("%i %i\n", p.a_, p.b_);
			}
		}

		// send data from previous timestep to slaves
		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("send %i %i\n", world_rank, i);
				MPI_Send(
						u.body(t-1, 0),
						u.num_bodies * sizeof(Body),
						MPI_BYTE,
						i,
						1,
						MPI_COMM_WORLD);
			}
		}
		else // slave
		{
			//printf("recv %i %i\n", world_rank, 0);
			MPI_Recv(
					u.body(t-1, 0),
					u.num_bodies * sizeof(Body),
					MPI_BYTE,
					0,
					1,
					MPI_COMM_WORLD,
					&stat);
		}

		// update on each node
=======
		u.setp(0, i, glm::vec3(float(rand() % r), float(rand() % r), float(rand() % r)));
		u.setv(0, i, glm::vec3());
		// mass
		u.setm(0, i, 1e6);
		// radius
		u.setr(0, i, pow(u.m(0,i) / density * 3.0 / 4.0 / M_PI, 0.33333));
	}


	for(int t = 1; t < u.num_step; t++)
	{

>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
		for(int i = start[world_rank]; i < end[world_rank]; i++)
		{
			//printf("update %i\n", i);
			update(i, dt, t);
		}

		if(world_rank == 0)
		{
			printf("t = %4i of %4i. time = %f\n", t, u.num_step, dt * (float)t);
			/*
			   printf("t = %f p = %f %f %f v = %f %f %f p(t-1) = %f %f %f\n", dt * (float)t,
			   u.p(t,0).x, u.p(t,0).y, u.p(t,0).z,
			   u.v(t,0).x, u.v(t,0).y, u.v(t,0).z,
			   u.p(t-1,0).x, u.p(t-1,0).y, u.p(t-1,0).z);
			   */
		}

<<<<<<< HEAD
		// collect data at master
=======

>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("recv %i %i\n", world_rank, i);
				MPI_Recv(
<<<<<<< HEAD
						u.body(t, start[i]),
=======
						&u.p(t, start[i]),
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
						(end[i] - start[i]) * sizeof(Body),
						MPI_BYTE,
						i,
						1,
						MPI_COMM_WORLD,
						&stat);
			}
		}
		else // slave
		{
			//printf("send %i %i\n", world_rank, 0);
			MPI_Send(
<<<<<<< HEAD
					u.body(t, start[world_rank]),
=======
					&u.p(t, start[world_rank]),
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
					(end[world_rank] - start[world_rank]) * sizeof(Body),
					MPI_BYTE,
					0,
					1,
					MPI_COMM_WORLD);
		}

<<<<<<< HEAD
=======
		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("send %i %i\n", world_rank, i);
				MPI_Send(
						&u.p(t, 0),
						u.num_bodies * sizeof(Body),
						MPI_BYTE,
						i,
						1,
						MPI_COMM_WORLD);
			}
		}
		else // slave
		{
			//printf("recv %i %i\n", world_rank, 0);
			MPI_Recv(
					&u.p(t,0),
					u.num_bodies * sizeof(Body),
					MPI_BYTE,
					0,
					1,
					MPI_COMM_WORLD,
					&stat);
		}
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77


	}

	if(world_rank == 0)
	{
		u.write();

		printf("write\n");

		printf("collisions: %i\n", num_collision);
<<<<<<< HEAD
		//printf("min_d:      %f\n", min_d);
		//printf("radius:     %f\n", u.r(0,0));
		//

		u.list(u.num_step-1);

=======
		printf("min_d:      %f\n", min_d);
		printf("radius:     %f\n", u.r(0,0));
>>>>>>> d01d9a711bebb92e0cc29e47bf901a6575265c77
	}



	MPI_Finalize();

	return 0;
}


