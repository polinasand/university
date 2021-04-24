#include "GroupDh.h"
#include "prime_gen.h"

User::User(){
}
User::User(string username){
    this->username = username;
    this->private_key = prime_gen::nextPrime(5);
}

string User::getUsername() {
    return username;
}

BigInt User::send(const BigInt& data, const BigInt& modulo) {
    return pow(data, this->private_key, modulo);
}

void User::setSecret(BigInt& data) {
    secret = data;
}

BigInt User::getPrivateKey() {
    return private_key;
}

GroupDH::GroupDH(int len) {
    bool done = false;
    map<BigInt, int> factors;
    while (!done) {
        modulo = prime_gen::nextPrime(len);
        //modulo = 23;
        Cryptography::factor(modulo-1, factors);
        BigInt m;
        for (m=2; m <= modulo; m=m+1) {
            done = true;
            for (auto factor : factors) {
                done &= pow(m, (modulo-1)/factor.first, modulo) != 1;
                if (!done)
                    break;
            }
            if (done && m != modulo) {
                g = m;
                cout << "Generator g = " << g << " for modulo " << modulo << endl;
                return;
            }
        }
        if (m==modulo){
            cout << "cannot find primitive root for " << modulo << endl;
            return;
        }
    }

}

void GroupDH::addUser(User user) {
    users.push_back(user);
    keys.push_back(BigInt(0));
    cout << "Add user " << user.getUsername() <<" with private key " << user.getPrivateKey()<< endl;
}

BigInt GroupDH::getGenerator() {
    return g;
}
BigInt GroupDH::getModulo() {
    return modulo;
}

void GroupDH::createKey() {
    int n = (int)users.size();
    for (int i=0; i<n; i++) {
        BigInt data = users[i].send(g, modulo);
        for (int j=i+1; j != i+1; j++){
            j %= n;
            if (i==j)
                continue;
            data = users[j].send(data, modulo);
        }
        users[(i+n) % n].setSecret(data);
        cout << "user got secret "<<data<<endl;
        keys[(i+n)%n] = data;
    }
}

void GroupDH::sendMessage(Message message) {
    unsigned int * h = sha.hash(message.data);
    int l = message.data.size(), outLen;
    unsigned char data[l] = message.data;
    unsigned char key[32];
    for (int i=0; i<32; i++){
         BigInt k = message.sender.getPrivateKey();
         k.toBytes();
         key[i] = k.bytes[0];
    }
    cout << key << endl;
    unsigned int * cipher = aes.Encrypt(data, l, key, outLen);
    cout << cipher << endl;
}


