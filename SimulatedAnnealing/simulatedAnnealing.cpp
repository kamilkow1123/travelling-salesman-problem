#include <iostream>
#include <random>
#include <numeric>
#include <string>
#include <ctime>
#include <iomanip>
#include <cmath>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

void printVector(vector<int> answer){
    string path = "";
    vector<int>::iterator it = answer.begin();

    while (it != answer.end())
    {
        path += to_string(*it);
        path += " ";
        it++;
    }

    cout<<" Path: "<<path<<endl;
}

int random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first)
   {
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

int costOfPermutation(GraphAM *graph, vector<int> permutation)
{
    int numOfVertices = graph->getNumOfVertexes();
    int cost = graph->findElement(0, permutation[0]);
    for (int i = 0; i < numOfVertices - 2; i++)
    {
        cost += graph->findElement(permutation[i], permutation[i + 1]);
    }
    cost += graph->findElement(permutation[permutation.size() - 1], 0);
    return cost;
}

vector<int> initialPermutation(GraphAM *graph)
{
    int numOfVertices = graph->getNumOfVertexes();

    vector<int> permutation;
    vector<int> unusedVertices(numOfVertices - 1);
    iota(unusedVertices.begin(), unusedVertices.end(), 1);

    int prevVertex = 0;
    for (int i = 0; i < numOfVertices - 1; i++){
        int minVertex = 0;
        int minCost = INT_MAX;
        for (int j = 0; j < unusedVertices.size(); j++){
            int tempVer = unusedVertices[j];
            if (graph->findElement(prevVertex, tempVer) < minCost && prevVertex != tempVer){
                minCost = graph->findElement(prevVertex, tempVer);
                minVertex = tempVer;
            }
        }
        permutation.push_back(minVertex);

        vector<int>::iterator it = unusedVertices.begin();
        while (it != unusedVertices.end()){
            if ((*it) == minVertex) it = unusedVertices.erase(it);
            else it++;
        }
        prevVertex = minVertex;
    }

    return permutation;
}

vector<int> permutationSwapRandom(vector<int> permutation)
{
    int firstIndex = random(0, permutation.size() - 1);
    int secondIndex =  random(0, permutation.size() - 1);
    if(firstIndex != secondIndex) iter_swap(permutation.begin() + firstIndex, permutation.begin() + secondIndex);

    return permutation;
}


double initialTemperature(GraphAM *graph)
{
    int numOfVertices = graph->getNumOfVertexes();
    int maxCost = 0;
    int tempCost;

    vector<int> permutation = initialPermutation(graph);
    vector<int> prevPermutation = initialPermutation(graph);

    prevPermutation = permutationSwapRandom(prevPermutation);
    for (int i = 0; i < numOfVertices; i++)
    {
        permutation = permutationSwapRandom(permutation);
        tempCost = abs(costOfPermutation(graph, prevPermutation) - costOfPermutation(graph, permutation));
        if(tempCost > maxCost) maxCost = tempCost;
        prevPermutation = permutation;
    }
    return maxCost;
}

void printNewAnswer(int i, int cost, int opt){
    cout<<" "<<i<<".   "<<cost<<"   "<<fixed<<setprecision(4)<<double(100 * (cost - opt))/opt<<"%"<<endl;
}

pair<vector<int>, int> solveSA(GraphAM *graph, float alpha)
{
    random_device rd;
    mt19937 g(rd());

    int numOfVertices = graph->getNumOfVertexes();
    vector<int> permutation = initialPermutation(graph);
    vector<int> bestPermutation = permutation;
    printVector(permutation);

    int eraLength = 10*numOfVertices;

    int cost = costOfPermutation(graph, permutation);
    int prevCost = cost;
    int bestCost = cost;
    int prevBestCost = INT_MAX;

    double initialTemp = initialTemperature(graph);
    double currentTemp = initialTemp;
    cout<<" Initial temperature "<<initialTemp<<endl;

    int iterationCounter = 0;
    int sameCostCounter = 0;

    while (currentTemp > 0.00001 && sameCostCounter < 50){
        if(prevCost == cost) sameCostCounter++;
        else sameCostCounter = 0;
        prevCost = cost;

        if(prevBestCost != bestCost) printNewAnswer(iterationCounter, bestCost, graph->getOptimalValue());

        for (int i = 0; i < eraLength; i++){
            vector<int> newPermutation;
            newPermutation = permutationSwapRandom(permutation);
            int newCost = costOfPermutation(graph, newPermutation);

            if (newCost < cost){
                permutation = newPermutation;
                cost = newCost;
            } else {
                uniform_real_distribution<> dis(0, 1);
                float s = dis(g);
                if (s < exp(-1 * (newCost - cost) / currentTemp)){
                    permutation = newPermutation;
                    cost = newCost;
                }
            }
        }
        currentTemp = initialTemp*pow(alpha, ++iterationCounter);
        prevBestCost = bestCost;
        if(cost < bestCost){
            bestCost = cost;
            bestPermutation = permutation;
        }
    }
    bestPermutation.insert(bestPermutation.begin(), 0);
    bestPermutation.push_back(0);
    return make_pair(bestPermutation, bestCost);
}