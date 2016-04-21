#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int rank;
	int data = 10;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	
	printf("Hello, I am the master!!!\nMy rank is %d", rank);
	//printf("Broadcasting the data to the Slave Processes\n");
	MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//printf("Successfully Broadcasted the data to the Slave Processes\n");


	MPI_Finalize();
	return 0;
}