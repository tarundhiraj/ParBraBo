#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <set>
#include <vector>


using namespace std;
#define INF 99999999

long globalBound = INF;
vector <long> currentSol;
long **inputArray;

typedef struct {
		long bound;
		long actualCost;
		set<long> jobDone;
		set<long> personDone;
		vector <long> assignment;
} Node;
	
void recursionPerson(Node *sol, long job, long person, int limit);

	void recursionJob(Node *sol, long job, int limit) {
		sol->jobDone.insert(job);

		for(long i = 0;  i < limit; i++) {
			if(sol->personDone.find(i) == sol->personDone.end()){
				// create new Node which has previous details
				Node * newSol = new Node();
				newSol->bound = sol->bound;
				newSol->actualCost = sol->actualCost;
				newSol->assignment.resize(limit); 
				for(auto job : sol->jobDone) {
					newSol->jobDone.insert(job);
				}
				for(auto person : sol->personDone) {
					newSol->personDone.insert(person);
				}

				for (int it = 0; it < limit ; it++) {
					newSol->assignment[it] = sol->assignment[it];
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
		sol->assignment[job] = person;

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
				currentSol = sol->assignment;
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

	Node *sol = new Node();
	sol->bound = 0;
	sol->actualCost = 0;
	sol->assignment.resize(noOfJob);
	recursionJob(sol,0,noOfJob);

	printf("solution : %ld\n",globalBound );
	long size = currentSol.size();
	for (long it = 0; it < size ; it++) {
		printf("JOB : %ld assigned to PERSON : %ld\n", it, currentSol[it]);
	}

	return 0;
}