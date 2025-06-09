#ifndef DEPOT_HPP
#define DEPOT_HPP

#include "package.hpp"
#include "stack.hpp"
#include <string>

#define MAX_STORAGE_CAPACITY 100 // Tamanho máximo do armazém

struct depotStack{
    Depot* d_depot;
    Stack<Package> d_stack; // Tamanho máximo do armazém definido como 100

    depotStack(Depot *depot, int capacity = MAX_STORAGE_CAPACITY) 
        : d_depot(depot), d_stack(capacity) {} // Inicializa o depotStack com um Depot e uma pilha de pacotes
};

class Depot{
private:
    int id;
    std::string name;
    depotStack* destinations;

public:
    Depot(int id, const std::string& name);

    void findConections() const; //procura as conexões no grafo de armazéns
    void linkDepots(Depot *depot); //Linka dois armazens, criando uma pilha de pacote de A para B (não é bidirecional)
    

    void addPackage(Depot* destination, const Package& package); // Adiciona um pacote ao armazém
    Package removePackage(Depot* destination); // Remove o primeiro pacote do armazém

    ~Depot();

};


#endif