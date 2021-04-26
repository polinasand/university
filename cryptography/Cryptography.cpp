#include "Cryptography.h"
#include "ElGamal.h"

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

// Baby-step-giant-step
const BigInt Cryptography::discrete_log(const BigInt& g, const BigInt& b, const BigInt& n) {
    BigInt m = sqrt(n) + BigInt(1);
    BigInt gM = pow(g, m, n),p = BigInt(1);
    BigInt i, j;
    // all values for j
    map<BigInt, BigInt> rvals = map<BigInt, BigInt>();
    rvals[p] = BigInt(0);
    for (j = BigInt(1); j < m; j = j + BigInt(1)) {
        p = (p * g) % n;
        rvals[p] = j;
        if (p == g && (-j) % n != n-BigInt(1))
            return (-j) % n;
    }
    p = BigInt(1);
    for (i = BigInt(1); i < m; i = i + BigInt(1)) {
        p = (p * gM) % n;
        auto it = rvals.find((inverseEl(b, n)*p)%n);
        if (it != rvals.end()){
            if (i*m - it->second != n-BigInt(1))
                return  i*m - it->second;
        }
    }
    return BigInt("-1");
}

// find inverse element in group by modulo p
const BigInt Cryptography::inverseEl(const BigInt&a, const BigInt&p) {
    BigInt _a = a % p;
    BigInt x, y;
    BigInt d = gcd(_a, p, x, y);
    if (d > 1)
        return p;
    return x % p;
}

// Cippola
const BigInt Cryptography::discrete_sqrt(const BigInt& a, const BigInt& p) {
    if (a == BigInt(0))
        return a;
    BigInt w = BigInt(1), b = BigInt(1);
    while (legendre(w,p) == 1) {
        b = BigInt::random(p);
        w = (b*b - a) % p;
        if (w == BigInt(0))
            return b;
    }
    BigInt deg = (p+BigInt(1))/BigInt(2), wi = BigInt(1), bi = pow(b, deg, p), ci = BigInt(1);
	BigInt result = (wi * ci * bi) % p;
	for (BigInt i = BigInt(2); i <= deg; i = i + BigInt(2)){
		wi = (wi * w) % p;
		bi = pow(b, deg - i, p);
		ci = (ci * (deg - i + BigInt(2)) * (deg - i + BigInt(1))) * inverseEl((i - BigInt(1)) * i, p) % p;
		result = (result + ci * bi * wi) % p;
	}
	return result == BigInt(0) ? BigInt("-1") : result;
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
// Baillie - PSW prime test
const bool Cryptography::isPrimeBPSW(const BigInt& a) {
    if (a == BigInt(2) || a == BigInt(3) || a == BigInt(5) || a == BigInt(7))
        return true;
    if (Cryptography::isPrime(a) == false)
        return false;
    cout << "Checked Miller-Rabin\n";
    BigInt d = BigInt(5);
    int i = 0;
    while (true){
        if (Cryptography::jacobi(d, a) == -1){
            cout << "Found d in BPSW algo\n";
            break;
        }
        d = d + BigInt(2);
        i++;
        d = d * (i%2 ? BigInt(-1) : BigInt(1));
    }
    return Cryptography::isPrimeLuke(a, d, BigInt(1), (BigInt(1)-d)/BigInt(4));
}

// Luke prime test
const bool Cryptography::isPrimeLuke(const BigInt& n, const BigInt& d, const BigInt& p, const BigInt& q) {
    BigInt k = n, t, add;
    BigInt u = BigInt(1);
    BigInt v = p;
    while (k > BigInt(0)){
        t = k % BigInt(2);
        k = k / BigInt(2);
        u = u*v;
        v = (v*v +d*u*u)/BigInt(2);
        if (t == BigInt(1)){
            add = p*u + v;
            if (add % BigInt(2) == BigInt(1))
                add = add + n;
            u = add / BigInt(2);
            add = d * u + p*v;
            if (add % BigInt(2) == BigInt(1))
                add = add + n;
            v = add / BigInt(2);
        }
        u = u % n;
        v = v % n;
    }
    add = p*u + v;
    if (add % BigInt(2) == BigInt(1))
        add = add + n;
    u = add / BigInt(2);
    return u % n == BigInt(0);
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
const BigInt findFactor(const BigInt& n) {
    BigInt x_0 = BigInt(2), x_i = f(x_0) % n, x_2i = f(x_i) % n, d = BigInt(1);
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
            it->second++;
        }
        else {
            factors[n] = 1;
        }
        return;
    }
    BigInt d = BigInt(1);
    while (d == BigInt(1) || d == n) {
        d = findFactor(n);
    }
    factor(n/d, factors);
    factor(d, factors);
}

const BigInt Cryptography::factorLenstra(const BigInt& _n)
{
    Point P = Point(BigInt(6997), BigInt(143519), false);
    BigInt n = _n, b = (P.y*P.y - pow(P.x, BigInt(3), n)) % n;
    curve e = curve(BigInt(0), b, n);
    ElGamal elGamal = ElGamal(e, P);
    BigInt i = BigInt(30);
    BigInt t = BigInt(1);
    while (i > BigInt(1)) {
        t = t * i;
        i = i - BigInt(1);
    }
    Point S = P;
    BigInt ans;
    while (t > BigInt(1)) {
        S = elGamal.addV(S, P, e, ans);
        if (ans > BigInt(1))
            return ans;
        t = t - BigInt(1);
    }
    return BigInt(1);
}

