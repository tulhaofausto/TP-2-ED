#ifndef DEPOT_HPP
#define DEPOT_HPP

#include "package.hpp"
#include "basicTADS.hpp"
#include <string>

#define MAX_STORAGE_CAPACITY 100 // Tamanho máximo do armazém

struct depotStack{
    Depot* d_depot;
    Stack<Package*> d_stack; // Tamanho máximo do armazém definido como 100
    int transport_time;

    depotStack(Depot *depot, int transportTime, int capacity = MAX_STORAGE_CAPACITY) 
        : d_depot(depot), d_stack(capacity) {} // Inicializa o depotStack com um Depot e uma pilha de pacotes
};

class Depot{
private:
    int id;
    std::string name;
    depotStack** destinations;
    int d_Num; // Número de destinos;
    depotStack* findStack(Depot* source);

public:
    Depot(int id, const std::string& name);

    void findConnections(Graph *depotNet); // Procura e cria as conexões dos armazens
    bool operator==(const Depot& other) const;

    void addPackage(Depot* destination, Package *package); // Adiciona um pacote ao armazém
    Package* removePackage(Depot* destination); // Remove o primeiro pacote do armazém

    int getTransportTime(Depot* destination);
    int getId() const;

    ~Depot();

};


#endif