#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
	MPI_Init(&argc, &argv);
	int rank;
	int data;


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	

	printf("Hello, I am a Slave!!!\nMy rank is %d", rank);
	
	MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	printf("Successfully Received the data %d\n", data);
	

	MPI_Finalize();
	return 0;
}