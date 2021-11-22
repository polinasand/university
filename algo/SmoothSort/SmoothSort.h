#include <vector>
#include<algorithm>

using namespace std;
struct LeonardoHeap {
    public:
    LeonardoHeap(int ind, int k) {
        this->ind = ind;
        this->k = k;
    }

    int ind;
    int k;
};

class SmoothSort {
private:
    vector<LeonardoHeap*> heaps;
    vector<int> L;
    void heapify(vector<int>&, int,int);
    void restore(vector<int>&);
    int getLeft(int, int);
    int getRight(int, int);
public:
    SmoothSort();
    void push(int , vector<int>&);
    int pop(vector<int>&);
    bool isEmpty();
    void sort(vector<int>&);
};

