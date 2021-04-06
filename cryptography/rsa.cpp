#include "rsa.h"
#include "BigInt/BigInt.h"
#include "prime_gen.h"

RSA::RSA(int len) {
    BigInt p = prime_gen::nextPrime(len);
    BigInt q = prime_gen::nextPrime(len);
    n = p*q;
    BigInt phi_n = Cryptography::carmichael(n);

    public_key = prime_gen::nextPrime(10); // todo:
    private_key = Cryptography::inverseEl(public_key, phi_n);
}

const BigInt RSA::_encrypt(const BigInt& m, const BigInt& public_key, const BigInt& modulo){
    return pow(m, public_key, modulo);
}

const BigInt RSA::_decrypt(const BigInt& c, const BigInt& private_key, const BigInt& modulo){
    return pow(c, private_key, modulo);
}

vector<BigInt> RSA::encrypt(const string message, const BigInt& public_key, const BigInt& modulo) {
    return encrypt(stringToVector(message, public_key, modulo));
}
vector<BigInt> RSA::encrypt(vector<BigInt> &message, const BigInt& public_key, const BigInt& modulo) {
    vector<BigInt> ans;
    for (auto symbol : message)
        ans.push_back(_encrypt(symbol, public_key, modulo));
    return ans;
}

string RSA::decrypt(vector<BigInt> &ciphertext, const BigInt& private_key, const BigInt& modulo) {
    return vectorToString(decrypt(ciphertext, private_key, modulo));
}

vector<BigInt> RSA::decrypt(vector<BigInt> &ciphertext, const BigInt& private_key, const BigInt& modulo) {
    vector<BigInt> ans;
    for (auto symbol : ciphertext)
        ans.push_back(_decrypt(symbol, private_key, modulo));
    return ans;
}

vector<BigInt> RSA::stringToVector(const string& s) {
    vector<BigInt> ans;
    for (int i=0; i<s.size(); i++){
        ans.push_back(BigInt(s[i]));
    }
    return ans;
}
string RSA::vectorToString(vector<BigInt>& m){
    string ans = "";
    for (int i=0; i<m.size(); i++){
  //      ans += (char)BigInt::toInt(m[i]);
    }
    return ans;
}

// sign
Signature sign(const string& message, const BigInt& pub_key, const BigInt& pr_key, const BigInt& n) {
    RSA::Signature signature;
    signature.public_key = pub_key;
    signature.n = n;
    signature.signatures = RSA::encrypt(message, pr_key, signature.n);
    return signature;
}

bool verify(const& string message, Signature signature) {
    return message == RSA::vectorToString(RSA::decrypt(signature.signatures, signature.public_key, signature.n));
}
