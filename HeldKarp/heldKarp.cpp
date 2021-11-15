#include<iostream>
#include<climits>
#include<algorithm>
#include<vector>
#include<utility>
#include<cmath>
#include<bitset>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

int heldKarp(GraphAM *graph)
{
    int numOfVer = graph->getNumOfVertexes();
    int numberOfCombinations = 1<<numOfVer;

    //initialize two-dimensional array
    int **paths = new int*[numberOfCombinations];
    for(int i = 0; i < numberOfCombinations; i++){
        paths[i] = new int[numOfVer];
        for(int j = 0; j < numOfVer; j++){
            paths[i][j] = INT_MAX;
        }
    }

    for (int visited = 1; visited < numberOfCombinations; ++visited)
    {
        for (int last = 0; last < numOfVer - 1; ++last)
        {
            int shift = 1<<last;
            // if last visited or path to itself
            bool alreadyVisited = !(visited & shift);
            if(alreadyVisited) continue;

            //try all possibilities, choose the paths among them
            if(visited == shift){
                //previous vertex must have been numOfVer-1
                paths[visited][last] = graph->findElement(numOfVer - 1, last);
            } else {
                //previous vertex must have been one of the other
                int prev_visited = visited ^ shift;
                for (int prev = 0; prev < numOfVer-1; ++prev) {
                    if (!(prev_visited & 1<<prev)) continue;

                    int tempMin = graph->findElement(last, prev) + paths[prev_visited][prev];
                    if(tempMin < paths[visited][last]){
                        paths[visited][last] = tempMin;
                    }
                }
            }
        }
    }


    // use the path lengths to choose the cheapest cycle
    int answer = INT_MAX;
    for(int last = 0; last < numOfVer - 1; ++last)
    {
        int tempMin = graph->findElement(last, numOfVer - 1) + paths[(1<<(numOfVer-1))-1][last];

        if(tempMin < answer){
            answer = tempMin;
        }
    }

    for(int i = 0; i<numberOfCombinations; i++) delete [] paths[i];
        delete [] paths;

    return answer;
}
