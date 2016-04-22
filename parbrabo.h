#ifndef _PARBRABO_H
#define _PARBRABO_H
#endif


#include <stdio.h>
#include <iostream>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>

using namespace std;



//Function to initialize the framework
void PBB_init(int *argc, char*** argv){
	int thread_support_provided;

	MPI_Init_thread(argc, argv, MPI_THREAD_FUNNELED, &thread_support_provided);
	if(thread_support_provided < MPI_THREAD_FUNNELED){
		printf("MPI_THREAD_FUNNELED NOT SUPPORTED!!\n");
		exit(1);
	}
}

void invoke_function(void* data, void (*func)(int,long)){
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	long d = (long)data;

	func(rank,d);

}


//Function to finalize the framework
void PBB_finalize(){

	MPI_Finalize();

}