/* Created by sandatsian */

#include "GroupDh.h"
#define KEY_LEN 16

User::User(string username){
    this->username = username;
    this->private_key = prime_gen::nextPrime(KEY_LEN);
    Sleep(500);
}

string User::getUsername() {
    return username;
}

BigInt User::send(const BigInt& data, const BigInt& modulo) {
    return pow(data, this->private_key, modulo);
}

void User::setSecret(BigInt data) {
    data.toBytes();
    for (int i=0; i<32; i++){
        secret[i] = data.bytes[i % KEY_LEN];
    }
}

BigInt User::getPrivateKey() {
    return private_key;
}

GroupDH::GroupDH(int len) {
    bool done = false;
    map<BigInt, int> factors;
    while (!done) {
        modulo = prime_gen::nextPrime(len);
        Cryptography::factor(modulo-1, factors);
        BigInt m;
        for (m = 2; m <= modulo; m = m + 1) {
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
        if (m == modulo){
            cout << "cannot find primitive root for " << modulo << endl;
            return;
        }
    }
}

void GroupDH::addUser(User user) {
    users.push_back(user);
    cout << "Add user " << user.getUsername() <<" with private key " << user.getPrivateKey()<< endl << endl;
}

BigInt GroupDH::getGenerator() {
    return g;
}
BigInt GroupDH::getModulo() {
    return modulo;
}

void GroupDH::createKey() {
    int n = (int)users.size();
    BigInt data = 0;
    for (int i=0; i<n; i++) {
        data = users[i].send(g, modulo);
        for (int j=i+1; j % n != i; j++){
            j %= n;
            data = users[j].send(data, modulo);
        }

        users[i].setSecret(data);
        cout << "User " << users[i].getUsername() << " got secret "<<data<<endl;
    }

    data.toBytes();
    for (int i=0; i<32; i++){
        key[i] = data.bytes[i % 32];
    }
}

void GroupDH::sendMessage(Message &message) {
    SHA256* sha = new SHA256();
    AES *aes = new AES();

    //unsigned int *h = sha->hash(message.data);
    string h = sha->hash(message.data);
    unsigned int l = message.data.size(), outLen;
    unsigned char *data = new unsigned char[l+1];
    strcpy((char*)data, message.data.c_str());

    unsigned char * cipher = aes->Encrypt(data, l+1, key, outLen);
    json j;

    to_json(j, cipher, message.sender, outLen, h);
    cout << "Message created\n";
    cout << "\njson = " <<j << endl << endl;

    from_json(j, cipher, outLen, h, message.sender);
    unsigned char * res = aes->Decrypt(cipher, outLen, key);
    string s(reinterpret_cast<char const*>(res));
    message.data = s;
    for (User user : this->users){
        if (user.getUsername() != message.sender)
        cout << "User " << user.getUsername() << " received message:\n" <<
        message.data << "\nfrom " << message.sender << endl;
    }

}


void to_json(json& j, unsigned char * cipher, string sender, unsigned int len, string h){
    //unsigned int _h[8];
    unsigned char _cipher[16];
    //memcpy(_h, h, 8);
    j["hash"] = h;
    memcpy(_cipher, cipher, 16);
    j["message"] = _cipher;
    j["size"] = len;
    j["user"] = sender;
}

void from_json(const json& j, unsigned char* &cipher, unsigned int &len, string &recHash, string& sender){
    //recHash = new unsigned int[8];
    cipher = new unsigned char[16];

    /*for (int i=0; i<8; i++){
        recHash[i] = j["hash"][i];
    }*/
    recHash = j["hash"];

    for (int i=0; i<16; i++){
        cipher[i] = j["message"][i];
    }

    sender = j["user"];
    len = j["size"];
}
