#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <set>
#include <vector>


using namespace std;
#define INF 99999999

/* 	For simplacity please consider the following Node structure 
	offered by framework to work on
*/
typedef struct {
		long bound;
		long actualCost;
		set<long> yDone;
		set<long> xDone;
		vector <long> assignment;
} Node;

#endif
