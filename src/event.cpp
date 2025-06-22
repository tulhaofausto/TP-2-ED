#include "event.hpp"
#include <sstream>
#include <iomanip>

Event::Event(int _eventType, int _eventTime, Package* pack):eventType(_eventType), eventTime(_eventTime){
    std::stringstream eventPriority;
        
    //Montagem da chave da prioridade a partir das informações de entrada
    eventPriority << std::setw(6) << std::setfill('0') << this->eventTime;

    if (this->eventType == 1) { // Evento de postagem
        eventPriority << std::setw(6) << std::setfill('0') << pack->getId();
    }
    else if (this->eventType == 2) { // Evento de transporte
        eventPriority << std::setw(3) << std::setfill('0') << pack->getCurrent();
        eventPriority << std::setw(3) << std::setfill('0') << pack->getNext();
    }

    eventPriority << this->eventType;

    this->priorityKey = std::stoll(eventPriority.str());
};

void Event::TransportOut(Package* pack) {
    // Implementação futura
}

void Event::TransportIn(Package* pack) {
    // Implementação futura
}

void Event::ChangePile(Package* pack) {
    // Implementação futura
}
