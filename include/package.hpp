#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "depot.hpp"
#include <stdexcept>

class Package {
private:
    int packageId;
    Depot* origin;
    Depot* destination;
public:
    Package(int id, Depot* originDepot, Depot* destinationDepot);

    

};
#endif