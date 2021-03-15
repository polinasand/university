#pragma once
#include<mutex>
using namespace std;

class Fork {
private:
    int priority;
    mutex free;
public:
    Fork(int);
    void put();
    void take();
    int getPriority();
};
