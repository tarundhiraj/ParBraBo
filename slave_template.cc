#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>


using namespace std;

int main(int argc, char** argv){

	MPI_Init(&argc, &argv);
	
	
	int rank, size, count;
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("Waiting for the Item to recieve\n");

	MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

	MPI_Get_count(&status, MPI_INT, &count);
	printf("Received Count: %d\n", count);

	if(count > 0){
		int *recv_data = (int*)malloc(sizeof(int) * count);
		MPI_Recv(recv_data, count, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		for_each(recv_data, recv_data + count , [](int x){cout << x << " " ; });
		cout << endl;
		
		free(recv_data);
	}

	

	MPI_Finalize();
	return 0;
}