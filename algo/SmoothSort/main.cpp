#pragma once

#include <iostream>
#include "SmoothSort.h"
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include<set>

using namespace std::chrono;
using namespace std;

const int numPerFile = 10000;
const int n = 1000;
const string inputFile = "in.txt";

void generate(int, string);
void generateSorted(int, string);
void executeSort();
int executeDistributedSort(SmoothSort);
void merge(int);
void read(vector<int>&, int);
void write(vector<int>&, string);


int main()
{
    generateSorted(n, inputFile);
    //executeSort();
    SmoothSort smooth;
    for (int i=0; i<20; i++){
        auto start = std::chrono::steady_clock::now();
        int num = executeDistributedSort(smooth);
        merge(num);
        auto elapsed = std::chrono::steady_clock::now() - start;
        long long time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << time<<endl;
    }
    return 0;
}

void generate(int n, string filename) {
    ofstream f;
    f.open(filename);
    srand(time(NULL));
    for (int i=0; i<n; i++){

        f << rand() %n << ' ';
    }
    f.close();
}

void generateSorted(int n, string filename) {
    ofstream f;
    f.open(filename);
    for (int i=0; i<n; i++){

        f << i << ' ';
    }
    f.close();
}

void executeSort() {
    SmoothSort smooth;
    ifstream in;

    in.open(inputFile);

    int val;
    vector<int> data;
    int N = n;
    while (!in.eof() && N>0){
        in >> val;
        data.push_back(val);
        N--;
    }
    in.close();
    for (int i=0; i<20; i++){
        auto start = std::chrono::steady_clock::now();
        smooth.sort(data);
        auto elapsed = std::chrono::steady_clock::now() - start;
        long long time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout << time<<endl;
    }




    /*ofstream out;
    out.open("out.txt");
    for (int i=0;i<data.size();i++){
        out << data[i] << ' ';
    }
    out.close();*/
}



void write(vector<int>& data, string filename) {
    ofstream f;
    f.open(filename);
    for (int i=0; i<data.size(); i++){
        f << data[i] << ' ';
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

int executeDistributedSort(SmoothSort smooth) {
    ifstream f(inputFile);

    int ind=0, i=0, val;
    vector<int> data;
    while(!f.eof()){
        f >> val;
        data.push_back(val);
        i++;
        if (i % numPerFile == 0){
            smooth.sort(data);
            write(data, to_string(ind)+".txt");
            ind++;
            data = {};
            i=0;
        }
    }
    if (data.size()>0){
        write(data, to_string(ind)+".txt");
        ind++;
    }
    f.close();

    return ind;
}

void merge(int num) {
    set<pair<int, int>> s;
    ifstream files[num];
    for (int i=0; i<num; i++){
        string filename = to_string(i)+".txt";

        files[i] = ifstream(filename);
        int val;
        files[i] >> val;
        s.insert(make_pair(val, i));
    }

    vector<int> data;
    ofstream f;
    f.open("out.txt");
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
                for (int i=0; i<data.size(); i++) {
                    f << data[i] << ' ';
                }

            data.clear();
        }

    }
   for (int i=0; i<data.size(); i++) {
                    f << data[i] << ' ';
                }
    for (int i=0;i<num;i++){
        files[i].close();
    }
    f.close();
}

