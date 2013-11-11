#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main( int argc, char** argv )
{
	printf("init\n");

	MPI_Init(NULL,NULL);
	
	printf("size\n");
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	printf("rank\n");
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	printf("name\n");
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name( processor_name, &name_len );
	
	printf("Hello world from processor %s, rank %i of %i processors\n", processor_name, world_rank, world_size);


	MPI_Finalize();


}


