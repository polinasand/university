#include<iostream>
using namespace std;
#include<vector>

class Trie {
public:
    Trie *children[4] = {};
    bool isEndOfWord = false;

    Trie() {
        Trie *children[4] = {};
        bool isEndOfWord = false;
    }

    Trie* getNode(){
        Trie *pNode =  new Trie();

        pNode->isEndOfWord = false;

        for (int i = 0; i < 4; i++)
            pNode->children[i] = NULL;

        return pNode;
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* p = this;
        for (int i = 0; i < word.length(); i++){
            int index = 0;
			switch(word[i]){
				case 'A':
					index = 0;
					break;
				case 'C':
					index = 1;
					break;
				case 'G':
					index = 2;
					break;
				case 'T':
					index = 3;
					break;
				default:
					break;
			}
		//	cout<<index<<' ';
            if (!p->children[index]) // letter in tree not find
                p->children[index] = getNode(); //created new empty trie for yhe rest of word

            p = p->children[index]; // move to next point
        }
        p->isEndOfWord = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string &s, int x) {
        Trie *p = this;
        for (int i = x ; i<s.length(); i++){
            if (p->isEndOfWord)
                return true;
            int index = 0;
			switch(s[i]){
				case 'A':
					index = 0;
					break;
				case 'C':
					index = 1;
					break;
				case 'G':
					index = 2;
					break;
				case 'T':
					index = 3;
					break;
				default:
					break;
			}
			//cout<<word[i]<<' ';
            if (!p->children[index])
                return false;

            p = p->children[index];
        }
        return (p != NULL && p->isEndOfWord);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string word) {
        Trie *p = this;
        for (int i =0; i < word.length(); i++){
            int index = word[i] - 'a';
            if (!p->children[index])
                return false;
            p = p->children[index];
        }
        return true;
    }
};
int main()
{
	string s;
	Trie* tree = new Trie();
	long long t;
	//set<int> p;
	int ans[10000] = {};
	int r = 0;
	cin>>s;
	cin>>t;
	for (int i=0; i<t; i++){
		string s1;
		cin>>s1;
		tree->insert(s1);
		//p.insert(s1.size());
	}
	int l = s.size();
	for (int i = 0; i<l; i++){
		if (tree->search(s, i)){
            ans[r] = i;
            r += 1;
		}
	}
	for (int i=0;i<r;i++)
		cout<<ans[i]<<' ';
}

