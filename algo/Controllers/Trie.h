#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Trie{
    class Node {
    public:
        int val;
        int next[40];

        Node() {
            val = -1;
            for (auto &it: next) {
                it = -1;
            }
        }
    };
    vector<Node> trie;
    int to[128];

public:

    Trie();
    void buildTrie(vector<string>&);
    int findString(string&);
};

