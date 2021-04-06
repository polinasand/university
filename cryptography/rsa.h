#include "BigInt/BigInt.h"

class RSA{
private:
    BigInt private_key; // d
    int len;
    vector<BigInt> message;
    const BigInt _encrypt(const BigInt &m, const BigInt&, const BigInt& modulo);
    const BigInt _decrypt(const BigInt &c, const BigInt&, const BigInt& modulo);
    vector<BigInt> encrypt(vector<BigInt>& message, const BigInt&, const BigInt& modulo);
	vector<BigInt> decrypt(vector<BigInt>& ciphertext, const BigInt&, const BigInt& modulo);
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
    vector<BigInt> encrypt(const string, const BigInt&, const BigInt&);
    string decrypt(vector<BigInt> &c, const BigInt& , const BigInt& modulo);
	vector<BigInt> stringToVector(const string& s);
    string vectorToString(vector<BigInt>& m);
    // sign
    Signature sign(const string& message, const BigInt&, const BigInt&, const BigInt&);
    bool verify(const& string message, Signature signature);
};
