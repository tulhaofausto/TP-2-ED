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
        Stack<Package*> d_stack;
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

    void addPackage(Package *package, Depot* destination); // Adiciona um pacote ao armazém
    Package* removePackage(Depot* destination); // Remove o primeiro pacote do armazém

    int getLeavingCapacity();
    int getEnteringCapacity();
    int getConFlowCapacity(Depot* des_depot); // Retorna a capacidade de transporte entre dois armazenamentos
    int getStackSize(Depot* des_depot); // Retorna o tamanho da Stack de pacotes do destino

    List<Depot*> getConnections();
    int getTransportTime(Depot* destination);
    int getId() const;
    int getD_num() const;
    Package* getStackHead(Depot* dep);

    ~Depot();

};


#endif