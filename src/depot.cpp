#include "depot.hpp"
#include "package.hpp"

Depot::Depot(int id, int flowCapacity) : id(id), enteringCapacity(flowCapacity), leavingCapacity(flowCapacity) {};

Depot::depotStack* Depot::findStack(Depot *source){
    if(source == nullptr){
        return destinations[d_Num]; // retorna a pilha de reestack
    }
    else if(source == this){
        return destinations[d_Num + 1]; // retorna a pilha para si mesmo. Para guardar os pacotes entregues ao destino final
    }
    for (int i = 0; i < d_Num; i++){
        if (destinations[i]->d_depot == source) {
            return destinations[i]; // retorna a determinada pilha
        }
    }
    throw std::out_of_range("Nao existe na Stack");
}

void Depot::findConnections(List<Depot*> depotConnections){
    this->destinations = new depotStack*[depotConnections.getSize()+2];
    int i;
    for(i = 1; i < depotConnections.getSize(); i++){
        Depot* destDepot = depotConnections.get(i);
        this->destinations[i] = new depotStack(destDepot, 
            (this->leavingCapacity < destDepot->getEnteringCapacity() ? // Seta a quantidade de pacotes de transporte de acordo com a capacidade de entrada/saída do destino/origem
            this->leavingCapacity : destDepot->getEnteringCapacity()));
    }
    this->destinations[i] = new depotStack(nullptr, 1); // Aloca à penúltima posição, um stack que será utilizado para movimentação
    this->destinations[i+1] = new depotStack(this, 0); // Aloca à última posição, um stack que aponta para si mesmo, para guardar os pacotes entreges
                                                       // antes dele ser retirado do sistema
    d_Num = i;
};

bool Depot::operator==(const Depot& other) const {
    return this->id == other.id;
};

void Depot::addPackage(Package *package, Depot *destination){
    depotStack* currentStack = findStack(destination);
    if(destination == nullptr)
        currentStack = destinations[d_Num];
    else 
        currentStack = findStack(destination);
    
    if (currentStack) {
        currentStack->d_stack.push(package);
    }
};

Package* Depot::removePackage(Depot *destination){
    depotStack* currentStack = nullptr;
    if(destination == nullptr)
        currentStack = destinations[d_Num];
    else
        currentStack = findStack(destination);

    if (currentStack) {
        if(currentStack->d_stack.getSize()!=0){
            return currentStack->d_stack.pop();
        }
        throw std::out_of_range("A stack chegou ao fim");
    }
    return nullptr; // Retorna nullptr se não encontrou ou se a pilha está vazia
};

List<Depot*> Depot::getConnections() {
    List<Depot*> connections;
    for (int i = 0; i < d_Num; i++) {
        if (destinations[i]->d_depot != nullptr) {
            connections.pushBack(destinations[i]->d_depot);
        }
    }
    return connections;
}

int Depot::getConFlowCapacity(Depot* des_depot){
    int dd_flowCapacity = findStack(des_depot)->d_depot->getEnteringCapacity();
    return this->leavingCapacity < dd_flowCapacity? this->leavingCapacity : dd_flowCapacity;
}

int Depot::getStackSize(Depot* des_depot){
    return findStack(des_depot)->d_stack.getSize();
}

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

int Depot::getD_num() const{
    return this->d_Num;
}

Package* Depot::getStackHead(Depot* dep){
    return findStack(dep)->d_stack.getHead();
}

Depot::~Depot() {

    for (int i = 0; i < d_Num+2; i++) {
        delete destinations[i];
    }

    delete[] destinations;
}