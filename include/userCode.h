#ifndef USERCODE_H
#define USERCODE_H

#include <stdio.h>
#include "dataStructures.h"

extern long globalBound;
extern vector <long> currentSol;
extern long **inputArray;
extern int limit;
extern set <Node *> liveNodes;

void initialize(void * root);
void branch(void * SubPro);
void evaluate(void * SubPro);

#endif