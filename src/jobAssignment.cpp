#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "userCode.h"

using namespace std;


long globalBound = INF;
vector <long> currentSol;
long **inputArray;
int limit;

//Framework Code starts

set <Node *> liveNodes;

void insertLiveNode(Node *solution) {
	if(solution->bound < globalBound) {
		liveNodes.insert(solution);
	} //else { printf("Branch pruned due to bound value\n");
//	}
}

void updateBestSolution(Node *solution) {
	if(globalBound >  solution->bound) {
		globalBound = solution->bound;
		currentSol = solution->assignment;
	}
}
	
void * chooseBestLiveNode() {

	// Following code implements best first
	// int minBound = INF;
	// Node * liveNode = NULL;
	// for (auto sol : liveNodes) {
	// 	if(minBound > sol->bound) {
	// 		minBound = sol->bound;
	// 		liveNode = sol;
	// 	}
	// }
	// liveNodes.erase(liveNode);
	// return (void *)liveNode;
	
	// Following code implements depth first 
	// depth first results into more prunning of branches
	Node *liveNode = NULL;
	for (auto sol : liveNodes) {
		if(liveNode == NULL) {
			liveNode = sol;
		} else {
			if(liveNode->yDone.size() < sol->yDone.size()) {
				liveNode = sol;
			}
		}
	}
	liveNodes.erase(liveNode);
	return (void *)liveNode;
}	


// void recursionPerson(Node *sol, long job, long person, int limit);

// 	void recursionJob(Node *sol, long job, int limit) {
// 		sol->yDone.insert(job);

// 		for(long i = 0;  i < limit; i++) {
// 			if(sol->xDone.find(i) == sol->xDone.end()){
// 				// create new Node which has previous details
// 				Node * newSol = new Node();
// 				newSol->bound = sol->bound;
// 				newSol->actualCost = sol->actualCost;
// 				newSol->assignment.resize(limit); 
// 				for(auto job : sol->yDone) {
// 					newSol->yDone.insert(job);
// 				}
// 				for(auto person : sol->xDone) {
// 					newSol->xDone.insert(person);
// 				}

// 				for (int it = 0; it < limit ; it++) {
// 					newSol->assignment[it] = sol->assignment[it];
// 				}

// 				if(newSol->bound < globalBound){
// 					recursionPerson(newSol,job,i,limit);
// 				} else {
// 					printf("Branch pruned GlobalBound : %ld, SolutionBound : %ld \n",globalBound, newSol->bound );
// 				}
// 			}
// 		}
// 	}

// 	void recursionPerson(Node *sol, long job, long person, int limit) {
// 		sol->xDone.insert(person);
// 		sol->actualCost = sol->actualCost + inputArray[job][person];
// 		sol->bound = sol->actualCost;
// 		sol->assignment[job] = person;

// 		for(long jobIt = 0; jobIt < limit ; jobIt++) {
// 			if (sol->yDone.find(jobIt) == sol->yDone.end() ) {
// 				long minJob2Person = INF;
// 				for(long personIt = 0; personIt < limit; personIt++ ) {
// 					if(sol->xDone.find(personIt) == sol->xDone.end()) {
// 						if(minJob2Person > inputArray[jobIt][personIt]) {
// 							minJob2Person = inputArray[jobIt][personIt];
// 						}
// 					}
// 				}
// 				if(minJob2Person != INF) {
// 						sol->bound += minJob2Person;
// 				}
// 			}
// 		}

// 		if( sol->yDone.size() == limit){
// 			if( globalBound > sol->bound) {
// 				printf("Solution found : %ld \n", sol->bound);
// 				globalBound = sol->bound;
// 				currentSol = sol->assignment;
// 			}
// 		} else {
// 			job++;
// 			if(sol->bound < globalBound) {

// 				recursionJob(sol,job,limit);
// 			}
// 			else {
// 				printf("Branch pruned GlobalBound : %ld, SolutionBound : %ld \n",globalBound, sol->bound );
// 			}
// 		}
// }
	

int main(int argc, char **argv) {

	FILE *inputFILE = fopen(argv[1],"r");
	char *line = NULL;
	size_t len ;
	ssize_t read;
	int noOfJob = 0;
	
	if( inputFILE ==  NULL)
		exit(-2);

	fscanf(inputFILE, "%d", &noOfJob);
	limit = noOfJob;
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
	//sol->bound = 0;
	//sol->actualCost = 0;
	//sol->assignment.resize(noOfJob);
	//recursionJob(sol,0,noOfJob);

	initialize((void *)sol);
	liveNodes.insert(sol);

	while(!liveNodes.empty()) {
		printf("liveNodes size : %ld\n", liveNodes.size());
		void * n = chooseBestLiveNode();
		branch(n);
	}

	printf("solution : %ld\n",globalBound );
	long size = currentSol.size();
	for (long it = 0; it < size ; it++) {
		printf("JOB : %ld assigned to PERSON : %ld\n", it, currentSol[it]);
	}

	return 0;
}