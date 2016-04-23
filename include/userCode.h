#ifndef USERCODE_H
#define USERCODE_H

#include <stdio.h>
#include "dataStructures.h"

// Following definitions will be provided by the framework -------------
extern long globalBound;
extern vector <long> currentSol;
extern long **inputArray;
extern int limit;
extern set <Node *> liveNodes;

extern void insertLiveNode(Node *solution);
extern void updateBestSolution(Node *solution);
// Framework definitions ends here -------------------------------------

void initialize(void * root);
void branch(void * SubPro);
void evaluate(void * SubPro);

#endif