#include "depot.hpp"
#define STANDART_TIME 20

Depot::Depot(int id, const std::string& name) : id(id), name(name) {};

depotStack* Depot::findStack(Depot *source){
    for (int i = 0; i < d_Num; i++){
        if (destinations[i]->d_depot == source) {
            return destinations[i];
        }
    }
    throw std::out_of_range("Nao existe na Stack");
}

void Depot::findConnections(Graph *depotNet){
    List<Depot*> depotConnections = depotNet->getEdges(this);
    this->destinations = new depotStack*[depotConnections.getSize()+1];
    int i;
    for(i = 0; i < depotConnections.getSize(); i++){
        Depot* destDepot = depotConnections.get(i);
        this->destinations[i] = new depotStack(destDepot, STANDART_TIME);
    }
    this->destinations[i+1] = new depotStack(nullptr, 1); // Aloca à última posição, um stack que será utilizado para movimentação
    d_Num = i;
};

bool Depot::operator==(const Depot& other) const {
    return this->id == other.id;
};

void Depot::addPackage(Depot *destination, Package *package){
    depotStack* currentStack = findStack(destination);
    if(destination == nullptr)
        currentStack = destinations[d_Num + 1];
    else 
        currentStack = findStack(destination);
    
    if (currentStack) {
        currentStack->d_stack.push(package);
    }
};

Package* Depot::removePackage(Depot *destination){
    depotStack* currentStack = nullptr;
    if(destination == nullptr)
        currentStack = destinations[d_Num + 1];
    else
        currentStack = findStack(destination);

    if (currentStack) {
        return currentStack->d_stack.pop();
    }
    return nullptr; // Retorna nullptr se não encontrou ou se a pilha está vazia
};

int Depot::getId() const{
    return this->id;
}

