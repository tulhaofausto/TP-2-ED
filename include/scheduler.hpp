#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "event.hpp"
#include "minHeap.hpp"

class Scheduler{
private:
    int currentTime;
    MinHeap<Event*> eventQueue;
public:
    Scheduler();

    /// @brief Enfilera evento
    /// @param tbqEvent tbq = to be queued = a ser enfileirado
    void queueEvent(Event* tbqEvent); 

    /// @brief Desinfilera o próximo evento da fila (o primeiro minHeap)
    Event* dequeueNextEvent();

    /// @brief Aumenta o tempo para equiparar com o tempo da simulação.
    /// @param time 
    void increaseTime(int time);

    void printEventQueue(){
        eventQueue.printInOrder();
    };

};

#endif