#include "package.hpp"

Package::Package(int id, Depot* originDepot, Depot* destinationDepot): packageId(id), origin(originDepot), destination(destinationDepot){
    current = originDepot;   
    pathIndex = 0;
    is_inTransit = 0;                    
};

void Package::setPath(Graph& depotNet){
    this->path = depotNet.findShortestPath(origin, destination);
}

void Package::advanceInPath(){
    if(this->path.get(pathIndex + 1) == nullptr){
        throw std::out_of_range("Ja esta no fim do caminho");
    }
    current = this->path.get(pathIndex);
    pathIndex++;
    
}

Depot* Package::getCurrent(){
    return current;
}

Depot* Package::getNext() {
    // O próximo é o elemento na posição pathIndex + 1
    // Verifica se existe próximo na lista
    if (path.getSize() > pathIndex + 1) {
        return path.get(pathIndex + 1);
    }
    return nullptr; // Não há próximo
}

void Package::changeState() {
    is_inTransit = !is_inTransit;
}

void Package::increaseStoredTime(int time){
    storedTime += time;
}

void Package::increaseTransitTime(int time){
    transitTime += time;
}

int Package::getStoredTime() const{
    return storedTime;
}

int Package::getTransitTime() const{
    return transitTime;
}

int Package::getId() const {
    return packageId;
}