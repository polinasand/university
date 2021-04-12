#include "BigInt/BigInt.h"

class RSA{
private:
    BigInt private_key; // d
    int len;
    vector<BigInt> message;
    const BigInt _encrypt(const BigInt &m, const BigInt&, const BigInt& modulo);
    const BigInt _decrypt(const BigInt &c, const BigInt&, const BigInt& modulo);
    vector<BigInt> encrypt(const string, const BigInt&, const BigInt&);
    string decrypt(vector<BigInt> &c, const BigInt& , const BigInt& modulo);
public:
    struct Signature {
        vector<BigInt> signatures;
        BigInt public_key;
        BigInt n;
    };

    RSA(int len);
    BigInt n;
    BigInt public_key; // e
    // global methods for user
    vector<BigInt> sendMessage(const string);
    string receiveMessage(vector<BigInt>&);
	BigInt stringToInt(const string& s);
    string intToString(BigInt& m);
    // sign
    Signature sign(const string& message, const BigInt&, const BigInt&, const BigInt&);
    bool verify(const string& message, Signature signature);
};
