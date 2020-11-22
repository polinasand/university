#include "Cryptography.h"
using namespace std;

const BigInt Cryptography::euler(const BigInt& n) {
    map<BigInt, int> factors;
    factor(n, factors);
    BigInt ans = BigInt(1);
    for (auto factor = factors.begin(); factor != factors.end(); factor++) {
        BigInt p = factor->first, k = BigInt(factor->second);
        ans = ans * pow(p, k-1, 0) * (p-1);
    }
    return ans;
}

const int Cryptography::mobius(const BigInt&n) {
    map<BigInt, int> factors;
    factor(n, factors);
    int ans = 1;
    for (auto factor = factors.begin(); factor != factors.end(); factor++) {
        if (factor->second > 1)
            return 0;
        ans *= (-1);
    }
    return ans;
}

const int Cryptography::legendre(const BigInt& a, const BigInt& p) {
    return pow(a, (p-BigInt(1))/BigInt(2), p) == BigInt(1) ? 1 : -1;
}

const int Cryptography::jacobi(const BigInt& a, const BigInt& m) {
    map<BigInt, int> factors;
    factor(m, factors);
    int ans = 1;
    for (auto factor = factors.begin(); factor != factors.end(); factor++) {
        BigInt p = factor->first, pow = BigInt(factor->second);
        if (pow % BigInt(2) == 1)
            ans *= legendre(a, p);
    }
    return ans;
}

const BigInt Cryptography::discrete_log(const BigInt& n) {
    return BigInt("1");
}
const BigInt Cryptography::discrete_sqrt(const BigInt& n) {
    return BigInt("1");
}

// Miller-Rabin
const bool Cryptography::isPrime(const BigInt& a) {
    if (a == BigInt(1))
        return false;
    if (a == BigInt(2) || a == BigInt(3))
        return true;
    if (gcd(a, BigInt(6)) > BigInt(1))
        return false;

    BigInt q = a - BigInt(1);
    BigInt n = BigInt(0);
    while (q % BigInt(2) == BigInt(0)) {
        q = q / BigInt(2);
        n = n + BigInt(1);
    }
    int i = Cryptography::N;
    while (i > 0) {
        i--;
        BigInt k = a / BigInt(2);
        BigInt b = pow(k, q, a);
        if (b == BigInt(1))
            continue;
        BigInt j = BigInt(0);
        while (b != a - BigInt(1) && j < n) {
            b = pow(b, BigInt(2), a);
            j = j + BigInt(1);
        }
        if (b == a - BigInt(1))
            continue;
        if (j == n)
            return false;
    }
    return true;
}

// help function for Pollard's algorithm
const BigInt f(const BigInt& x) {
    return x*x - BigInt(1);
}
// trivial factorization for small numbers
BigInt trivialFactor(const BigInt& n) {
    if (n % BigInt(2) == BigInt(0))
        return BigInt(2);
    for (BigInt i = BigInt(3); i*i <= n; i = i + BigInt(1)) {
        if (n % i == BigInt(0))
            return i;
    }
    return BigInt(1);
}

// Pollard's algorithm
const BigInt findFactor(const BigInt& n, BigInt x0) {
    BigInt x_0 = x0, x_i = f(x_0) % n, x_2i = f(x_i) % n, d = BigInt(1);
    int max_iter = 1000, i = 0;
    while (i < max_iter && (d == BigInt(1) || d == n)) {
        d = gcd(n, abs(x_i - x_2i));
        x_i = f(x_i) % n;
        x_2i = f(f(x_2i)% n) % n;
        i++;
    }
    if (d == n || d == BigInt(1)) {
        return trivialFactor(n);
	}
    return d;
}
const void Cryptography::factor(const BigInt& n, map<BigInt, int>& factors) {
    if (n == BigInt(1)) {
        return;
    }
    if (isPrime(n)) {
        auto it = factors.find(n);
        if (it != factors.end()) {
            int power = it->second;
            factors.insert(pair<BigInt, int>(n, power+1));
        }
        else {
            factors.insert(pair<BigInt, int>(n, 1));
        }
        return;
    }
    BigInt d = BigInt(1);
    BigInt i = BigInt(2);
    while (d == BigInt(1) || d == n) {
        d = findFactor(n, i);
        i = i + BigInt(1);
    }

    auto it = factors.find(d);
        if (it != factors.end()) {
            int power = it->second;
            factors.insert(pair<BigInt, int>(d, power+1));
        }
        else {
            factors.insert(pair<BigInt, int>(d, 1));
        }
    cout << d << endl;
    factor(n/d, factors);
}
