#ifndef EVENT_HPP
#define EVENT_HPP

#include "depot.hpp"
#include "package.hpp"
#include "graph.hpp"

class Event{
private:
    long long priorityKey;
    int eventType;
    int eventTime;

public:
    /// @brief Cria a chave de prioridade de acordo com as regras fornecidas pelo enunciado do TP
    /// @param _eventType 1 = Evento de pacote-postagem / 2 = Evento de transporte
    /// @param _eventTime tempo que o evento deverá acontecer
    /// @param pack 
    Event(int _eventType, int _eventTime, Package* pack);
    Event():Event(-1, -1, nullptr){};

    /// @brief Procura o Package e executa a seguinte sequencia: tira da pilha inicial e o coloca em estado de "Em transporte"
    /// @param pack 
    /// @details "evento de transporte"
    void TransportOut(Package* pack);

    /// @brief Coloca o Package no armazem marcado pelo index interno da classe Package
    /// @param pack 
    /// @details "evento de postagem"
    void TransportIn(Package* pack);

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
};

#endif