#include <iostream>
#include "BigInt/BigInt.cpp"
#include "Cryptography.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    BigInt a;

    while (true) {
        cin >> a;
        map<BigInt, int> factors;
        Cryptography::factor(a, factors);
        for (auto it = factors.begin(); it != factors.end(); it++) {
            cout << it->first << " - " << it->second << '\n';
        }
    }

    return 0;
}
