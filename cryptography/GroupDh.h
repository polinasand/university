/* Created by sandatsian */

#pragma once
#include<string>
#include<map>
#include "prime_gen.h"
#include "SHA256.h"
#include "AES.h"
#include "json.hpp"
#include <windows.h>
using namespace std;

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
public:
    User(string);
    void setSecret(BigInt);
    string getUsername();
    BigInt getPrivateKey();
    BigInt send(const BigInt&, const BigInt&);
};

class GroupDH {
private:
    vector<User> users;
    BigInt modulo;
    BigInt g;
    unsigned char key[32];
public:
    GroupDH(int len);
    BigInt getModulo();
    BigInt getGenerator();
    void addUser(User);
    void createKey();
    void sendMessage(Message);
};

void to_json(json& j, unsigned char * cipher, string sender, unsigned int len, unsigned int* h);
void from_json(const json& j, unsigned char* &cipher, unsigned int &len, unsigned int* &recHash, string& sender);

