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
    Depot* current;

    List<Depot*> path;
    int pathIndex;
    
    int storedTime;
    int transitTime;

    bool is_inTransit;

public:
    Package(int id, Depot* originDepot, Depot* destinationDepot);

    void setPath(Graph& depotNet);
    void advanceInPath();
    Depot* getCurrent();
    Depot* getNext();
    void changeState(); //Muda is_inTransit para 1 caso esteja em 0 e vice versa
    void increaseTransitTime(int time);
    void increaseStoredTime(int time);
    int getTransitTime() const;
    int getStoredTime() const;
    int getId() const;
    
    ~Package();

};
#endif