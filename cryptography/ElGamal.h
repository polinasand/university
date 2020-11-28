#pragma once
#include "BigInt/BigInt.h"
#include "Cryptography.h"
#include<iostream>
using namespace std;

struct Point {
    BigInt x;
    BigInt y;
    bool zero;
    Point() {
        x = BigInt(0);
        y = BigInt(0);
        zero = false;
    }
    Point(BigInt _x, BigInt _y, bool _zero) {
        x = _x;
        y = _y;
        zero = _zero;
    }
};

struct curve {
    BigInt a;
    BigInt b;
    BigInt n;
    curve() {
        a = BigInt(0);
        b = BigInt(3);
        n = BigInt("6277101735386680763835789423207666416102355444459739541047");
    }
    curve(BigInt _a, BigInt _b, BigInt _n) {
        a = _a;
        b = _b;
        n = _n;
    }
};

class ElGamal {
private:
    curve e;
    Point P;
    BigInt N;
    Point Y;
    BigInt k;

public:
    ElGamal();
    ElGamal(curve e, Point P);
    map<int, Point> intToPoint;
    const Point add(const Point&, const Point&, const curve&);
    const Point addV(const Point&, const Point&, const curve&, BigInt&);
    const Point mult(const Point&, const BigInt&, const curve&);
    const void encrypt(const string&, vector<pair<Point, Point>>&);
    const void decrypt(const vector<pair<Point, Point>>& , vector<Point>& );
    const string makeString(const vector<Point>&);
};
