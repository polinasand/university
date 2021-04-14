#include "rsa.h"
#include "BigInt/BigInt.h"
#include "prime_gen.h"

RSA::RSA(int len) {
    BigInt p = prime_gen::nextPrime(len);
    BigInt q = prime_gen::nextPrime(len);
    n = p*q;
    BigInt phi_n = lcm(p-BigInt(1), q-BigInt(1));
    public_key = prime_gen::nextPrime(len/2);
    private_key = Cryptography::inverseEl(public_key, phi_n);
}

vector<BigInt> RSA::sendMessage(const string message) {
    this->signature = this->sign(message, public_key, private_key, n);
    return encrypt(message, this->public_key, this->n);
}

string RSA::receiveMessage(vector<BigInt>& ciphertext) {
    string message = decrypt(ciphertext, this->private_key, this->n);
    if (verify(message, this->signature))
        return message;
    return "==Wrong signature==\n";
}

const BigInt RSA::_encrypt(const BigInt& m, const BigInt& public_key, const BigInt& modulo){
    return pow(m, public_key, modulo);
}

const BigInt RSA::_decrypt(const BigInt& c, const BigInt& private_key, const BigInt& modulo){
    return pow(c, private_key, modulo);
}

vector<BigInt> RSA::encrypt(const string message, const BigInt& public_key, const BigInt& modulo) {
    vector<BigInt> M = stringToInt(message);
    vector<BigInt> ciphertext;
    for (auto byte : M) {
        ciphertext.push_back(_encrypt(byte, public_key, modulo));
    }
    return ciphertext;
}

string RSA::decrypt(vector<BigInt> &ciphertext, const BigInt& private_key, const BigInt& modulo) {
    vector<BigInt> M;
    for (auto byte : ciphertext) {
        M.push_back(_decrypt(byte, private_key, modulo));
    }
    return intToString(M);
}

vector<BigInt> RSA::stringToInt(const string& s) {
    vector<BigInt> ans;
    for (int i=0; i<s.size(); i++){
        ans.push_back((int)s[i] );
    }
    return ans;
}

string RSA::intToString(vector<BigInt>& m){
    string ans = "";
    for (auto byte : m){
        byte.toBytes();
        ans += (char)byte.bytes[0];
    }
    return ans;
}

// sign
RSA::Signature RSA::sign(const string& message, const BigInt& pub_key, const BigInt& pr_key, const BigInt& n) {
    RSA::Signature signature;
    signature.public_key = pub_key;
    signature.n = n;
    signature.signatures = RSA::encrypt(message, pr_key, signature.n);
    return signature;
}

bool RSA::verify(const string& message, RSA::Signature signature) {
    return message == decrypt(signature.signatures, signature.public_key, signature.n);
}
