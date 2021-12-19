#include "../AdjacencyMatrixGraph/graphAM.h"
#include "../SimulatedAnnealing/simulatedAnnealing.cpp"
using namespace std;

vector<int> permutationSwap(vector<int> permutation, int firstIndex, int secondIndex)
{
    if(firstIndex != secondIndex) iter_swap(permutation.begin() + firstIndex, permutation.begin() + secondIndex);

    return permutation;
}

void decrementCadencies(vector<vector<int>> &tabuList){
    int size = tabuList.size();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if(tabuList[i][j] > 0)
                --tabuList[i][j];
        }
    }
}

void clearTabuList(vector<vector<int>> &tabuList){
    int size = tabuList.size();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            tabuList[i][j] = 0;
        }
    }
}

void printTabuList(vector<vector<int>> &tabuList){
    int size = tabuList.size();
    cout<<"tabuList"<<endl;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout<<tabuList[i][j]<<" ";
        }
        cout<<endl;
    }
}


pair<vector<int>, int> solveTS(GraphAM *graph, int numOfIterations)
{
    random_device rd;
    mt19937 g(rd());

    int numOfVertices = graph->getNumOfVertexes();
    vector<vector<int>> tabuList(numOfVertices, vector<int>(numOfVertices));
    vector<int> permutation = initialPermutation(graph);
    vector<int> bestPermutation = permutation;
    vector<int> newPermutation = permutation;

    int cadency = (int)sqrt(numOfVertices);
    cout<<" Cadency: "<<cadency<<endl;

    int cost = costOfPermutation(graph, permutation);
    int prevCost = cost;
    int bestCost = cost;
    int prevBestCost = INT_MAX;

    int bestI;
    int bestJ;

    int sameCostCounter = 0;
    int criticalEvents = 0;
    int iterationCounter = 0;
    while (iterationCounter <= numOfIterations && sameCostCounter < 50){
        bestI = 0;
        bestJ = 0;

        if(prevCost == cost) sameCostCounter++;
        else sameCostCounter = 0;
        prevCost = cost;

        if(prevBestCost != bestCost) printNewAnswer(iterationCounter, bestCost, graph->getOptimalValue());

        iterationCounter++;
        for (int i = 0; i < numOfVertices - 1; i++){
            for(int j = 0; j < numOfVertices - 1; j++){
                if(i == j) continue;
                newPermutation = permutationSwap(permutation, i, j);
                int newCost = costOfPermutation(graph, newPermutation);

                if (newCost >= bestCost && (newCost >= cost || tabuList[i][j] != 0)) continue;

                permutation = newPermutation;
                cost = newCost;
                bestI = i;
                bestJ = j;
            }
        }

        permutation = permutationSwap(permutation, bestI, bestJ);
        tabuList[bestI][bestJ] = cadency;

        decrementCadencies(tabuList);

        prevBestCost = bestCost;
        if(cost < bestCost){
            bestCost = cost;
            bestPermutation = permutation;
            criticalEvents = 0;
        } else if(cost >= prevCost){
            criticalEvents++;
            if(criticalEvents < 20) continue;

            shuffle(permutation.begin(), permutation.end(), g);
            cost = costOfPermutation(graph, permutation);
            clearTabuList(tabuList);
        }
    }
    bestPermutation.insert(bestPermutation.begin(), 0);
    bestPermutation.push_back(0);
    return make_pair(bestPermutation, bestCost);
}