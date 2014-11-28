#include <cstdlib>
#include <mpi.h>
#include <glm/glm.hpp>

#include "nbody.hpp"

Universe u;

float G = 6.674e-11;
float dt = 0.01;

void	update(int me, float dt, int t)
{
	glm::vec3 a;

	glm::vec3 r;
	float d;

	for(int i = 0; i < me; i++)
	{
		r = u.p(t-1, i) - u.p(t-1, me);
		d = r.length();
		a += r * (float)(G * u.m(t-1, i) / pow(d,3.0f));
	}
	for(int i = me + 1; i < u.num_bodies; i++)
	{
		r = u.p(t-1, i) - u.p(t-1, me);
		d = r.length();
		a += r * (float)(G * u.m(t-1, i) / pow(d,3.0f));
	}

	u.v(t, me) = u.v(t-1, me) + a * dt;
	u.p(t, me) = u.p(t-1, me) + u.v(t, me) * dt;
	u.m(t, me) = u.m(t-1, me);

	if(me == 0)
	{
		printf("%f %f %f\n", u.p(t, me).x, u.p(t, me).y, u.p(t, me).z);
	}
}


int main(int argc, char ** argv)
{
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

	// data
	u.num_bodies = 100;
	u.num_step = 100;
	u.alloc();

	MPI_Status stat;
	
	int r = 1000;

	for(int i = 0; i < u.num_bodies; i++)
	{
		printf("%f\n", float(rand() % r));

		u.p(0, i) = glm::vec3(float(rand() % r), float(rand() % r), float(rand() % r));
		u.v(0, i) = glm::vec3();
		u.m(0, i) = 10;
		//velocity[i] = glm::vec3(float(rand()), float(rand()), float(rand()))
	}


	for(int t = 1; t < u.num_step; t++)
	{
		if(world_rank == 0)
		{
			printf("t = %f\n", dt * (float)t);
		}

		for(int i = start[world_rank]; i < end[world_rank]; i++)
		{
			//printf("update %i\n", i);
			update(i, dt, t);
		}


		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("recv %i %i\n", world_rank, i);
				MPI_Recv(
						&u.p(t, start[i]),
						(end[i] - start[i]) * 3,
						MPI_FLOAT,
						i,
						1,
					       	MPI_COMM_WORLD,
						&stat);
				MPI_Recv(
						&u.v(t, start[i]),
						(end[i] - start[i]) * 3,
						MPI_FLOAT,
						i,
						1,
					       	MPI_COMM_WORLD,
						&stat);
				MPI_Recv(
						&u.m(t, start[i]),
						end[i] - start[i],
						MPI_FLOAT,
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
					&u.p(t, start[world_rank]),
					(end[world_rank] - start[world_rank]) * 3,
					MPI_FLOAT,
					0,
					1,
					MPI_COMM_WORLD);
			MPI_Send(
					&u.v(t, start[world_rank]),
					(end[world_rank] - start[world_rank]) * 3,
					MPI_FLOAT,
					0,
					1,
					MPI_COMM_WORLD);
			MPI_Send(
					&u.m(t, start[world_rank]),
					end[world_rank] - start[world_rank],
					MPI_FLOAT,
					0,
					1,
					MPI_COMM_WORLD);
		}

		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("send %i %i\n", world_rank, i);
				MPI_Send(
						&u.p(t, 0),
						u.num_bodies * 3,
						MPI_FLOAT,
						i,
						1,
						MPI_COMM_WORLD);
				MPI_Send(
						&u.v(t, 0),
						u.num_bodies * 3,
						MPI_FLOAT,
						i,
						1,
						MPI_COMM_WORLD);
				MPI_Send(
						&u.m(t, 0),
						u.num_bodies,
						MPI_FLOAT,
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
					u.num_bodies * 3,
					MPI_FLOAT,
					0,
					1,
					MPI_COMM_WORLD,
					&stat);
			MPI_Recv(
					&u.v(t,0),
					u.num_bodies * 3,
					MPI_FLOAT,
					0,
					1,
					MPI_COMM_WORLD,
					&stat);
			MPI_Recv(
					&u.m(t,0),
					u.num_bodies,
					MPI_FLOAT,
					0,
					1,
					MPI_COMM_WORLD,
					&stat);
		}


	}

	if(world_rank == 0)
	{
		u.write();

		printf("write\n");
	}


	MPI_Finalize();

	return 0;
}


