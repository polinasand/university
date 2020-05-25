#include<iostream>
using namespace std;
#include<vector>

vector<int> SortCharacters(string &s);
vector<int> BuildSuffixArray(string &s);
vector<int> ComputeCharClasses(string &s, vector<int>);
vector<int> SortDoubled(string&, int, vector<int>, vector<int>);
vector<int> UpdateClasses(vector<int>, vector<int>, int);

int main()
{
    string s;
    cin>>s;
    vector<int> ans = BuildSuffixArray(s);
    for (auto i:ans)
        cout<<i<<' ';
}

vector<int> SortCharacters(string &s) //типа сложная сортировка подсчетом
{
    vector<int> order(s.size());
    vector<int> c(5);

    for (int i =0; i<s.size(); i++){
        switch(s[i]){
        case '$':
            c[0]++;
            break;
        case 'A':
            c[1]++;
            break;
        case 'C':
            c[2]++;
            break;
        case 'G':
            c[3]++;
            break;
        case 'T':
            c[4]++;
            break;
        default:
            break;
        }
    }
    for (int j = 1; j<5; j++){
        c[j] += c[j-1];
    }
    for (int i = s.size()-1; i>=0; i--){
        switch(s[i]){
        case '$':
            c[0]--;
            order[c[0]] = i;
            break;
        case 'A':
            c[1]--;
            order[c[1]] = i;
            break;
        case 'C':
            c[2]--;
            order[c[2]] = i;
            break;
        case 'G':
            c[3]--;
            order[c[3]] = i;
            break;
        case 'T':
            c[4]--;
            order[c[4]] = i;
            break;
        default:
            break;
        }

    }
    return order;
}
vector<int> ComputeCharClasses(string &s, vector<int> order)
{
    vector<int> classes(s.size());
    int t = 0;
    classes[order[0]] = 0;
    for (int i = 1; i<s.size(); i++){
        if (s[order[i]] != s[order[i-1]])
            classes[order[i]] = classes[order[i-1]]+1;
        else
            classes[order[i]] = classes[order[i-1]];
        }
    return classes;
}
vector<int> SortDoubled(string& s, int l, vector<int> order, vector<int> classes)
{
    int slen = s.size();
    vector<int> c(slen);
    vector<int> newOrder(slen);
    for (int i =0; i<slen; i++){
        c[classes[i]]++;
    }
    for (int i =1 ; i<slen; i++){
        c[i] += c[i-1];
    }
    for (int i = slen-1; i>=0; i--){
        int start = (order[i]-l+slen) % slen;

        newOrder[--c[classes[start]]] = start;
    }
    return newOrder;
}

vector<int> UpdateClasses(vector<int> order, vector<int> classes, int l){
    int n = order.size();
    vector<int> newClass(n);
    newClass[order[0]] = 0;
    for (int i =1; i<n; i++){
        int curr = order[i], prev = order[i-1];
        int mid = (curr+l) % n, midprev = (prev+l) % n;
        if (classes[curr] != classes[prev] || classes[mid] != classes[midprev]){
            newClass[curr] = newClass[prev] + 1;
        }
        else{
            newClass[curr] = newClass[prev];
        }
    }
    return newClass;
}

vector<int> BuildSuffixArray(string &s){
    vector<int> order = SortCharacters(s);
    vector<int> classes = ComputeCharClasses(s, order);
    int l = 1;
    while (l<s.size()){
        order = SortDoubled(s,l,order,classes);
        classes = UpdateClasses(order, classes, l);
        l *= 2;
    }
    return order;
}
