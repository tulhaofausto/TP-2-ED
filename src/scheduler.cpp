#include "scheduler.hpp"

Scheduler::Scheduler():currentTime(0), eventQueue(){}

void Scheduler::queueEvent(Event* tbqEvent){
    this->eventQueue.push(tbqEvent);
}

Event* Scheduler::dequeueNextEvent(){
    if (!eventQueue.isEmpty())
        return eventQueue.pop();
    return nullptr;
}

void Scheduler::increaseTime(int time){
    this->currentTime += time;
}

