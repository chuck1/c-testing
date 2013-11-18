#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main( int argc, char** argv )
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
	
	printf("Hello world from processor %s, rank %i of %i processors\n", processor_name, world_rank, world_size);


	MPI_Finalize();


}


