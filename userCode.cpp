#include "userCode.h"
#include <stdio.h>
#include <set>
#include <vector>

#define INF 99999999
using namespace std;


/* 	For simplacity please consider the following Node structure 
	offered by framework to work on
*/
typedef struct {
		long bound;
		long actualCost;
		set<long> jobDone;
		set<long> personDone;
		vector <long> assignment;
} Node;

extern int limit;
extern set <Node *> liveNodes;
extern long globalBound;
extern vector <long> currentSol;
extern long **inputArray;

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
				liveNodes.insert(sol);
				//recursionJob(sol,job,limit);
			}
			else {
				printf("Branch pruned GlobalBound : %ld, SolutionBound : %ld \n",globalBound, sol->bound );
			}
		}
}


void initialize(void * root) {
	Node *RootSol = (Node *)root;
	RootSol->bound = 0;
	RootSol->actualCost = 0;
	RootSol->assignment.resize(limit);
}

void branch(void * SubPro) {
	Node *SubProNode = (Node *)SubPro;
	long nextJob = 0;
	for (long i = 0; i < limit ; i++) {
		if(SubProNode->jobDone.find(i) == SubProNode->jobDone.end()) {
			nextJob = i;
			break;
		}
	}
	recursionJob(SubProNode,nextJob,limit);
}

void evaluate(void * SubPro) {

}

