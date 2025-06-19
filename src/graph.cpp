#include "graph.hpp"

Graph::Graph(int vertices):numVertices(vertices){}

void Graph::addEdge(Depot* source, Depot* destination){
    for(int i = 0; i < numVertices; i++){
        if(adjacencyList[i].front() == *source){
            adjacencyList[i].pushBack(*destination);
        }
    }
}

List<Depot> Graph::getEdges(Depot source){
    for(int i = 0; i < numVertices; i++){
        if(adjacencyList[i].front() == source){
            return adjacencyList[i];
        }
    }
    throw std::invalid_argument("O deposito nao pertence a rede de armazens");
};

void Graph::breadthFirstSearch(Depot *startVertex, Depot *finishVertex){
    Queue<Depot*> exploreQueue(numVertices);
    List<Depot*> exploredVertices();
    Depot* auxDepot = startVertex;

    exploredVertices().pushBack(startVertex);
    exploreQueue.enqueue(startVertex);
    int i, j;
    while(exploreQueue.getSize()!=0){
        auxDepot = exploreQueue.dequeue();
        if(*auxDepot == *finishVertex){
            return 
        }
    }

};