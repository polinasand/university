#include "SmoothSort.h"

#include <iostream>
int max_val=20;


SmoothSort::SmoothSort() {
    heaps = {};
    L = vector<int>(max_val);
    L[0] = 1, L[1] = 1;
    for (int i=2; i<max_val; i++){
        L[i] = L[i-1]+L[i-2]+1;
    }
}

int SmoothSort::getLeft(int ind, int k){
    return ind - L[k-2]-1;
}

int SmoothSort::getRight(int ind, int k){
    return ind-1;
}
void SmoothSort::push(int val, vector<int>& data) {

    int n = heaps.size()-1;
    if (n>=1 && heaps[n]->k == heaps[n-1]->k-1){
        LeonardoHeap* newHeap = new LeonardoHeap(val, heaps[n]->k+2);
        heaps.pop_back();
        heaps.pop_back();
        heaps.push_back(newHeap);
    } else {
        LeonardoHeap* heap = new LeonardoHeap(val, 1);
        if (n>=0 && heaps[n]->k==1)
            heap = new LeonardoHeap(val, 0);


        heaps.push_back(heap);
    }

    restore(data);
}
void SmoothSort::restore(vector<int>& data) {
    int curr = heaps.size()-1;

    while (curr>0){
        int ind = heaps[curr]->ind;
        int k = heaps[curr]->k;
        int prev = heaps[curr-1]->ind;
        int max_val = max(data[ind], data[prev]);

        if (k>1) {
            int left = getLeft(ind, k);
            int right = getRight(ind, k);
            max_val = max(max_val, max(data[left], data[right]));
        }
        if (max_val != data[prev]){
            break;
        }

        swap(data[ind], data[prev]);
        curr--;
    }
    heapify(data, heaps[curr]->k,  heaps[curr]->ind);
}
void SmoothSort::heapify(vector<int>& data, int k, int ind) {
    if (k<2)
        return;


    int left = getLeft(ind, k);
    int right = getRight(ind, k);
    int max_val = max(data[ind], max(data[left], data[right]));
    if (max_val==data[ind])
        return;
    if (max_val==data[left]) {
        swap(data[ind], data[left]);
        heapify(data, k-1, left);

        return;
    }
    swap(data[right], data[ind]);
    heapify(data, k-2, right);

}
int SmoothSort::pop(vector<int>& data){

    int n = heaps.size()-1;
    if (heaps[n]->k <= 1){
        int val = heaps[n]->ind;
        heaps.pop_back();
        return val;
    }
    int k = heaps[n]->k;
    int ind = heaps[n]->ind;
    int res = data[ind];
    int left = getLeft(ind, k), right = getRight(ind, k);

    heaps.pop_back();
    heaps.push_back(new LeonardoHeap(left, k-1));
    restore(data);
    heaps.push_back(new LeonardoHeap(right, k-2));
    restore(data);

    return res;
}

bool SmoothSort::isEmpty(){
    return heaps.size()==0;
}

void SmoothSort::sort(vector<int>& data){
    for (int i=0; i<data.size(); i++){
        push(i, data);
    }
    for (int i=0;i<data.size();i++){
        pop(data);
    }
}
