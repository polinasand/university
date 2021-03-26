#include <iostream>
#include "BigInt/BigInt.cpp"
#include "Cryptography.h"
#include "ElGamal.h"
#include "prime_gen.h"

using namespace std;

void info();
void error();
void process();
bool processLine(BigInt &, BigInt &, BigInt &);

int main()
{
    info();
    while (true)
        process();
    return 0;
}
void info() {
    cout << "------"<< endl;
    cout << "Choose some option.\n";
    cout << "Euler function: eul a"<< endl;
    cout << "Mobius function: mob a" << endl;
    cout << "Legendre symbol: leg a p" << endl;
    cout << "Jacobi symbol: jac a p" << endl;
    cout << "is Prime with probability > 1 - 4^(1-N), N = 20: prime a" << endl;
    cout << "is Prime BPSW: primeB a" << endl;
    cout << "Discrete log: solution for g^x = b mod p: log g b p" << endl;
    cout << "Discrete sqrt: solution for x^2 = a mod p: sqrt a p" << endl;
    cout << "Factor number: factor a" << endl;
    cout << "Sum of two points on elliptic curve: ell x1 y1 z1 x2 y2 z2 a b n (z == 0 if Point is zero, else Point is not zero)" << endl;
    cout << "Add k times Point p: sell x y z k a b n"<< endl;
    cout << "El-Gamal cryptosystem: elgamal" << endl;
    cout << "Lenstra: len n" << endl;
    cout << "generate prime of len n: gen n" << endl;
    cout << "info" << endl;
    cout << "exit" << endl;
    cout << "------"<< endl;
}
void error() {
    cout << "Wrong input!" << endl;
}

bool processLine(BigInt &a, BigInt &b, BigInt &c) {
    string s;
    getline(cin, s, '\n');
    int counter = -1;
    string nums[] = {"", "", ""};
    int i = 0;
    int len = s.size();
    while (counter < 3 && i < len) {
        while (s[i] != ' ' && i < len){
            nums[counter] += s[i];
            i++;
        }
        if (s[i] == ' '){
            counter++;
            if (counter > 2)
                continue;
            while (s[i] == ' ' && i < len)
                i++;
        }
    }
    if (counter < 0)
        return false;
    a = BigInt(nums[0]);
    b = BigInt(0);
    c = BigInt(0);
    if (counter > 0)
        b = BigInt(nums[1]);
    if (counter == 2)
        c = BigInt(nums[2]);
    return true;
}

void process() {
    string command;
    BigInt a, b, c;
    if (cin>>command) {
        if (command == "exit")
            exit(0);
        if (command == "info") {
            info();
            return;
        }
        if (command == "eul") {
            if (processLine(a, b, c))
                cout << Cryptography::euler(a) << endl;
            else
                error();
        }

        if (command == "mob") {
            if (processLine(a, b, c))
                cout << Cryptography::mobius(a) << endl;
            else
                error();
        }

        if (command == "leg") {
            if (processLine(a, b, c))
                cout << Cryptography::legendre(a, b) << endl;
            else
                error();
        }
        if (command == "jac") {
            if (processLine(a, b, c))
                cout << Cryptography::jacobi(a, b) << endl;
            else
                error();
        }
        if (command == "prime") {
            if (processLine(a, b, c)){
                string ans = Cryptography::isPrime(a) ? "true" : "false";
                cout << ans << endl;
            }
            else
                error();
        }
        if (command == "primeB") {
            if (processLine(a, b, c)){
                string ans = Cryptography::isPrimeBPSW(a) ? "true" : "false";
                cout << ans << endl;
            }
            else
                error();
        }
        if (command == "log") {
            if (processLine(a, b, c))
                cout << Cryptography::discrete_log(a, b, c) << endl;
            else
                error();
        }
        if (command == "sqrt") {
            if (processLine(a, b, c))
                cout << Cryptography::discrete_sqrt(a, b) << endl;
            else
                error();
        }
        if (command == "factor") {
            if (processLine(a, b, c)) {
                map<BigInt, int> factors;
                Cryptography::factor(a, factors);
                for (auto it = factors.begin(); it != factors.end(); it++) {
                    cout << it->first << " > " << it->second << '\n';
                }
            }
            else
                error();
        }
        if (command == "ell") {
            BigInt x1, x2, y1, y2, z1, z2;
            ElGamal elGamal = ElGamal();
            if (cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> a >> b >>c) {
                Point ans = elGamal.add(
                                         Point(x1 % c, y1 % c, z1 == BigInt(0) ? true : false),
                                         Point(x2 % c, y2 % c, z2 == BigInt(0) ? true : false),
                                         curve(a, b, c));
                if (ans.zero)
                    cout << "zero\n";
                else
                    cout << "Point " << ans.x << ' ' << ans.y << '\n';
                }
            else
                error();
        }
        if (command == "sell") {
                ElGamal elGamal = ElGamal();
            BigInt x, y, z, k;
            if (cin >> x >> y >> z >> k >> a >> b >>c) {
                Point ans = elGamal.mult(
                                         Point(x % c, y % c, z == BigInt(0) ? true : false),
                                         k,
                                         curve(a, b, c));
                if (ans.zero)
                    cout << "zero\n";
                else
                    cout << "Point " << ans.x << ' ' << ans.y << '\n';
                }
            else
                error();
        }
        if (command == "elgamal") {
            ElGamal elGamal = ElGamal();
            while (true) {
                cout << "Input some message" << endl;
                string message;
                getline(cin, message);
                if (message.size() == 0)
                    continue;
                vector<pair<Point, Point>> points;
                vector<Point> mPoints;
                elGamal.encrypt(message, points);
                elGamal.decrypt(points, mPoints);
                string ans = elGamal.makeString(mPoints);
                cout << "Message: " << ans << endl;
            }
        }
        if (command == "len") {
            cin >> a;
            b = Cryptography::factorLenstra(a);
            cout << b << ' ' << a/b << endl;
        }
        if (command == "gen") {
            int n;
            cin >> n;
            b = prime_gen::nextPrime(n);
            cout << b << endl;
        }
    }
    else{
        error();
        return;
    }
}
