using namespace std;
#include<string>
#include<map>
#include "BigInt/BigInt.h"
#include "AES.h"
#include "SHA256.h"
#include "json.hpp"
#include "windows.h";

using json=nlohmann::json;

struct Message {
    string sender;
    string data;
    Message(string sender, string data){
        this->sender = sender;
        this->data = data;
    }
};


class User {
private:
    unsigned char secret[32];
    BigInt private_key;
    string username;
    json encrypt(Message);
    Message decrypt(json);
public:
    User();
    User(string);
    void setSecret(BigInt);
    string getUsername();
    BigInt getPrivateKey();
    BigInt send(const BigInt&, const BigInt&);
    void getMessage(json);
    json createMessage(Message);
};

class GroupDH {
private:
    vector<User> users;
    BigInt modulo;
    BigInt g;
    vector<BigInt> keys;
    unsigned char key[32];
public:
    GroupDH(int len);
    static bool verify(string data, unsigned int* recHash);
    BigInt getModulo();
    BigInt getGenerator();
    void addUser(User);
    void createKey();
    void sendMessage(json);
};

void to_json(json& j, unsigned char * cipher, string sender, unsigned int len, unsigned int* h);
    void from_json(const json& j, unsigned char* &cipher, unsigned int &len, unsigned int* &recHash, string& sender);

