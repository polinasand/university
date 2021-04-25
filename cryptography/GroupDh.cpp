#include "GroupDh.h"
#include "prime_gen.h"
#include "SHA256.h"
#include "AES.h"

AES aes;
SHA256 sha;
User::User(){

}
User::User(string username){
    this->username = username;
    this->private_key = prime_gen::nextPrime(6);
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
        secret[i] = data.bytes[0];
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
        for (int j=i+1; j % n != i; j++){
            j %= n;
            data = users[j].send(data, modulo);
        }
        users[i].setSecret(data);
        cout << "user got secret "<<data<<endl;

    }
}

void GroupDH::sendMessage(json j) {
    for (auto user : users){
        user.getMessage(j);
    }

}

json User::createMessage(Message message){
    unsigned int * h = sha.hash(message.data);
    unsigned int l = message.data.size(), outLen;
    unsigned char *data = new unsigned char[l+1];
    strcpy((char*)data, message.data.c_str());
    cout << data << endl;
    unsigned char * cipher = aes.Encrypt(data, l+1, secret, outLen);
    aes.printHexArray(cipher, outLen);
    json j;
    to_json(j, cipher, message.sender, outLen, h);
    cout << "Message created\n";
    cout << j << endl;
    delete [] h;
    delete [] data;
    delete [] cipher;
    return j;
}

void User::getMessage(json j) {
    Message message = decrypt(j);
    cout << "User " << username << " received message " <<
        message.data << " from " << message.sender << endl;
}

Message User::decrypt(json j) {
    unsigned char * cipher;
    Message message("none", "");
    unsigned int * h;
    unsigned int len;
    from_json(j, cipher, len, h, message.sender);

    for (int i=0; i<len; i++){
        // message.data += res[i];
    }

    if (!GroupDH::verify(message.data, h)){
        cout << "wrong hash\n";
    }
    unsigned char * res = aes.Decrypt(cipher, len, this->secret);
    cout << res;
    return message;
}

bool GroupDH::verify(string data, unsigned int* recHash){
    unsigned int* actHash = sha.hash(data);
    for (int i=0; i<8; i++){
        if (actHash[i] != recHash[i])
            return false;
    }
    return true;
}
void to_json(json& j, unsigned char * cipher, string sender, unsigned int len, unsigned int* h){
    unsigned int ha[8];
    unsigned char ci[16];
    memcpy(ha, h, 8);
    j["hash"] = ha;
    memcpy(ci, cipher, 16);
    j["message"] = ci;
    j["size"] = len;
    j["user"] = sender;
    delete [] ha;
    delete [] ci;
}

void from_json(const json& j, unsigned char* &cipher, unsigned int &len, unsigned int* &recHash, string& sender){
    recHash = new unsigned int[8];
    cipher = new unsigned char[16];
    int i=0;
    for (; i<8;){
        recHash[i] = j["hash"][i];
        i++;
    }
    i=0;
    for (;i<16;){
        cipher[i] = j["message"][i];
        i++;
    }
    sender = j["user"];
    len = j["size"];
}
