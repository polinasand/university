#include "Fork.h"

Fork::Fork(int _priority): priority(_priority) {}

void Fork::put(){
    this->free.unlock();
}

void Fork::take() {
    this->free.lock();
}

int Fork::getPriority() {
    return priority;
}


