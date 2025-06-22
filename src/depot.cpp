#include "depot.hpp"
#include "package.hpp"

Depot::Depot(int id, int flowCapacity) : id(id), enteringCapacity(flowCapacity), leavingCapacity(flowCapacity) {};

Depot::depotStack* Depot::findStack(Depot *source){
    for (int i = 0; i < d_Num; i++){
        if (destinations[i]->d_depot == source) {
            return destinations[i];
        }
    }
    throw std::out_of_range("Nao existe na Stack");
}

void Depot::findConnections(List<Depot*> depotConnections){
    this->destinations = new depotStack*[depotConnections.getSize()+1];
    int i;
    for(i = 1; i < depotConnections.getSize(); i++){
        Depot* destDepot = depotConnections.get(i);
        this->destinations[i] = new depotStack(destDepot, 
            (this->leavingCapacity < destDepot->getEnteringCapacity() ? // Seta a quantidade de pacotes de transporte de acordo com a capacidade de entrada/saída do destino/origem
            this->leavingCapacity : destDepot->getEnteringCapacity()));
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

int Depot::getLeavingCapacity() {
    return leavingCapacity;
}

int Depot::getEnteringCapacity() {
    return enteringCapacity;
}

int Depot::getTransportTime(Depot* destination){
    return findStack(destination)->transport_time;
};

int Depot::getId() const{
    return this->id;
}

Depot::~Depot() {
    // Libera cada depotStack alocado
    for (int i = 0; i < d_Num; i++) {
        delete destinations[i];
    }
    // Libera o array de ponteiros
    delete[] destinations;
}