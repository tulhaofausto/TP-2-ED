#include "package.hpp"

Package::Package(int id, Depot* originDepot, Depot* destinationDepot): packageId(id), origin(originDepot), destination(destinationDepot){
                                   
};

void Package::setPath(Graph& depotNet){
    this->path = depotNet.findShortestPath(origin, destination);
}

void Package::advanceInPath(){
    if(this->path.get(pathIndex + 1) == nullptr){
        throw std::out_of_range("Ja esta no fim do caminho");
    }
    pathIndex++;
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