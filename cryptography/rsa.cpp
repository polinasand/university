#include "rsa.h"
#include "BigInt/BigInt.h"
#include "prime_gen.h"

RSA::RSA(int len) {
    BigInt p = prime_gen::nextPrime(len);
    cout << "p generated ";
    BigInt q = prime_gen::nextPrime(len);
    cout << "q generated ";
    n = p*q;
    BigInt phi_n = Cryptography::carmichael(p, q);
    cout << phi_n << ' ' << (p-1)*(q-1) << endl;
    public_key = prime_gen::nextPrime(10); // todo:
    private_key = Cryptography::inverseEl(public_key, phi_n);
}

vector<BigInt> RSA::sendMessage(const string message) {
    return encrypt(message, this->public_key, this->n);
}

string RSA::receiveMessage(vector<BigInt>& ciphertext) {
    return decrypt(ciphertext, this->private_key, this->n);
}

const BigInt RSA::_encrypt(const BigInt& m, const BigInt& public_key, const BigInt& modulo){
    return pow(m, public_key, modulo);
}

const BigInt RSA::_decrypt(const BigInt& c, const BigInt& private_key, const BigInt& modulo){
    return pow(c, private_key, modulo);
}

vector<BigInt> RSA::encrypt(const string message, const BigInt& public_key, const BigInt& modulo) {
    BigInt M = stringToInt(message);
    vector<BigInt> ciphertext;
    M.toBytes();
    for (auto byte : M.bytes) {
        ciphertext.push_back(_encrypt(BigInt(byte), public_key, modulo));
    }
    return ciphertext;
}

string RSA::decrypt(vector<BigInt> &ciphertext, const BigInt& private_key, const BigInt& modulo) {
    BigInt M = BigInt(0);
    for (auto byte : ciphertext) {
        M = M * BigInt(256);
        M = M + _decrypt(byte, private_key, modulo);
    }
    return intToString(M);
}

BigInt RSA::stringToInt(const string& s) {
    BigInt ans = BigInt(0);
    for (int i=0; i<s.size(); i++){
        ans = ans * BigInt(256);
        ans = ans + (int)s[i];
    }
    return ans;
}

string RSA::intToString(BigInt& m){
    string ans = "";
    m.toBytes();
    for (auto byte : m.bytes){
        cout << byte << ' ';
        ans += (char)byte;
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
