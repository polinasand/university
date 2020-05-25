#include<iostream>
using namespace std;
#include<vector>

vector<int> ComputePrefixFunction(string &p)
{
    int plen = p.size();
    vector<int> s(plen);
    for (int i=0; i<plen; i++)
        s[i] = 0;
    int border = 0;

    for (int i=1; i<plen; i++){
        while (border>0 && p[i] != p[border]){
                border = s[border-1];
        }
        if (p[i] == p[border]){
            border ++;
        }
        else{
            border = 0;
        }
        s[i] = border;
    }

    return s;
}

vector<int> FindAllOccurrences(string &p, string &t){
    int plen = p.size();
    string text = p+'$'+t;
    int textlen = text.size();
    vector<int> s = ComputePrefixFunction(text);
    int j = 0;
    vector<int> ans = {};
    for (int i=plen+1; i<textlen; i++){
        if (s[i] == plen)
            ans.push_back(i - 2*plen);
    }
    return ans;
}

int main()
{
    string p, t;
    cin>>p>>t;
    vector<int> ans = FindAllOccurrences(p,t);
    for(auto i:ans)
        cout<<i<<' ';

}
