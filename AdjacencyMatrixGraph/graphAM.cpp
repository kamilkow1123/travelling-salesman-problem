#include<iostream>
#include<iomanip>
#include<fstream>
#include<climits>
#include "graphAM.h"
using namespace std;

GraphAM::GraphAM(){ //initialize the graph with zero and null
    this->numOfVertexes = 0;
    this->graph = nullptr;
    this->optimalValue = 0;
}

GraphAM::~GraphAM(){ //release the memory allocated for the graph
    for(int i = 0; i<numOfVertexes; i++) delete [] graph[i];
    delete [] graph;
}

void GraphAM::printGraph(){
    if(numOfVertexes == 0){ //if the graph is empty, print that and return
        cout<<" Graph is empty!"<<endl;
        return;
    }
    cout<<"    ";
    for(int j = 0; j < numOfVertexes; j++){
        cout<<setw(5)<<j;
    }
    cout<<endl<<"    ";
    for(int j = 0; j < numOfVertexes*5 + 3; j++){
        cout<<"-";
    }
    cout<<endl;

    for(int i = 0; i<numOfVertexes; i++){
        cout<<" "<<i<<" |";
        for(int j = 0; j<numOfVertexes; j++){
            cout<<setw(5)<<graph[i][j];
        }
        cout<<endl;
    }
}


void GraphAM::setNumOfVertexes(int num){ //set the number of vertices
    this->numOfVertexes = num;
}

int GraphAM::getNumOfVertexes(){ //get the number of vertices
    return numOfVertexes;
}

int GraphAM::findElement(int n, int m){ //return the value from the array's given indexes
    if(n >= this->numOfVertexes || m >= this->numOfVertexes) return -1;
    return graph[n][m];
}

int GraphAM::getOptimalValue(){ //return optimal Hamiltonian circuit
    return optimalValue;
}

void GraphAM::setOptimalValue(int opt){ //set optimal Hamiltonian circuit
    this->optimalValue = opt;
}

void GraphAM::addVertexes(int vertexes){ //initialize the adjacency matrix with the given number of vertices
    this->graph = new int *[vertexes]; //create array of arrays for the vertices
    this->numOfVertexes = vertexes; //set the number of vertices in the graph
    for(int i = 0; i<numOfVertexes; i++){
        this->graph[i] = new int[vertexes] {0}; //set the vertexes arrays filled with zeros
    }
}

void GraphAM::addEdge(int i, int j, int edgeValue){
    graph[i][j] = edgeValue;
}

void GraphAM::fillGraphFromFile(string file){
    if(numOfVertexes != 0){ //if the graph is not empty, print that and return
        cout<<" Graph is not empty"<<endl;
        return;
    }

    fstream in;
    in.open(file, ios::in); //open the file with the description of the edges

    if(in.good()){ //if the file opened correctly, fill the graph
        string fileName;
        in>>fileName;

        int numberOfVertexes;
        in>>numberOfVertexes; //get number of vertices from the file

        this->addVertexes(numberOfVertexes); //initialize graph by adding vertices

        int edge;
        for(int i = 0; i<numberOfVertexes; i++){
            for(int j = 0; j<numberOfVertexes; j++){
                in>>edge;
                this->addEdge(i, j, edge);
            }
        }
        int optVal;
        in>>optVal;
        this->setOptimalValue(optVal);

        cout<<" Successfully filled matrix!"<<endl; //filled the graph from file
        in.close();
    }
    else{
        cout<<" Cannot open graph.txt"<<endl; //opening the file failed
    }
}