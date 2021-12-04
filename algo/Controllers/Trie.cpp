#include "Trie.h"


Trie::Trie() {
    memset(to, -1, sizeof(int) * 128);

    for (char c = 'a'; c <= 'z'; c++) {
        to[c] = c - 'a';
    }
    for (char c = '0'; c <= '9'; c++) {
        to[c] = c - '0' + 26;
    }
    to['/'] = 36;
    to['?'] = 37;
    to['='] = 38;
    trie.push_back(Node());
}

void Trie::buildTrie(vector<string> &controllers) {
    int i = 0;
    for (string &controller: controllers) {
        int pos = 0;
        for (char c: controller) {
            int p = to[c];
            if (trie[pos].next[p] == -1) {
                trie[pos].next[p] = trie.size();
                trie.push_back(Node());
            }
            pos = trie[pos].next[p];
        }
        trie[pos].val = i;
        i++;
    }
}

int Trie::findString(string &s) {
    int res = -1, pos = 0;
    for (char c: s) {
        int p = to[c];

        if (trie[pos].next[p] == -1) {
            break;
        }
        pos = trie[pos].next[p];
        if (trie[pos].val != -1) {
            res = trie[pos].val;
            break;
        }
    }
    return res;
}
