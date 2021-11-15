#include<iostream>
#include<climits>
#include<algorithm>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

double getPRD(int len, int opt){
    return double(100 * (len - opt))/opt;
}

int* bruteForce(GraphAM *graph, int src){
    int numOfVer = graph->getNumOfVertexes();
    if(src >= numOfVer || src < 0) return nullptr;

    int routeSize = numOfVer - 1;
    int *route = new int[routeSize];
    for(int i = 0; i < routeSize; i++){ //initialize all vertices but src
        if(i < src) route[i] = i;
        else if(i >= src) route[i] = i + 1;
    }

    int shortestPathWeight = INT_MAX;
    int shortestPathSize = routeSize + 2; //routeSize + 2 -> src vertex at the beginning and at the end
    int *shortestPath = new int[shortestPathSize];

    bool isFirst = true;
    int firstShortestPathWeight = INT_MAX;
    double firstPRD;

    do{
        int pathWeigh = 0;
        int currentNode = src;
        for(int i = 0; i < routeSize; i++){
            pathWeigh += graph->findElement(currentNode, route[i]);
            currentNode = route[i];
        }
        pathWeigh += graph->findElement(currentNode, src); //returning to the src

        if(pathWeigh < shortestPathWeight){ //new shortest path
            shortestPathWeight = pathWeigh;

            shortestPath[0] = src; //src at the beginning
            for(int i = 0; i < routeSize; i++){
                shortestPath[i + 1] = route[i];
            }
            shortestPath[shortestPathSize - 1] = src; //src at the end

            //print info about new shortest path
            cout<<" Weight: "<<shortestPathWeight<<"     ";
            double prd = getPRD(shortestPathWeight, graph->getOptimalValue());
            cout<<fixed<<setprecision(2)<<"PRD: "<<prd<<"%"<<endl;

            if(isFirst){
                firstShortestPathWeight = shortestPathWeight;
                firstPRD = prd;
                isFirst = false;
            }
        }
    }while(next_permutation(route, route + routeSize)); //continue with new permutation

    cout<<" Weight: "<<firstShortestPathWeight<<"     ";
    cout<<fixed<<setprecision(2)<<"PRD: "<<firstPRD<<"%"<<endl;

    int resultSize = shortestPathSize + 2; //two extra items for shortestPathWeight and shortestPathSize
    int *result = new int[resultSize]; //array for results
    result[0] = shortestPathWeight;
    result[1] = shortestPathSize;

    for(int i = 0; i<shortestPathSize; i++){
        result[i + 2] = shortestPath[i];
    }

    delete [] route;
    delete [] shortestPath;

    return result;
}