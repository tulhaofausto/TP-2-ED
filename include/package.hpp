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
    int lastTimeChange;

    bool is_posted;
    bool is_inTransit;

public:
    Package(int id, Depot* originDepot, Depot* destinationDepot);
    Package():Package(0, nullptr, nullptr){};

    void setPath(Graph& depotNet);
    void advanceInPath();
    Depot* getOrigin();
    Depot* getCurrent();
    Depot* getNext();
    Depot* getDestination();
    void changeState(); //Muda is_inTransit para 1 caso esteja em 0 e vice versa
    void increaseTransitTime(int time);
    void increaseStoredTime(int time);
    int getTransitTime() const;
    int getStoredTime() const;
    int getId() const;
    bool isPosted();
    bool operator==(const Package& other) const {
        return this->packageId == other.packageId;
    }

    ~Package();

};
#endif