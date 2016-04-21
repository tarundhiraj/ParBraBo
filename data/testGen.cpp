#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
	time_t t;
	FILE *outputFile = fopen(argv[1],"w");
	int noOfJobs = atoi(argv[2]);

	int maxVal = atoi(argv[3]);

	fprintf(outputFile, "%d\n", noOfJobs);

	srand((unsigned) time(&t));

	for(int i= 0 ; i < noOfJobs; i++) {
		for(int j =0; j < noOfJobs; j++) {
			fprintf(outputFile, "%d ", rand() % maxVal);
		}
		fprintf(outputFile, "\n" );
	}

	fclose(outputFile);

	return 0;
}