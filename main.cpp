#include <iostream>
#include<string>
#include "AdjacencyMatrixGraph/graphAM.cpp"
#include "BruteForce/bruteForce.cpp"
#include "HeldKarp/heldKarp.cpp"
#include "Timer/timer.cpp"

using namespace std;

float unitFactor = 1.0f; //seconds
string unit = " seconds";

void runBruteForce(GraphAM *graph, int src){
    float time = 0;
    Timer timer;
    int *result = bruteForce(graph, src);
    time += timer.getTime().count() * unitFactor;
    int shortestPathWeight = result[0];
    int lengthOfRoute = result[1];

    cout<<" Shortest path: ";
    for(int i = 0; i < lengthOfRoute; i++){
        cout<<result[i + 2]<<" ";
    }
    cout<<endl<<" Weight: "<<shortestPathWeight<<endl;
    cout<<fixed<<setprecision(4)<<" Brute force took: "<<time<<unit<<endl<<endl;
}

void runHeldKarp(GraphAM *graph){
    float time = 0;
    Timer timer;
    int answer = heldKarp(graph);
    time += timer.getTime().count() * unitFactor;
    cout<<" Weight: "<<answer<<endl;
    cout<<fixed<<setprecision(4)<<" Held-Karp took: "<<time<<unit<<endl<<endl;
}

int main(){
    GraphAM *graph = new GraphAM();

    graph->fillGraphFromFile("instances/m10.atsp");
    //graph->printGraph();

    runBruteForce(graph, 0);

    runHeldKarp(graph);

    delete graph;

    return 0;
}
