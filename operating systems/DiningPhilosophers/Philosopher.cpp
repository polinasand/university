#include "Philosopher.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

Philosopher::Philosopher(Fork* lFork, Fork* rFork) {
    leftFork = lFork;
    rightFork = rFork;
}
void Philosopher::start(chrono::milliseconds lifetime, int num){
    auto start = chrono::system_clock::now();
	while (true) {
        //cout << "Ph "<<num<<" eating\n";
		eat();
        //cout << "Ph "<<num<<" thinking\n";
		think();
		auto curr = chrono::system_clock::now();
		auto time = chrono::duration_cast<chrono::milliseconds>(curr-start);
        if (time >= lifetime)
			return;
	}
}

void Philosopher::eat() {
    int left = leftFork->getPriority();
    int right = rightFork->getPriority();

    if (left < right){
        leftFork->take();
        rightFork->take();
    }
    else {
        rightFork->take();
        leftFork->take();
    }
    // eating
    this_thread::sleep_for(chrono::milliseconds(10));

    if (left < right){
        rightFork->put();
        leftFork->put();
    }
    else {
        leftFork->put();
        rightFork->put();
    }
    eatingTimes++;
}

void Philosopher::think() {
    //thinking
    this_thread::sleep_for(chrono::milliseconds(10));
}

long long Philosopher::getEatingTime(){
    return (this->eatingTimes*chrono::milliseconds(10)).count();
}

long long Philosopher::getThinkingTime(){
    return (this->eatingTimes*chrono::milliseconds(10)).count();
}
