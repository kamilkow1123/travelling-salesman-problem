#include <iostream>
#include <random>
#include <numeric>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

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

vector<int> initialPermutation(GraphAM *graph, mt19937 g)
{
    int numOfVertices = graph->getNumOfVertexes();
    vector<int> permutation(numOfVertices - 1);
    iota(permutation.begin(), permutation.end(), 1);
    shuffle(permutation.begin(), permutation.end(), g);

    return permutation;
}

vector<int> permutationSwap(vector<int> permutation)
{
    int firstIndex = random(0, permutation.size() - 1);
    int secondIndex =  random(0, permutation.size() - 1);
    iter_swap(permutation.begin() + firstIndex, permutation.begin() + secondIndex);

    return permutation;
}

void printNewAnswer(int i, int cost, int opt){
    cout<<i<<". "<<cost<<" "<<fixed<<setprecision(4)<<double(100 * (cost - opt))/opt<<"%"<<endl;
}

pair<vector<int>, int> solveSA(GraphAM *graph, double initialTemp, float alpha, int eraLength)
{
    random_device rd;
    mt19937 g(rd());
    int numOfVertices = graph->getNumOfVertexes();
    vector<int> permutation = initialPermutation(graph, g);
    int cost = costOfPermutation(graph, permutation);
    int prevCost = INT_MAX;
    double currentTemp = initialTemp;

    while (currentTemp > 0.00001)
    {
        prevCost = cost;

        for (int i = 0; i < eraLength; i++){
            vector<int> newPermutation;
            newPermutation = permutationSwap(permutation);
            int newCost = costOfPermutation(graph, newPermutation);
            int delta = newCost - cost;

            if (delta < 0){
                permutation = newPermutation;
                cost = newCost;
                //printNewAnswer(i, cost, graph->getOptimalValue());
            } else {
                uniform_real_distribution<> dis(0, 1);
                float s = dis(g);
                if (s < exp(-delta / currentTemp)){
                    permutation = newPermutation;
                    cost = newCost;
                    //printNewAnswer(i, cost, graph->getOptimalValue());
                }
            }
        }
        currentTemp *= alpha;
    }
    permutation.insert(permutation.begin(), 0);
    permutation.push_back(0);
    return make_pair(permutation, cost);
}