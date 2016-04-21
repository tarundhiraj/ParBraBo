#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>


using namespace std;

int main(int argc, char** argv){

	MPI_Init(&argc, &argv);
	
	int data[] = {0,1,2,3,4,5,6,7,8,9};
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//printf("Master Process..\nInitiating communication with the slaves!\n");
	printf("The size of the comm world is %d", size);
	for(int i = 1 ; i < size ; ++i){
		MPI_Send(&data, 10, MPI_INT, i, 0, MPI_COMM_WORLD);
	}

	printf("Sent all the items to the slaves!\n");

	MPI_Finalize();
	return 0;
}