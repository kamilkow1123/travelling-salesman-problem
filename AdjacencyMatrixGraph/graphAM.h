#ifndef _GRAPH_ADJACENCY_MATRIX_H_
#define _GRAPH_ADJACENCY_MATRIX_H_

class GraphAM{ // graph in adjacency matrix
private:
    int **graph; //two-dimensional array representing adjacency matrix
    int numOfVertexes; //number of vertices in the graph
public:
    GraphAM(); //constructor
    ~GraphAM(); //destructor
    void fillGraphFromFile(); //fill the adjacency matrix with data from file
    void printGraph(); //printing adjacency matrix
    void setNumOfVertexes(int); //set the number of vertices
    int getNumOfVertexes(); //get the number of vertices
    int findElement(int, int); //return the value from the array
    void addEdge(int, int, int); //add undirected edge to the graph
    void addVertexes(int); //add vertexes to the graph, without the edges
};

#endif