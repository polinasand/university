#pragma once
#include<cmath>
#include<vector>
#include<string>
using namespace std;
class BloomFilter {
private:
    float pr = 0.01;
    //long long p = 100000007;
    long long n = 1E6;
    long long m = (long long)n*log(1/pr)/(log(2)*log(2)); // size
    long long k = (long long)1LL*log(1/pr)/(log(2)*1LL) + 1; // number of hash functions
    vector<int> bits;
    vector<int> seeds;
    int capacity = 0;
public:
    vector<long long> h(string&);
    bool add(string&);
    bool contains(string&);
    BloomFilter();
};

