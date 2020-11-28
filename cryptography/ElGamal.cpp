#include "ElGamal.h"
#include "BigInt/BigInt.h"
#include "Cryptography.h"

using namespace std;

ElGamal::ElGamal() {
    // x: DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D
    // y: 9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D
    // p: FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37
    this->e = curve(BigInt(0), BigInt(3), BigInt("6277101735386680763835789423207666416102355444459739541047"));
    this->P = Point(BigInt("5377521262291226325198505011805525673063229037935769709693"),
                    BigInt("3805108391982600717572440947423858335415441070543209377693")
                           , false);
    this->N = BigInt("6277101735386680763835789423207666416102355444459739541047");
    this->k = BigInt::random(sqrt(sqrt(N)));
    this->Y = ElGamal::mult(P, k, e);
    cout << "Public key: curve with params " << e.a << ' ' << e.b << ' ' << e.n
    <<";\nN = " << N <<";\nP = (" << P.x << "; " << P.y << "),\nY = (" << Y.x << "; " << Y.y << ")" << endl;
    Point G = Point(BigInt(0), BigInt(1), false);
    for (int i = 0; i < 256; i++) {
        G = add(G, P, e);
        this->intToPoint[i] = G;
    }
    cout << "Keys created" << endl;
}

ElGamal::ElGamal(curve e, Point P) {
    this->e = e;
    this->P = P;
}
const Point ElGamal::add(const Point& P, const Point& Q, const curve& e) {
    if (P.zero) return Q;
    if (Q.zero) return P;
    Point R = Point(BigInt(0), BigInt(1), false);
    if (P.x == Q.x && (P.y != Q.y || (P.y == BigInt(0) && Q.y == BigInt(0)))){
        R.zero = true;
        return R;
    }
    BigInt m;
    if (P.x == Q.x && P.y == Q.y && P.y != BigInt(0)) {
        m = (BigInt(3)*P.x*P.x + e.a) * Cryptography::inverseEl(BigInt(2) * P.y, e.n);
    } else {
        m = (Q.y - P.y)*Cryptography::inverseEl(Q.x - P.x, e.n);
    }
    m = m % e.n;
    R.x = (m*m - (P.x + Q.x));
	R.y = -P.y + m * (P.x - R.x);
	R.x = R.x % e.n;
	R.y = R.y % e.n;
    return R;
}

const Point ElGamal::addV(const Point&P , const Point&Q, const curve& e, BigInt& d){
    if (P.zero) return Q;
    if (Q.zero) return P;
    Point R = Point(BigInt(0), BigInt(1), false);
    if (P.x == Q.x && (P.y != Q.y || (P.y == BigInt(0) && Q.y == BigInt(0)))){
        R.zero = true;
        return R;
    }
    BigInt m, x, y;
    d = BigInt(1);
    if (P.x == Q.x && P.y == Q.y && P.y != BigInt(0)) {
        if (gcd(BigInt(2) * P.y, e.n, x, y) > d)
            d = gcd(BigInt(2) * P.y, e.n, x, y);
        m = (BigInt(3)*P.x*P.x + e.a) * Cryptography::inverseEl(BigInt(2) * P.y, e.n);
    } else {
        if (gcd(Q.x - P.x, e.n, x, y) > d)
            d = gcd(Q.x - P.x, e.n, x, y);
        m = (Q.y - P.y)*Cryptography::inverseEl(Q.x - P.x, e.n);
    }
    m = m % e.n;
    R.x = (m*m - (P.x + Q.x));
	R.y = -P.y + m * (P.x - R.x);
	R.x = R.x % e.n;
	R.y = R.y % e.n;
    return R;
}

const Point ElGamal::mult(const Point& a, const BigInt& n, const curve& e) {
    Point ans = Point(BigInt(0), BigInt(1), true);
    BigInt p = n;
    Point mult = a;
    while (p > BigInt(0)) {
        BigInt pw = p % BigInt(2);
        p = p / BigInt(2);
        if (pw == BigInt(1)) {
            ans = ElGamal::add(ans, mult, e);
        }
        mult = ElGamal::add(mult, mult, e);
    }
    return ans;
}
const void ElGamal::encrypt(const string& m, vector<pair<Point, Point>>& points) {
    cout << "---Encryption message by symbols---" << endl;
    for (int i = 0; i < m.size(); i++) {
        Point M = intToPoint[int(m[i])];
        cout << "Point M = (" << M.x << ' ' << M.y <<")"<< endl;
        Point g = add(P, P, e);
        Point h = ElGamal::add(M, ElGamal::add(Y, Y, e), e);
        cout << "Ciphertext: g = (" << g.x << ' ' << g.y << ") h = (" << h.x << ' ' << h.y <<")"<< endl;
        points.push_back(pair<Point, Point>(g,h));
    }
}

const void ElGamal::decrypt(const vector<pair<Point, Point>>& cPoints, vector<Point>& mPoints) {
    cout << "---Decryption---"<<endl;
    int i = 1;
    for (auto it = cPoints.begin(); it != cPoints.end(); it++) {
        Point S = mult(it->first, k, e);
        S.y = (-S.y) % ElGamal::e.n;
        Point ansM = ElGamal::add(S, it->second, ElGamal::e);
        cout << "Symbol " << i << " is decrypted" << endl;
        i++;
        mPoints.push_back(ansM);
    }
}
const string ElGamal::makeString(const vector<Point>& points) {
    int len = points.size();
    string ans = "";
    for (int i = 0; i < len; i++) {
        Point p = points[i];
        for (int j =0; j<256; j++){
            Point curr = intToPoint[j];
            if (curr.x == p.x && curr.y == p.y) {
                ans += (char)j;
            }
        }
    }
    return ans;
}
