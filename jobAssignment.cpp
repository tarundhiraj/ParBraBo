#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <set>
#include <vector>


using namespace std;
#define INF 99999999

long globalBound = INF;
long **inputArray;

typedef struct {
		long bound;
		long actualCost;
		set<long> jobDone;
		set<long> personDone;
		vector <long> assignment;
} Node;
	
	// void findBound(Node *SubProblem, long start_X, long start_Y, long limit) {
	// 	SubProblem->actualCost = SubProblem->actualCost + inputArray[start_X][start_Y];
	// 	SubProblem->bound = SubProblem->actualCost;
	// 	SubProblem->doneX.insert(start_X);
	// 	SubProblem->doneY.insert(start_Y);
	// 	SubProblem->assignment[start_X] = start_Y;
	// 	for(int ix = 0 ; ix < limit; ix++) {
	// 		if(SubProblem->doneX.find(ix) == SubProblem->doneX.end()) {
	// 			int minY = INF;
	// 			for(int iy = 0; iy < limit; iy++){
	// 				if(SubProblem->doneY.find(iy) == SubProblem->doneY.end()){
	// 					if( minY > inputArray[ix][iy]) {
	// 						minY = inputArray[ix][iy];
	// 					}
	// 				}
	// 			}
	// 			if(minY != INF){
	// 				//printf(" minY : %d\n", minY);
	// 				SubProblem->bound = SubProblem->bound + minY;
	// 			}
	// 		}
	// 	}
	// 	if(SubProblem->doneX.size() == limit ) {
	// 		if( globalBound >  SubProblem->bound) {
	// 			globalBound = SubProblem->bound;
	// 			printf("New solution value found : %ld\n", SubProblem->bound);
	// 			// for( auto mapEntry : SubProblem->assignment) {
	// 			// 	printf("JOB %ld ==> WORKER %ld\n", mapEntry.first, mapEntry.second );
	// 			// }
	// 		}
	// 	}
	// }

	// void recursion(Node *SubProblem, long start_X,long limit) {
	// 	start_X++;
	// 	if(start_X < limit) {
	// 		printf("Recursive Call with start_X : %ld\n", start_X );
	// 		for(int iy = 0; iy < limit ; iy++) {
	// 			if(SubProblem->doneY.find(iy) == SubProblem->doneY.end()) {
	// 				Node *SubPro = new Node();
	// 				memcpy(SubPro,SubProblem, sizeof(Node));
	// 				findBound(SubPro,start_X,iy,limit);
	// 				if(SubPro->bound < globalBound) 
	// 					recursion(SubPro,start_X,limit);
	// 				else
	// 					printf("Branch pruned globalBound : %ld , solution.bound : %ld \n", globalBound, SubPro->bound);
	// 			}
	// 		}
	// 	}
	// }

	// void start(long start_X, long limit) {		
	// 		for(int i = 0; i < limit ; i++ ) {
	// 				printf("findBound called with values start_X : %ld start_Y : %d limit : %ld\n", start_X,i,limit );
	// 				Node *SubPro = new Node();
	// 				findBound(SubPro,start_X,i,limit);
	// 				if(SubPro->bound < globalBound) {
	// 					recursion(SubPro,start_X,limit);
	// 				}
	// 				else
	// 					printf("Branch pruned globalBound : %ld , solution.bound : %ld \n", globalBound, SubPro->bound);
	// 		}
	// 		// start_X++;
	// 		// if(start_X < limit) {
	// 		// 	printf("Fresh call with value start_X : %ld limit : %ld \n", start_X,limit);
	// 		// 	start(start_X,limit);
	// 		// }		
	// }
void recursionPerson(Node *sol, long job, long person, int limit);

	void recursionJob(Node *sol, long job, int limit) {
		sol->jobDone.insert(job);

		for(long i = 0;  i < limit; i++) {
			if(sol->personDone.find(i) == sol->personDone.end()){
				// create new Node which has previous details
				Node * newSol = new Node();
				newSol->bound = sol->bound;
				newSol->actualCost = sol->actualCost;
				for(auto job : sol->jobDone) {
					newSol->jobDone.insert(job);
				}
				for(auto person : sol->personDone) {
					newSol->personDone.insert(person);
				}
				if(newSol->bound < globalBound){
					recursionPerson(newSol,job,i,limit);
				} else {
					printf("Branch pruned GlobalBound : %ld, SolutionBound : %ld \n",globalBound, newSol->bound );
				}
			}
		}
	}

	void recursionPerson(Node *sol, long job, long person, int limit) {
		sol->personDone.insert(person);
		sol->actualCost = sol->actualCost + inputArray[job][person];
		sol->bound = sol->actualCost;

		for(long jobIt = 0; jobIt < limit ; jobIt++) {
			if (sol->jobDone.find(jobIt) == sol->jobDone.end() ) {
				long minJob2Person = INF;
				for(long personIt = 0; personIt < limit; personIt++ ) {
					if(sol->personDone.find(personIt) == sol->personDone.end()) {
						if(minJob2Person > inputArray[jobIt][personIt]) {
							minJob2Person = inputArray[jobIt][personIt];
						}
					}
				}
				if(minJob2Person != INF) {
						sol->bound += minJob2Person;
				}
			}
		}

		if( sol->jobDone.size() == limit){
			if( globalBound > sol->bound) {
				printf("Solution found : %ld \n", sol->bound);
				globalBound = sol->bound;
			}
		} else {
			job++;
			if(sol->bound < globalBound) {

				recursionJob(sol,job,limit);
			}
			else {
				printf("Branch pruned GlobalBound : %ld, SolutionBound : %ld \n",globalBound, sol->bound );
			}
		}
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
	//printf("%d", noOfJob );
	inputArray = (long **) malloc(noOfJob * sizeof(long *));
	
	int temp = 0;
	int i = 0;
	int j = 0;

	for(i = 0; i < noOfJob ; i++) {
		inputArray[i] = (long *)malloc(noOfJob * sizeof(long));
		for(j = 0 ; j < noOfJob ;j++) {
			fscanf(inputFILE, "%ld ", &inputArray[i][j]);
			printf("%ld ", inputArray[i][j] );
		}
		printf("\n"); 
	}

	// char *token;
	// char array[2*noOfJob];
	// getline(&line, &len, inputFILE);
	// while((read = getline(&line, &len, inputFILE)) != -1) {
	// 	j = 0;
	// 	inputArray[i] = (long *)malloc(noOfJob * sizeof(long));
	// 	char *str;
	// 	for(int k = 0; k < read; k++) {
	// 		char c = line[k];

	// 		if (isspace(c) == 0) {
	// 			char *endPtr;		
	// 			long val = strtol(str, &endPtr, 10);
	// 			inputArray[i][j] = val;
	// 		//	printf("%ld ", inputArray[i][j] );
	// 			j++;
	// 		} else {
	// 			str

	// 		}
	// 	}
	// 	//printf("\n");
	// 	i++;
	// }
	
	// for(int i =0 ; i < noOfJob; i++) {
	// 	for(int j =0; j< noOfJob ; j++) {
	// 		printf("%ld ", inputArray[i][j]);
	// 	}
	// 	printf("\n");
	// }

	Node *sol = new Node();
	sol->bound = 0;
	sol->actualCost = 0;
	recursionJob(sol,0,noOfJob);

	printf("solution : %ld\n",globalBound );
	

	return 0;
}