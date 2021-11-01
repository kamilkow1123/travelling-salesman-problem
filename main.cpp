#include <iostream>
#include "AdjacencyMatrixGraph/graphAM.cpp"
#include "BruteForce/bruteForce.cpp"
#include "Timer/timer.cpp"

using namespace std;

float unitFactor = 1.0f; //microseconds
string unit = " seconds";

int main(){
    GraphAM *graphAM = new GraphAM();

    graphAM->fillGraphFromFile("data/m11.atsp");
    //graphAM->printGraph();

    float time = 0;
    Timer timer;
    int *result = bruteForce(graphAM, 0);
    time += timer.getTime().count() * unitFactor;
    int shortestPathWeigh = result[0];
    int lengthOfRoute = result[1];

    cout<<"Shortest path: ";
    for(int i = 0; i < lengthOfRoute; i++){
        cout<<result[i + 2]<<" ";
    }
    cout<<endl<<"Weigh: "<<shortestPathWeigh<<endl;
    cout<<"Brute force took: "<<time<<unit<<endl;

    return 0;
}
