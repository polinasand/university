#include "StringSet.h"
#include<cmath>
#include<ctime>
#include<chrono>
using namespace std;
#include <iostream>

StringSet::StringSet(): first(nullptr){
    srand(time(nullptr));
    p = rand();
    while (p < pow(2,8)) {
        p = p << 1;
    }
    if (p % 2 == 0)
        p++;
}

link::link(unsigned long long key, int sum, link* next): key(key), sum(sum), next(next) {}

bool StringSet::add(string& s) {
    unsigned long long key = h(s);
    if (capacity < MAX_SIZE && !contains(s)) {
        capacity++;
        first = new link(key, 1, first);
        return true;
    }
    else if (capacity < MAX_SIZE) {
        capacity++;
        link* curr = first;
        while (curr != nullptr) {
            if (curr->key == key){
                curr->sum++;
                return true;
            }
            curr = curr -> next;
        }
    }
    cout << "Element already exists or/and overflow\n";
    return false;
}

bool StringSet::rm(string& s) {
    unsigned long long key = h(s);
    if (first != nullptr) {
        if (first->key == key){
            if (first->sum > 1)
                first->sum--;
            else {
                link* temp = first;
                first = first->next;
                delete temp;
            }
            return true;
        }
    }
    link* curr = first;
    first->next = curr->next;
    while (curr->next != nullptr) {
        if (curr->next->key == key) {
            if (curr->next->sum > 1)
                curr->next->sum--;
            else {
                link* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
            }
            return true;
        }
        curr = curr -> next;
    }
    cout << "There is no such an element\n";
    return false;
}

bool StringSet::contains(string& s){
    unsigned long long key = h(s);
    link* curr = first;
    while (curr != nullptr) {
        if (curr->key == key)
            return true;
        curr = curr -> next;
    }
    return false;
}

unsigned long long StringSet::h(string& s) {
    unsigned long long ans = 0;
    for (int i = 0; i < s.size(); i++) {
        ans += (long long)((int)s[i] * 1LL * pow(p, i));
        ans %= m;
    }
    return ans;
}

void StringSet::iterate() {
    link* curr = first;
    while (curr != nullptr) {
        cout << curr->key << " " << curr->sum << endl;
        curr = curr -> next;
    }
}

