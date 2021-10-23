#include <iostream>
#include "AdjacencyMatrixGraph/graphAM.cpp"

using namespace std;

int main(){
    GraphAM *graphAM = new GraphAM();

    graphAM->fillGraphFromFile();
    graphAM->printGraph();

    return 0;
}
