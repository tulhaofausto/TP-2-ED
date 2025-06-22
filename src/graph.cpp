#include "graph.hpp"

Graph::Graph(int vertices):numVertices(vertices){}

void Graph::addEdge(Depot* source, Depot* destination) {
    for (int i = 0; i < numVertices; i++) {
        if (*(adjacencyList[i].front()) == *source) {
            adjacencyList[i].pushBack(destination);
            return;
        }
    }
    // Se não encontrou, cria uma nova lista para esse source
    adjacencyList[adjacencyList[0].getSize()].pushBack(source);
    adjacencyList[adjacencyList[0].getSize() - 1].pushBack(destination);
};

List<Depot*> Graph::getEdges(Depot* source) {
    for (int i = 0; i < numVertices; i++) {
        if (*(adjacencyList[i].front()) == *source) {
            return adjacencyList[i];
        }
    }
    throw std::invalid_argument("O deposito nao pertence a rede de armazens");
};



List<Depot*> Graph::findShortestPath(Depot* startVertex, Depot* finishVertex) {
    Queue<Depot*> exploreQueue(numVertices);
    bool* exploredVertices = new bool[numVertices]();

    Depot** lastVisited = new Depot*[numVertices];
    for (int i = 0; i < numVertices; ++i)
        lastVisited[i] = nullptr;

    
    Depot* auxDepot = startVertex;
    exploredVertices[auxDepot->getId()] = true;
    exploreQueue.enqueue(auxDepot);

    while (exploreQueue.getSize() != 0) {
        auxDepot = exploreQueue.dequeue();
        if (*auxDepot == *finishVertex) {
            break;
        }
        List<Depot*> adjacents = this->getEdges(auxDepot);
        adjacents.removeFront(); // Remove o próprio vértice (source)
        while (!adjacents.isEmpty()) {
            Depot* atual = adjacents.popHead();
            if (!exploredVertices[atual->getId()]) {
                exploreQueue.enqueue(atual);
                exploredVertices[atual->getId()] = true;
                lastVisited[atual->getId()] = auxDepot;
            }
        }
    }

    // Reconstrução do caminho
    List<Depot*> path;
    for (Depot* at = finishVertex; at != nullptr; at = lastVisited[at->getId()]) {
        path.pushFront(at);
    }

    delete[] lastVisited;
    delete[] exploredVertices;
    return path;
}

Graph::~Graph() {
    delete[] adjacencyList;
}