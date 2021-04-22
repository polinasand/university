using namespace std;

struct Message {
private:
    string sender;
    string data;
public:
    Message(string sender, string data){
        this->sender = sender;
        this->data = data;
    }
};

class GroupDH {
private:
    map<string, User> users;
    static BigInt modulo;
    static BigInt g;
public:
    GroupDH(int len);
    BigInt getModulo();
    BigInt getGenerator();
    void addUser(User);
    void createKey();
};

class User {
private:
    BigInt secret;
    BigInt private_key;
    string username;
public:
    User(string);
    BigInt send(const BigInt&);
    void setSecret(BigInt&);
    string getUsername();
    BigInt decryptMessage();
    BigInt encryptMessage();
};
