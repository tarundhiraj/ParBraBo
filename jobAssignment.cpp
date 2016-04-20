#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <set>
#include <map>

using namespace std;
#define INF 99999999

long globalBound = INF;
long **inputArray;

typedef struct {
		long bound;
		long actualCost;
		set<long> doneX;
		set<long> doneY;
		map <long,long> assignment;
} Node;
	
	void findBound(Node *SubProblem, long start_X, long start_Y, long limit) {
		SubProblem->actualCost = SubProblem->actualCost + inputArray[start_X][start_Y];
		SubProblem->bound = SubProblem->actualCost;
		SubProblem->doneX.insert(start_X);
		SubProblem->doneY.insert(start_Y);
		SubProblem->assignment[start_X] = start_Y;
		for(int ix = 0 ; ix < limit; ix++) {
			if(SubProblem->doneX.find(ix) == SubProblem->doneX.end()) {
				int minY = INF;
				for(int iy = 0; iy < limit; iy++){
					if(SubProblem->doneY.find(iy) == SubProblem->doneY.end()){
						if( minY > inputArray[ix][iy]) {
							minY = inputArray[ix][iy];
						}
					}
				}
				if(minY != INF){
					//printf(" minY : %d\n", minY);
					SubProblem->bound = SubProblem->bound + minY;
				}
			}
		}
		if(SubProblem->doneX.size() == limit ) {
			if( globalBound >  SubProblem->bound) {
				globalBound = SubProblem->bound;
				printf("New solution value found : %ld\n", SubProblem->bound);
				// for( auto mapEntry : SubProblem->assignment) {
				// 	printf("JOB %ld ==> WORKER %ld\n", mapEntry.first, mapEntry.second );
				// }
			}
		}
	}

	void recursion(Node *SubProblem, long start_X,long limit) {
		start_X++;
		if(start_X < limit) {
			printf("Recursive Call with start_X : %ld\n", start_X );
			for(int iy = 0; iy < limit ; iy++) {
				if(SubProblem->doneY.find(iy) == SubProblem->doneY.end()) {
					Node *SubPro = new Node();
					memcpy(SubPro,SubProblem, sizeof(Node));
					findBound(SubPro,start_X,iy,limit);
					if(SubPro->bound < globalBound) 
						recursion(SubPro,start_X,limit);
					else
						printf("Branch pruned globalBound : %ld , solution.bound : %ld \n", globalBound, SubPro->bound);
				}
			}
		}
	}

	void start(long start_X, long limit) {		
			for(int i = 0; i < limit ; i++ ) {
					printf("findBound called with values start_X : %ld start_Y : %d limit : %ld\n", start_X,i,limit );
					Node *SubPro = new Node();
					findBound(SubPro,start_X,i,limit);
					if(SubPro->bound < globalBound) {
						recursion(SubPro,start_X,limit);
					}
					else
						printf("Branch pruned globalBound : %ld , solution.bound : %ld \n", globalBound, SubPro->bound);
			}
			// start_X++;
			// if(start_X < limit) {
			// 	printf("Fresh call with value start_X : %ld limit : %ld \n", start_X,limit);
			// 	start(start_X,limit);
			// }		
	}

int main(int argc, char **argv) {

	FILE *inputFILE = fopen(argv[1],"r");
	char *line = NULL;
	size_t len ;
	ssize_t read;
	int noOfJob = 0;
	

	

	if( inputFILE ==  NULL)
		exit(-2);

	fscanf(inputFILE, "%d", &noOfJob);
	printf("%d", noOfJob );
	inputArray = (long **) malloc(noOfJob * sizeof(long *));
	int temp = 0;
	int i = 0;
	int j = 0;
	char *token;
	char array[2*noOfJob];
	getline(&line, &len, inputFILE);
	while((read = getline(&line, &len, inputFILE)) != -1) {
		j = 0;
		inputArray[i] = (long *)malloc(noOfJob * sizeof(long));
		for(int k = 0; k < read; k++) {
			char c = line[k];
			if (isspace(c) == 0) {
				char *endPtr;
				long val = strtol(&c, &endPtr, 10);
				inputArray[i][j] = val;
				printf("%ld ", inputArray[i][j] );
				j++;
			}
		}
		printf("\n");
		i++;
	}
	
	for(int i =0 ; i < noOfJob; i++) {
		for(int j =0; j< noOfJob ; j++) {
			printf("%ld ", inputArray[i][j]);
		}
		printf("\n");
	}
	
	
	 //Node *Solution = NULL;
	// SubProblem->bound = 0;
	// SubProblem->actualCost = 0;

	start(0,noOfJob);
	printf("Global Bound : %ld \n",globalBound);
	

	return 0;
}