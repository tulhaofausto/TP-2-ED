#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "depot.hpp"
#include "graph.hpp"
#include <stdexcept>

class Package {
private:
    int packageId;

    Depot* origin;
    Depot* destination;
    
    List<Depot*> path;
    int pathIndex;
    
    int storedTime;
    int transitTime;

public:
    Package(int id, Depot* originDepot, Depot* destinationDepot);

    void setPath(Graph& depotNet);
    void advanceInPath();
    void increaseTransitTime(int time);
    void increaseStoredTime(int time);
    int getTransitTime() const;
    int getStoredTime() const;
    
    ~Package();

};
#endif