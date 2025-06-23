#ifndef EVENT_HPP
#define EVENT_HPP

#include "depot.hpp"
#include "package.hpp"
#include "graph.hpp"
#include <exception>

class PackageDeliveredException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Pacote entregue!";
    }
};

class DepotNotPrepared : public std::exception{
private:
    int numToOk;
public:
    DepotNotPrepared(int num):numToOk(num){};
    const char* what() const noexcept override {
        return "Pilha não pronta para retirada, deve-se desestackar";
    }
    int getNumUntillOk(){
        return numToOk;
    }

};
class Event{
protected:
    long long priorityKey;
    int eventType;
    int eventTime;

    Package *e_package;
    Depot *e_depot;
    Depot *e_des_depot;

public:
    /// @brief Cria a chave de prioridade de acordo com as regras fornecidas pelo enunciado do TP
    /// @param _eventType 1 = Evento de pacote-postagem / 2 = Evento de transporte
    /// @param _eventTime tempo que o evento deverá acontecer
    /// @param pack 
    Event(int _eventType, int _eventTime, Package* pack);
    Event(int _eventType, int _eventTime, Depot* orgDep, Depot* dstDep);
    Event():eventTime(-1), eventType(-1){};



    /// @brief Procura o Package e executa a seguinte sequencia: tira da pilha inicial e o coloca em estado de "Em transporte"
    /// @param pack 
    /// @details "evento de transporte"
    List<Package*> TransportOut();

    /// @brief Coloca o Package no armazem marcado pelo index interno da classe Package
    /// @param pack 
    /// @details "evento de postagem"
    void TransportIn(int transitLatency);

    /// @brief Retorna o pacote caso ele tenha sido entregue.
    /// @details A intenção é que isso seja útil para armazenar em um vetor de pacotes entregues, por exemplo.
    /// @return pacote do evento
    Package* DeliveredPackage();

    /// @brief Muda o Package para a pilha de reestoque. Se o pacote ja está na pilha de reestoque, recoloca no destino.
    /// @param pack 
    /// @details "evento de pacote"
    void ChangePile(Package* pack);

    /// Comparadores de maior que e menor que
    bool operator<(const Event& other) const {
        return this->priorityKey < other.priorityKey;
    }
    bool operator>(const Event& other) const {
        return this->priorityKey > other.priorityKey;
    }
    /// ---------------------------------------------

    int getSTime() const;
    int getType() const;
    Depot* getDepot() const;
    friend std::ostream& operator<<(std::ostream& os, const Event& e);
};

std::ostream& operator<<(std::ostream& output, const Event& e) {
    if(e.eventType == 1){
        output << e.priorityKey << " pacote " << e.e_package->getId() << " ";
    }else if(e.eventType == 2){

    }
    
    return output;
}

#endif