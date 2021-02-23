#pragma once
#include<string>
#include<cmath>
using namespace std;
struct link{
    unsigned long long key;
    int sum = 0;
    link* next;
    link(unsigned long long key, int sum, link* next=nullptr);
};
class StringSet {
    private:
        link* first;
        const unsigned long long m = pow(2, 32);
        long long p;
        int capacity = 0;
        int MAX_SIZE = 1000000;
        unsigned long long h(string&);
    public:
        StringSet();
        bool add(string&);
        bool rm(string&);
        bool contains(string&);
        void iterate();
};
