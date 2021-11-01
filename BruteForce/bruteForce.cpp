#include<iostream>
#include<climits>
#include<algorithm>
#include "../AdjacencyMatrixGraph/graphAM.h"
using namespace std;

template<class BidirIt>
bool nextPermutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;

    while (true) {
        BidirIt i1, i2;

        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2));
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}

// unsigned long long int factorial(int n){
//     if(n == 1) return 1;

//     return n*factorial(n-1);
// }

double getPRD(int len, int opt){
    return double(100 * (len - opt))/opt;
}

int* bruteForce(GraphAM *graph, int src){
    int numOfVer = graph->getNumOfVertexes();
    if(src >= numOfVer || src < 0) return nullptr;

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

    bool isFirst = true;
    int firstShortestPathWeigh = INT_MAX;
    double firstPRD;

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
            double prd = getPRD(shortestPathWeigh, graph->getOptimalValue());
            cout<<fixed<<setprecision(2)<<"PRD: "<<prd<<"%"<<endl;

            if(isFirst){
                firstShortestPathWeigh = shortestPathWeigh;
                firstPRD = prd;
                isFirst = false;
            }
        }
    }while(nextPermutation(route, route + routeSize)); //continue with new permutation

    cout<<"Weigh: "<<firstShortestPathWeigh<<"     ";
    cout<<fixed<<setprecision(2)<<"PRD: "<<firstPRD<<"%"<<endl;

    int resultSize = shortestPathSize + 2; //two extra items for shortestPathWeigh and shortestPathSize
    int *result = new int[resultSize]; //array for results
    result[0] = shortestPathWeigh;
    result[1] = shortestPathSize;

    for(int i = 0; i<shortestPathSize; i++){
        result[i + 2] = shortestPath[i];
    }

    return result;
}