#pragma once
#include "Fork.h"
using namespace std;

class Philosopher {
private:
    Fork* leftFork;
    Fork* rightFork;
    int eatingTimes = 0;
    static constexpr auto oneEatingTime = chrono::milliseconds(10);
    int thinkingTimes = 0;
    static constexpr auto oneThinkingTime = chrono::milliseconds(10);
public:
    Philosopher(Fork* leftFork, Fork* rightFork);
    void start(chrono::milliseconds, int num);
    void think();
    void eat();
    long long getEatingTime();
    long long getThinkingTime();
};
