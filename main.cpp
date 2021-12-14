#include <iostream>
#include <string>
#include <conio.h>
#include <float.h>
#include "AdjacencyMatrixGraph/graphAM.cpp"
#include "BruteForce/bruteForce.cpp"
#include "HeldKarp/heldKarp.cpp"
#include "SimulatedAnnealing/simulatedAnnealing.cpp"
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

void runSimulatedAnnealing(GraphAM *graph){
    float time = 0;
    pair<vector<int>, int> answer;

    Timer timer;
    answer = solveSA(graph, 0.999, 1000);
    time += timer.getTime().count() * unitFactor;

    int weight = answer.second;
    string path = "";
    vector<int>::iterator it = answer.first.begin();

    while (it != answer.first.end())
    {
        path += to_string(*it);
        path += " ";
        it++;
    }

    int optimalWeight = graph->getOptimalValue();
    cout<<" Weight: "<<weight<<endl;
    cout<<" Optimal weight: "<<optimalWeight<<endl;
    cout<<fixed<<setprecision(4)<<" Error: "<<double(100 * (weight - optimalWeight))/optimalWeight<<"%"<<endl;
    cout<<" Path: "<<path<<endl;
    cout<<" Simulated annealing took: "<<time<<unit<<endl<<endl;
}

int main(){
    GraphAM *graph = new GraphAM();

    // graph->fillGraphFromFile("instances/m10.atsp");
    // graph->fillGraphFromFile("instances/gr17.tsp");
    // graph->fillGraphFromFile("instances/gr48.tsp");
    graph->fillGraphFromFile("instances/gr120.tsp");
    // graph->fillGraphFromFile("instances/gr137.tsp");
    // graph->fillGraphFromFile("instances/gr202.tsp");
    // graph->fillGraphFromFile("instances/gr229.tsp");
    // graph->fillGraphFromFile("instances/rbg443.atsp");
    // graph->fillGraphFromFile("instances/rbg403.atsp");

    //graph->printGraph();

    //runBruteForce(graph, 0);

    //runHeldKarp(graph);

    runSimulatedAnnealing(graph);

    delete graph;

    cout<<endl<<" Press any key to exit";
    getch();

    return 0;
}
