#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    string s1, s2, s3;
    while (true) {
        cin>>s1;
        cin>>s2;
        cin>>s3;
        BigInt a = BigInt(s1);
        BigInt b = BigInt(s2);
        BigInt c = BigInt(s3);
        BigInt d = (a * b) % c;
        cout<< d;
    }

    return 0;
}
