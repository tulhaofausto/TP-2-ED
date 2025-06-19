#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "list.hpp"
#include "stack.hpp"
#include "depot.hpp"

// Decidi implementar o grafo sem ser abstrato, focado no stack de depots pois será melhor para trabalhar com as chaves 

class Graph {
private:
    int numVertices; // Numero de vértices no grafo
    List<Depot>* adjacencyList; // Array de listas de adjacência

public:
    Graph(int vertices);
    ~Graph();

    void addEdge(Depot* source, Depot* destination);
    List<Depot> getEdges(Depot source);
    void breadthFirstSearch(Depot *startVertex, Depot *finishVertex);
};

#endif