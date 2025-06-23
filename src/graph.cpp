#include "graph.hpp"

Graph::Graph(int vertices):numVertices(vertices){}

void Graph::addVertex(Depot* source) {
    // Procura uma lista vazia (ou posição disponível) no array de listas
    for (int i = 0; i < numVertices; i++) {
        if (adjacencyList[i].isEmpty()) {
            adjacencyList[i].pushBack(source);
            return;
        }
    }
    // Se não houver espaço, pode lançar exceção ou ignorar
    throw std::out_of_range("Não há espaço para adicionar novo vértice.");
}

void Graph::addEdge(Depot* source, Depot* destination) {
    for (int i = 0; i < numVertices; i++) {
        if (*(adjacencyList[i].front()) == *source) {
            adjacencyList[i].pushBack(destination);
            return;
        }
    }
    // Se não encontrou, cria uma nova lista para esse source
    addVertex(source);

};

void Graph::addEdge(int index1, int index2) {
    if(this->adjacencyList[index1].front() != nullptr && this->adjacencyList[index2].front() != nullptr)
        this->adjacencyList[index1].pushBack(this->adjacencyList[index2].front());

    // Se não encontrou, joga exceção de erro lógico pois esse método não deveria ser chamado sem ter essa certeza de que funcionaria
    throw std::logic_error("addEdge indexado só deve ser chamado se houver certeza de que ambos vértices existem");

};

List<Depot*> Graph::getEdgeAdjList(Depot* source) {
    for (int i = 0; i < numVertices; i++) {
        if (*(adjacencyList[i].front()) == *source) {
            return adjacencyList[i];
        }
    }
    throw std::invalid_argument("O deposito nao pertence a rede de armazens");
};

List<Depot*>* Graph::getAdjacencyList() {
    return adjacencyList;
}

void Graph::setEdgeConnections(int index){
    this->adjacencyList[index].front()->findConnections(this->adjacencyList[index]);
}

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
        List<Depot*> adjacents = this->getEdgeAdjList(auxDepot);
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