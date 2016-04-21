#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char** argv){
	int rank, thread_support_provided;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &thread_support_provided);
	if(thread_support_provided < MPI_THREAD_FUNNELED){
		printf("Specified Thread Level not supported!!");
		exit(1);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	#pragma omp parallel
	{
		printf("Rank: %d\t Thread: %d\n", rank, omp_get_thread_num());
	}


	MPI_Finalize();

	return 0;
}