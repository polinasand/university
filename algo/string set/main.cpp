#include <iostream>
#include "StringSet.h"
using namespace std;


int main()
{
    StringSet newSet;
    string s;
    while(getline(cin, s)) {
        char sign = s[0];
        s.replace(0, 2, "");
        bool ans;
        switch(sign) {
        case '#':
            return 0;
            break;
        case '+':
            ans = newSet.add(s);
            break;
        case '-':
            ans = newSet.rm(s);
            break;
        case '?':
            ans = newSet.contains(s);
            break;
        default:
            break;
        }
        cout << (ans ? "true" : "false") << endl;
        newSet.iterate();
    }

       return 0;
}
