#include "parbrabo.h"

void print_int(int rank, long x){
	printf("Rank: %d prints %ld\n", rank, x);
}


int main(int argc, char** argv){
	long data = 10;
	PBB_init(&argc, &argv);
	invoke_function((void*)data, &print_int);
	PBB_finalize();
	return 0;
}