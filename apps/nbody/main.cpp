#include <cstdlib>
#include <mpi.h>
#include <glm/glm.hpp>

glm::vec3* position = 0;
glm::vec3* velocity = 0;
float* mass = 0;
int num_bodies = 100;
float G = 6.674e-11;

void	update(int me, float dt)
{
	glm::vec3 a;

	glm::vec3 r;
	float d;

	for(int i = 0; i < me; i++)
	{
		r = position[i] - position[me];
		d = r.length();
		a += r * (float)(G * mass[i] / pow(d,3.0f));
	}
	for(int i = me + 1; i < num_bodies; i++)
	{
		r = position[i] - position[me];
		d = r.length();
		a += r * (float)(G * mass[i] / pow(d,3.0f));
	}

	velocity[me] += a * dt;
	position[me] += velocity[me] * dt;
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

	int block_size = num_bodies / world_size;
	
	int* start = new int[world_size];
	int* end = new int[world_size];

	for(int i = 0; i < world_size; i++)
	{
		start[i] = i * block_size;
		
		if(i == (world_size-1))
		{
			end[i] = num_bodies;
		}
		else
		{
			end[i] = (i + 1) * block_size;
		}
	}

	printf("Hello world from processor %s, rank %i of %i processors, block: %i to %i\n", processor_name, world_rank, world_size, start[world_rank], end[world_rank]);

	// data
	position = new glm::vec3[num_bodies];
	velocity = new glm::vec3[num_bodies];
	mass = new float[num_bodies];

	MPI_Status stat;
	


	for(int i = 0; i < num_bodies; i++)
	{
		position[i] = glm::vec3(float(rand()), float(rand()), float(rand()));
		velocity[i] = glm::vec3();
		mass[i] = 1000;
		//velocity[i] = glm::vec3(float(rand()), float(rand()), float(rand()))
	}

	float dt = 1.0;

	for(int t = 0; t < 100; t++)
	{
		if(world_rank == 0)
		{
			printf("t = %f\n", dt * (float)t);
		}

		for(int i = start[world_rank]; i < end[world_rank]; i++)
		{
			//printf("update %i\n", i);
			update(i, dt);
		}


		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("recv %i %i\n", world_rank, i);
				MPI_Recv(&position[start[i]], end[i] - start[i], MPI_FLOAT, i, 1, MPI_COMM_WORLD, &stat);
			}
		}
		else // slave
		{
			//printf("send %i %i\n", world_rank, 0);
			MPI_Send(&position[start[world_rank]], end[world_rank] - start[world_rank], MPI_FLOAT, 0, 1, MPI_COMM_WORLD);
		}

		if(world_rank == 0) // master
		{
			for(int i = 1; i < world_size; i++)
			{
				//printf("send %i %i\n", world_rank, i);
				MPI_Send(position, num_bodies, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
			}
		}
		else // slave
		{
			//printf("recv %i %i\n", world_rank, 0);
			MPI_Recv(position, num_bodies, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &stat);
		}


	}

	if(world_rank == 0)
	{
		FILE* fp = fopen("bodies.dat", "w");
		fwrite(&num_bodies, sizeof(int), 1, fp);
		fwrite(position, sizeof(glm::vec3), num_bodies, fp);
		fwrite(velocity, sizeof(glm::vec3), num_bodies, fp);
		fwrite(mass, sizeof(float), num_bodies, fp);
		fclose(fp);
	}

	delete[] position;
	delete[] velocity;

	MPI_Finalize();

	return 0;
}

