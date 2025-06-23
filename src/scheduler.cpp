#include "scheduler.hpp"
#include "event.hpp"

Scheduler::Scheduler():currentTime(0), eventQueue(){}

void Scheduler::queueEvent(Event* tbqEvent){
    this->eventQueue.push(tbqEvent);
}

void Scheduler::requeueEvent(Event *tbqEvent, int time){
    Event* auxEvent = tbqEvent;
    auxEvent->priorityKey += time * (10000000LL); 
    this->eventQueue.push(auxEvent);
}

Event* Scheduler::dequeueNextEvent(){
    if (!eventQueue.isEmpty())
        return eventQueue.pop();
    return nullptr;
}

void Scheduler::increaseTime(int time){
    this->currentTime += time;
}

