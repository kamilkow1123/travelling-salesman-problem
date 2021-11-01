#include <iostream>
#include "AdjacencyMatrixGraph/graphAM.cpp"
#include "BruteForce/bruteForce.cpp"

using namespace std;

int main(){
    GraphAM *graphAM = new GraphAM();

    graphAM->fillGraphFromFile("data/m8.atsp");
    graphAM->printGraph();

    int result = bruteForce(graphAM, 0);

    return 0;
}
