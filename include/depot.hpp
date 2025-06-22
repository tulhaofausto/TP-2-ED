#ifndef DEPOT_HPP
#define DEPOT_HPP

#include "basicTADS.hpp"
#include <string>

class Package;

class Depot{
private:
    int id;
    int leavingCapacity; // Capacidade de entrada de transporte
    int enteringCapacity; // Capacidade de saída de transporte
    struct depotStack{
        Depot* d_depot;
        Stack<Package*> d_stack; // Tamanho máximo do armazém definido como 100
        int transport_time;

        depotStack(Depot *depot, int transportTime) 
            : d_depot(depot), d_stack() {} // Inicializa o depotStack com um Depot e uma pilha de pacotes
    };
    depotStack** destinations;
    int d_Num; // Número de destinos;
    depotStack* findStack(Depot* source);

public:
    Depot(int id, int flowCapacity);
    Depot():Depot(-1, 0){};

    void findConnections(List<Depot*> depotConnections); // Procura e cria as conexões dos armazens
    bool operator==(const Depot& other) const;

    void addPackage(Depot* destination, Package *package); // Adiciona um pacote ao armazém
    Package* removePackage(Depot* destination); // Remove o primeiro pacote do armazém

    int getLeavingCapacity();
    int getEnteringCapacity();
    int getTransportTime(Depot* destination);
    int getId() const;

    ~Depot();

};


#endif