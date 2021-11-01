#include<iostream>
#include<climits>
#include<algorithm>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

// unsigned long long int factorial(int n){
//     if(n == 1) return 1;

//     return n*factorial(n-1);
// }

double getPRD(int len, int opt){
    return double(100 * (len - opt))/opt;
}

int* bruteForce(GraphAM *graph, int src){
    int numOfVer = graph->getNumOfVertexes();
    if(src >= numOfVer || src < 0) return 0;

    //cout<<"Number of possible routes: "<<factorial(numOfVer - 1)<<endl;

    int routeSize = numOfVer - 1;
    int *route = new int[routeSize];
    for(int i = 0; i < routeSize; i++){ //initialize all vertices but src
        if(i < src) route[i] = i;
        else if(i >= src) route[i] = i + 1;
    }

    int shortestPathWeigh = INT_MAX;
    int shortestPathSize = routeSize + 2; //routeSize + 2 -> src vertex at the beginning and at the end
    int *shortestPath = new int[shortestPathSize];
    do{
        int pathWeigh = 0;
        int currentNode = src;
        for(int i = 0; i < routeSize; i++){
            pathWeigh += graph->findElement(currentNode, route[i]);
            currentNode = route[i];
        }
        pathWeigh += graph->findElement(currentNode, src); //returning to the src

        if(pathWeigh < shortestPathWeigh){ //new shortest path
            shortestPathWeigh = pathWeigh;

            shortestPath[0] = src; //src at the beginning
            for(int i = 0; i < routeSize; i++){
                shortestPath[i + 1] = route[i];
            }
            shortestPath[shortestPathSize - 1] = src; //src at the end

            //print info about new shortest path
            cout<<"Weigh: "<<shortestPathWeigh<<"     ";
            cout<<fixed<<setprecision(2)<<"PRD: "<<getPRD(shortestPathWeigh, graph->getOptimalValue())<<"%"<<endl;
        }
    }while(next_permutation(route, route + routeSize)); //continue for new permutation

    int resultSize = shortestPathSize + 2; //two extra items for shortestPathWeigh and shortestPathSize
    int *result = new int[resultSize]; //array for results
    result[0] = shortestPathWeigh;
    result[1] = shortestPathSize;

    for(int i = 0; i<shortestPathSize; i++){
        result[i + 2] = shortestPath[i];
    }

    return result;
}