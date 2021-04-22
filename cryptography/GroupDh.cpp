#include "GroupDh.h"

User::User(string username){
    this->username = username;
    this->private_key = prime_gen::nextPrime(8);
}

User::getUsername() {
    return username;
}
User::encryptMessage() {
}

User::decryptMessage() {
}

GroupDH::GroupDH(int len) {
    bool done = false;
    vector<int> factors;
    while (!done) {
        modulo = prime_gen::nextPrime(len);
        Cryptography::factor(modulo-1, factors);
        for (BigInt m=2; m <= modulo; m++) {
            done = true;
            for (auto factor:factors) {
                done &= pow(m, (modulo-1)/factor, modulo) != 1;
                if (!done)
                    break;
            }
            if (done) {
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
    users[user.getUsername()] = user;
}

BigInt GroupDH::getGenerator() {
    return g;
}
BigInt GroupDH::getModulo() {
    return modulo;
}

void GroupDH::createKey() {
    int n = users.size();
    for (int i=0; i<n; i++) {
        BigInt data = users[i].send(g, modulo);
        for (int j=i+1; j<(n+i-1) % n; j++){
            if (i==j)
                continue;
            data = users[j].send(data, modulo);
        }
        users[(i+n) % n].setSecret(data);
    }
}

void User::send(const BigInt& data, const BigInt& modulo) {
    return pow(data, this->private_key, modulo);
}
