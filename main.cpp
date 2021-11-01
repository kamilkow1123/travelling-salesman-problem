#include <iostream>
#include "AdjacencyMatrixGraph/graphAM.cpp"
#include "BruteForce/bruteForce.cpp"
#include "Timer/timer.cpp"

using namespace std;

float unitFactor = 1.0f; //seconds
string unit = " seconds";

void runBruteForce(GraphAM *graph){
    float time = 0;
    Timer timer;
    int *result = bruteForce(graph, 0);
    time += timer.getTime().count() * unitFactor;
    int shortestPathWeigh = result[0];
    int lengthOfRoute = result[1];

    cout<<"Shortest path: ";
    for(int i = 0; i < lengthOfRoute; i++){
        cout<<result[i + 2]<<" ";
    }
    cout<<endl<<"Weigh: "<<shortestPathWeigh<<endl;
    cout<<"Brute force took: "<<time<<unit<<endl;
}

int main(){
    GraphAM *graph = new GraphAM();

    graph->fillGraphFromFile("data/m11.atsp");
    //graph->printGraph();

    runBruteForce(graph);

    return 0;
}
