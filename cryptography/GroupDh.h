using namespace std;
#include<string>
#include<map>
#include "BigInt/BigInt.h"
#include "AES.h"
#include "SHA256.h"

class User {
private:
    BigInt secret;
    BigInt private_key;
    string username;
public:
    User();
    User(string);
    BigInt send(const BigInt&, const BigInt&);
    void setSecret(BigInt&);
    string getUsername();
    BigInt getPrivateKey();
};

struct Message {
    User sender;
    string data;
    Message(User sender, string data){
        this->sender = sender;
        this->data = data;
    }
};

class GroupDH {
private:
    AES aes;
    SHA256 sha;
    vector<User> users;
    BigInt modulo;
    BigInt g;
    vector<BigInt> keys;
public:
    GroupDH(int len);
    BigInt getModulo();
    BigInt getGenerator();
    void addUser(User);
    void createKey();
    void sendMessage(Message);
};



