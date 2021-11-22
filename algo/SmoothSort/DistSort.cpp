#pragma once

#include "SmoothSort.h"
#include<fstream>
#include<set>

const int numPerFile = 100000;

void write(vector<int>& data, string filename) {
    ofstream f;
    f.open(filename);
    for (int i=0; i<data.size(); i++){
        f << data[i];
    }
    f.close();
}

void read(vector<int>& data, int ind) {
    ifstream f;
    f.open(ind+".txt");
    data = {};
    int val;
    for (int i=0; i<data.size(); i++){
        f >> val;
        data.push_back(val);
    }
    f.close();
}

int executeDistributedSort() {
    ifstream f("input.txt");

    int ind=0, i=0, val;
    vector<int> data;
    while(!f.eof()){
        f >> val;
        data.push_back(val);
        i++;
        if (i % numPerFile == 0){
            write(data, ind+".txt");
            ind++;
            data = {};
            i=0;
        }
    }
    if (data.size()>0){
        write(data, ind+".txt");
        ind++;
    }
    f.close();
    return ind;
}

void merge(int num) {
    set<pair<int, int>> s;
    ifstream files[num];
    for (int i=0; i<num; i++){
        string filename = i+".txt";

        files[i] = ifstream(filename);
        int val;
        files[i] >> val;
        s.insert(make_pair(val, i));
    }

    string output = "output.txt";
    vector<int> data;
    while (s.size() > 0){
        auto next = *s.begin();
        s.erase(s.begin());
        data.push_back(next.first);

        if (!files[next.second].eof()){
            int val;
             files[next.second] >> val;
             s.insert(make_pair(val, next.second));
        }

        if (data.size() == numPerFile) {
            write(data, output);
            data.clear();
        }
    }

    write(data, output);
    for (int i=0;i<num;i++){
        files[i].close();
    }
}
