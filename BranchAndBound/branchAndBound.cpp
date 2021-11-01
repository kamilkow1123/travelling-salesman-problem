#include<iostream>
#include<climits>
#include<algorithm>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

int* branchAndBound(GraphAM *graph, int src){
    int numOfVer = graph->getNumOfVertexes();
    if(src >= numOfVer || src < 0) return nullptr;
}