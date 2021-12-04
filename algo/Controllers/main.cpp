#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include<chrono>
#include "Trie.h"

using namespace std;

vector<string> controllers;
vector<string> qs;

const int numOfQueries = 10000000;

char genChar(int i)
{
    if (i < 26)
    {
        return 'a' + i;
    }
    else if (i < 36)
    {
        return '0' + (i - 26);
    }
    else if(i == 36)
    {
        return '/';
    }
    else if (i == 37)
    {
        return '?';
    }
    else if (i == 38)
    {
        return '=';
    }
    else
    {
        return '*';
    }
}

string genRandomStr(int len, int mod) {
    string s;
    string symbol = "";
    for (int i = 0; i < len; i++)
    {
        s += genChar(rand() % mod);
    }
    return s;
}

void genInput(int n) {
    vector<string> controllers;
    vector<string> qs;

    srand(time(nullptr));
    string s = "";
    for (int i = 0; i < n/2; i++) {
        s = genRandomStr(rand()%20, 26);
        controllers.push_back(s);
    }
    for (int i = n /2; i < n * 3 / 4; i++) {
        s = controllers[rand() % controllers.size()] + genRandomStr(rand() % 5, 26);
        controllers.push_back(s);
    }
    for (int i = n * 3 / 4; i < n; i++) {
        s = controllers[rand() % controllers.size()] + genRandomStr(rand() % 10, 26) +
                   genRandomStr(rand() % 5, 26);
        controllers.push_back(s);
    }

    ofstream inputFile("input.txt");
    inputFile << n << "\n";
    for (auto it : controllers)
    {
        inputFile << it << "\n";
    }
    inputFile << numOfQueries << "\n";

    for (int i = 0; i < numOfQueries; i++) {
        int r = rand() % 127;
        if (r < 27) {
            inputFile << genRandomStr(rand() % 20 + 3, 26) << "\n";
        } else if (r < 42){
            inputFile << genRandomStr(rand() % 30 + 3, 39) << "\n";
        } else if (r < 54) {
            inputFile << controllers[rand() % controllers.size()] << "\n";
        } else if (r < 86) {
            inputFile << controllers[rand() % controllers.size()] << "\n";
        } else {
            int iters = rand() % 5 + 1;
            s = controllers[rand() % controllers.size()];
            for (int j = 0; j < iters; j++) {
                s += "/" + genRandomStr(rand() % 10 + 2, 39);
            }
            inputFile << s << "\n";
        }
    }
    inputFile.close();

}

long long getTime(void(* f)()) {
    auto start = chrono::steady_clock::now();
    f();
    auto elapsed = std::chrono::steady_clock::now() - start;
    long long time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    return time;
}

vector<int> runBrute(int n, int q) {
    vector<int> results;

    for (int i = 0; i < q; i++) {
        int res = -1, bestLen = -1;

        for (int j = 0; j < n; j++) {
            int size = min(controllers[j].size(), qs[i].size());
            int l = 0;

            for (; l < size; l++) {
                if (controllers[j][l] != qs[i][l]) {
                    break;
                }
            }

            if (l == controllers[j].size()) {
                if (size > bestLen) {
                    res = j;
                    bestLen = l;
                }
            }
        }
        results.push_back(res);
    }
    return results;
}

void readData(int &n, int &q) {
    controllers.clear();
    qs.clear();

    string ts;
    ifstream input("input.txt");

    input >> n;
    for (int i = 0; i < n; i++) {
        input >> ts;
        controllers.push_back(ts);
    }
    input >> q;
    for (int i = 0; i < q; i++) {
        input >> ts;
        qs.push_back(ts);
    }
}

void bruteForceSolution() {

    int n, q;
    readData(n, q);
    vector<int> res = runBrute(n, q);
}

vector<int> runTrie() {
    vector<int> res;

    Trie trie;
    trie.buildTrie(controllers);
    for (int i = 0; i < qs.size(); i++) {
        res.push_back(trie.findString(qs[i]));
    }
    return res;
}

void trieSolution() {

    int n, q;
    readData(n, q);
    vector<int> res = runTrie();
}




int main() {
    genInput(1000);
    cout << getTime(bruteForceSolution) << "\n";
    cout << getTime(trieSolution);

    return 0;
}


