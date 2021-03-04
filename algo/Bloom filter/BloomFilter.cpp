#include "BloomFilter.h"
#include <random>
#include<ctime>


BloomFilter::BloomFilter(){
    bits.resize(m);
    for (int i=0; i<k; i++){
        int p = rand();
        if (p % 2 == 0)
            p++;
        if (p < 256) {
            p *= (256/p*2);
        }
        seeds.push_back(p);
    }
}
vector <long long> BloomFilter::h(string &s) {
    vector<long long> res;
    srand(time(nullptr));
    for (int i=0; i<k; i++){
        long long val = s[0];
        int j = 1;
        while (j < s.size()){
            val *= seeds[i];
            val += s[j++];
            val %= m;
        }
        res.push_back(val);
    }
    return res;
}

bool BloomFilter::add(string& s) {
    if (capacity >= n)
        return false;
    vector<long long> values = h(s);
    for (int i=0; i<k; i++){
        bits[values[i]] = 1;
        capacity++;
    }
    return true;
}

bool BloomFilter::contains(string& s) {
    vector<long long> values = h(s);
    for (int i=0; i<k; i++){
        if (bits[values[i]] == 0)
            return false;
    }
    return true;
}
