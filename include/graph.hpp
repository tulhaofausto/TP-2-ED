#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "../include/basicTADS.hpp"
#include "depot.hpp"

// Decidi implementar o grafo sem ser abstrato, focado no stack de depots pois será melhor para trabalhar com as chaves 

class Graph {
private:
    int numVertices; // Numero de vértices no grafo
    List<Depot*>* adjacencyList; // Array de listas de adjacência

public:
    Graph(int vertices);
    ~Graph();

    void addVertex(Depot* source);
    void addEdge(Depot* source, Depot* destination);
    void addEdge(int index1, int index2);
    List<Depot*> getEdgeAdjList(Depot* source);
    void setEdgeConnections(int index);
    List<Depot*> findShortestPath(Depot* startVertex, Depot* finishVertex);

};

#endif