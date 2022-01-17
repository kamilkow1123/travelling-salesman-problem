#include <iostream>
#include <string>
#include <conio.h>
#include <float.h>
#include "AdjacencyMatrixGraph/graphAM.cpp"
#include "BruteForce/bruteForce.cpp"
#include "HeldKarp/heldKarp.cpp"
//#include "SimulatedAnnealing/simulatedAnnealing.cpp"
//#include "TabuSearch/tabuSearch.cpp"
#include "GeneticAlgorithm/geneticAlgorithm.cpp"
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

    cout<<" Running Simulated Annealing"<<endl;
    Timer timer;
    answer = solveSA(graph, 0.9999);
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

void runTabuSearch(GraphAM *graph){
    float time = 0;
    pair<vector<int>, int> answer;

    cout<<" Running Tabu Search"<<endl;
    Timer timer;
    answer = solveTS(graph, 10000);
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
    cout<<" Tabu search took: "<<time<<unit<<endl<<endl;
}

void runGeneticAlgorithm(GraphAM *graph){
    float time = 0;
    pair<vector<int>, int> answer;

    Timer timer;
    //graph, populationSize, numOfGenerations, crossoverProb, mutationProb
    answer = solveGeneticAlgorithm(graph, 500, 30000, 0.9, 0.25);
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
    cout<<" Genetic algorithm took: "<<time<<unit<<endl<<endl;
}

int main(){
    GraphAM *graph = new GraphAM();

    // graph->fillGraphFromFile("instances/m6.atsp");
    // graph->fillGraphFromFile("instances/m10.atsp");
    // graph->fillGraphFromFile("instances/gr17.tsp");
    // graph->fillGraphFromFile("instances/gr24.tsp");
    // graph->fillGraphFromFile("instances/ftv38.atsp");
    // graph->fillGraphFromFile("instances/gr48.tsp");
    // graph->fillGraphFromFile("instances/att48.tsp");
    // graph->fillGraphFromFile("instances/eil101.tsp");
    graph->fillGraphFromFile("instances/gr120.tsp");
    // graph->fillGraphFromFile("instances/bier127.tsp");//
    // graph->fillGraphFromFile("instances/pr152.tsp");
    // graph->fillGraphFromFile("instances/u159.tsp");
    // graph->fillGraphFromFile("instances/rat195.tsp");
    // graph->fillGraphFromFile("instances/tsp225.tsp");
    // graph->fillGraphFromFile("instances/pr299.tsp");
    // graph->fillGraphFromFile("instances/rbg323.atsp");
    // graph->fillGraphFromFile("instances/rbg403.atsp");
    // graph->fillGraphFromFile("instances/rbg443.atsp");

    // graph->printGraph();

    // runBruteForce(graph, 0);

    // runHeldKarp(graph);

    // runSimulatedAnnealing(graph);

    // runTabuSearch(graph);

    runGeneticAlgorithm(graph);

    delete graph;

    cout<<endl<<" Press any key to exit";
    getch();

    return 0;
}
