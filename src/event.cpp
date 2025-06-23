#include "event.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Event::Event(int _eventType, int _eventTime, Package* pack):eventType(_eventType), eventTime(_eventTime), e_package(pack){
    std::stringstream eventPriority;
    if(pack->isPosted()){
        e_depot = pack->getCurrent(); 
    }else
        e_depot = pack->getOrigin();
    

    //Montagem da chave da prioridade a partir das informações de entrada
    eventPriority << std::setw(6) << std::setfill('0') << this->eventTime;
    eventPriority << std::setw(6) << std::setfill('0') << pack->getId();
    eventPriority << this->eventType;

    this->priorityKey = std::stoll(eventPriority.str());
};

Event::Event(int _eventType, int _eventTime, Depot* orgDep, Depot* dstDep):eventType(_eventType), eventTime(_eventTime), e_depot(orgDep){
    std::stringstream eventPriority;
        
    //Montagem da chave da prioridade a partir das informações de entrada
    
    eventPriority << std::setw(6) << std::setfill('0') << this->eventTime;
    if(orgDep != dstDep){
        eventPriority << std::setw(3) << std::setfill('0') << orgDep->getId();
        eventPriority << std::setw(3) << std::setfill('0') << dstDep->getId();
    }else{ // Define uma prioridade melhor para quando o transporte é de reestoque, para garantir que ele ocorra o mais rápido possível
        eventPriority << std::setw(3) << std::setfill('0') << 0;
        eventPriority << std::setw(3) << std::setfill('0') << 0;
    }

    eventPriority << this->eventType;

    this->priorityKey = std::stoll(eventPriority.str());
};

List<Package*> Event::TransportOut() {
    List<Package*> transportingTruck;
    if(e_depot->getConFlowCapacity(e_des_depot) >= e_depot->getStackSize(e_des_depot)){
        for(int i = 0; i < e_depot->getConFlowCapacity(e_des_depot); i++){
            // Esse try/catch busca pelo fim adiantado da stack; caso a capacidade de transporte seja maior que o tamanho do stack
            try{
                transportingTruck.pushBack(e_depot->removePackage(e_des_depot));
            }catch (std::out_of_range &e){
                break;
            }
            transportingTruck.get(i)->advanceInPath();
            transportingTruck.get(i)->changeState();
        }
    }else{
        // Avisa para o código da simulação que o transporte não está preparado e que deve-se retirar a diferença 
        // entre a capacidade de fluxo entre os dois depósitos e o tamanho da pilha da origem para o destino
        throw DepotNotPrepared(e_depot->getConFlowCapacity(e_des_depot) <= e_depot->getStackSize(e_des_depot));
    }
    return transportingTruck;
    
}

void Event::TransportIn(int inTransitTime) {

    e_depot->addPackage(e_package, e_package->getNext()); //coloca o pacote no armazem do evento com direção ao próximo da rota
    e_package->advanceInPath();
    e_package->changeState(); //Muda o estado de em transporte para Estocado
    e_package->increaseTransitTime(inTransitTime); //Muda o tempo em transito
    if(e_package->getCurrent() == e_package->getDestination())
        throw PackageDeliveredException();

    
}

Package* Event::DeliveredPackage(){
    return e_package->getCurrent()->removePackage(e_package->getCurrent());
};

void Event::ChangePile(Package* pack) {
    // Implementação futura
}

int Event::getSTime() const{
    return eventTime;
}

int Event::getType() const{
    return eventType;
}

Depot* Event::getDepot() const{
    return e_depot;
}