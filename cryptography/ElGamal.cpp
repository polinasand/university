#include "ElGamal.h"
#include "Cryptography.h"

using namespace std;

const Point ElGamal::add(const Point& P, const Point& Q, const curve& e) {
    if (P.zero) return Q;
    if (Q.zero) return P;
    Point R = Point(BigInt(0), BigInt(1), false);
    if (P.x == Q.x && (P.y != Q.y || (P.y == BigInt(0) && Q.y == BigInt(0)))){
        R.zero = true;
        return R;
    }
    BigInt m, n;
    if (P.x == Q.x && P.y == Q.y && P.y != BigInt(0)) {
        m = (BigInt(3)*P.x*P.x + e.a) * Cryptography::inverseEl(BigInt(2) * P.y, e.n);
        n = (-P.x * P.x * P.x + e.a * P.x + BigInt(2)*e.b) * Cryptography::inverseEl(BigInt(2) * P.y, e.n);
        n = n % e.n;
    } else {
        m = (Q.y - P.y)*Cryptography::inverseEl(Q.x - P.x, e.n);
        n = (P.y*Q.x-Q.y*P.x) * Cryptography::inverseEl(Q.x-P.x, e.n);
        n = n % e.n;
    }
    m = m % e.n;
    //R.x = (m - P.x - Q.x) % e.n;
    //R.y = (-m*m*m + m*(P.x+Q.x) - n) % e.n;
    R.x = (m*m - (P.x + Q.x));
	R.y = -P.y + m * (P.x - R.x);
	R.x = R.x % e.n;
	R.y = R.y % e.n;
    return R;
}

const void ElGamal::elGamal() {
    BigInt k, m;
    // secp192
    /*a = BigInt(2), b = BigInt(3), p = BigInt(67), N = p, x = BigInt(2), y = BigInt(22);
    curve e = curve(a, b, p);
    N = N > p ? p : N;
    Point P = Point(x, y, false);*/
    /*curve e = curve(BigInt(0), BigInt(3), BigInt("6277101735386680763835789423207666416102355444459739541047"));
    Point P = Point(BigInt("2"), BigInt("")
                           Cryptography::discrete_sqrt(
                                (pow(BigInt("67"), BigInt(3), e.n) + e.a*BigInt("67") + e.b) % e.n, e.n), false);
    BigInt N = BigInt("6277101735386680763835789423207666416102355444459739541047");*/
    curve e = curve(BigInt(0), BigInt(13), BigInt(133));
    Point P = Point(BigInt("29"), BigInt(76), false);

    BigInt N = BigInt(133);
    k = (P.x * P.y) % N;
    BigInt k1 = k % N;
    Point Y = Point(P.x, P.y, false);
    while (k1 > BigInt(1)) {
        k1 = k1 - BigInt(1);
        Y = ElGamal::add(
                         Point(P.x % e.n, P.y % e.n, false),
                         Point(Y.x % e.n, Y.y % e.n, Y.zero),
                         e);
    }
    cout << "public key: curve with params " << e.a << ' ' << e.b << ' ' << e.n
    <<"; N = " << N <<"; P = (" << P.x << "; " << P.y << "), Y = (" << Y.x << "; " << Y.y << ")," << endl;
    // encryption r = 2
    cout << "Input 0 < [m] < N" << endl;
    cin >> m;
    BigInt y = ((m*m*m)%e.n + e.a*m + e.b) % e.n;
    BigInt my = Cryptography::discrete_sqrt(y, e.n), mx = m;
    BigInt rv = (my * my) % e.n, rl = (pow(mx, BigInt(3), e.n) + mx*e.a + e.b) % e.n;
    while (rv != rl) {
        mx = (mx + BigInt(1)) % e.n;
        y = ((mx*mx*mx)%e.n + e.a*mx + e.b) % e.n;
        my = Cryptography::discrete_sqrt(y, e.n);
        rv = (my * my) % e.n, rl = (pow(mx, BigInt(3), e.n) + mx*e.a + e.b) % e.n;
    cout << rv << " g " << rl << endl;
    }
    Point M = Point(mx, my, false);
    cout << "Point M = " << M.x << ' ' << M.y << endl;
    Point g = ElGamal::add(P, P, e);
    Point h = ElGamal::add(M, ElGamal::add(Y, Y, e), e);
    cout << "ciphertext: g = " << g.x << ' ' << g.y << " h = " << h.x << ' ' << h.y << endl;
    cout << "Y =" << Y.x << ' ' << Y.y << " k =" << k << endl;
    // decryption
    Point S = g;
    while (k > BigInt(1)) {
        k = k - BigInt(1);
        S = ElGamal::add(
                         Point(g.x, g.y, g.zero),
                         Point(S.x, S.y, S.zero),
                         e);
    }
    S.y = (-S.y) % e.n;
    Point ansM = ElGamal::add(S, h, e);
    cout << "Message Point " << ansM.x << ' ' << ansM.y << ansM.zero <<endl;
}
