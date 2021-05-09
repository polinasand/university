#include "blockchain.h"
#include <iostream>
void to_json(json& j, const Transaction& transaction){
	j = json{{"id", transaction.id},
			 {"from", transaction.from},
			 {"to", transaction.to},
			 {"amount", transaction.amount}};
}

void from_json(const json& j, Transaction& transaction){
	j.at("id").get_to(transaction.id);
	j.at("from").get_to(transaction.from);
	j.at("to").get_to(transaction.to);
	j.at("amount").get_to(transaction.amount);
}

void to_json(json& j, const SignedTransaction& signed_transaction){
	j = json{{"transaction", signed_transaction.getTransaction()},
			 {"signature", signed_transaction.getSignature()}};
}

void from_json(const json& j, SignedTransaction& signed_transaction){
	Transaction transaction;
	j.at("transaction").get_to(transaction);
	signed_transaction.setTransaction(transaction);

	RSA::Signature signature;
	j.at("signature").get_to(signature);
	signed_transaction.setSignature(signature);
}

void to_json(json& j, const MiningTransaction& mining_transaction){
	j = json{{"transaction", mining_transaction.getTransaction()}};
}

void from_json(const json& j, MiningTransaction& mining_transaction){
	Transaction transaction;
	j.at("transaction").get_to(transaction);
	mining_transaction.setTransaction(transaction);
}

void to_json(json& j, const Block::Header& header){
	j = json{{"id", header.id},
			 {"previous_hash", header.previous_hash},
			 {"merkle_root", header.merkle_root},
		     {"nonce", header.nonce}};
}

void from_json(const json& j, Block::Header& header){
	j.at("id").get_to(header.id);
	j.at("previous_hash").get_to(header.previous_hash);
	j.at("merkle_root").get_to(header.merkle_root);
	j.at("nonce").get_to(header.nonce);
}

void to_json(json& j, const Block& block){
	j = json{{"header", block.getHeader()},
			 {"signed_transactions", block.getSignedTransactions()},
			 {"mining_transaction", block.getMiningTransaction()}};
}

void from_json(const json& j, Block& block){
	Block::Header header;
	j.at("header").get_to(header);
	block.setHeader(header);

	std::vector<SignedTransaction> signed_transactions;
	j.at("signed_transactions").get_to(signed_transactions);

	MiningTransaction mining_transaction;
	j.at("mining_transaction").get_to(mining_transaction);

	block.setTransactions(signed_transactions, mining_transaction);
}

void to_json(json& j, const Blockchain& blockchain){
	j = json{{"blocks", blockchain.getBlocks()},
			 {"pool", blockchain.getPool()}};
}

void from_json(const json& j, Blockchain& blockchain){
	std::vector<Block> blocks;
	j.at("blocks").get_to(blocks);
	blockchain.setBlocks(blocks);

	std::vector<SignedTransaction> pool;
	j.at("pool").get_to(pool);
	blockchain.setPool(pool);
}


// blockchain
const int Blockchain::kTargetZerosPrefix = 1;
const string Blockchain::kZeroBlockHash = "0";
const double Blockchain::kBlockReward = 10;
const BigInt Blockchain::kCoinMintingAddress = BigInt(0);
const std::string Blockchain::kDumpFile = "blockchain.txt";

bool Blockchain::verify() {
    string previous_block_hash = kZeroBlockHash;
    for (Block block : blocks) {
        if (block.getHeader().previous_hash != previous_block_hash)
            return false;
        if (!block.verify(previous_block_hash))
            return false;
        previous_block_hash = block.getHeaderHash();
    }
    return true;
}

Blockchain Blockchain::load() {
    std::ifstream file;
    file.open(kDumpFile);

    if (!file.is_open()){
        cout << "not opened ";
        return Blockchain();
    }

    json j;
    file >> j;
    file.close();

    auto blockchain = j.get<Blockchain>();
    return blockchain;
}

void Blockchain::dump() {
    json j = *this;
    std::ofstream file;
    file.open(kDumpFile);

    file << j.dump();
    file.close();
}


vector<SignedTransaction> Blockchain::getPool() const {
    return this->pool;
}

vector<Block> Blockchain::getBlocks() const {
    return blocks;
}

void Blockchain::setPool(vector<SignedTransaction> pool) {
    this->pool = pool;
}
void Blockchain::setBlocks(vector<Block> blocks) {
    this->blocks = blocks;
}

int Blockchain::getPoolSize() {
    return pool.size();
}

bool Blockchain::addBlock(Block block) {
    if (!block.verify(this->getLastBlockHeaderHash()))
        return false;
    this->blocks.push_back(block);
    this->pool.clear();
    return true;
}

bool Blockchain::addSignedTransaction(SignedTransaction signed_transaction) {
    if (!signed_transaction.verify())
        return false;
    pool.push_back(signed_transaction);
    return true;
}

string Blockchain::getLastBlockHeaderHash() {
    int n = blocks.size();
    if (n==0)
        return kZeroBlockHash;
    return this->blocks[n-1].getHeaderHash();
}

int Blockchain::getNumberOfBlocks() {
    return this->blocks.size();
}

map<BigInt, double> Blockchain::getBalances(int block) {
    map<BigInt, double> balance;
    if (block == -1)
        block = getNumberOfBlocks();

    if (block > getNumberOfBlocks()) return balance;

    for (int i=0; i<block; i++)
        this->blocks[i].updateBalances(balance);

    return balance;
}

double Blockchain::getBalance(BigInt address, int block) {
    return getBalances(block)[address];
}

//block
string Block::getHeaderHash() {
    SHA256 sha;
    json j = getHeader();
    string ans;
    unsigned int* h = sha.hash(j.dump());
    strcpy((char*)h, ans.c_str());
    return ans;
}

Block::Header Block::getHeader() const {
    return header;
}

void Block::setHeader(Block::Header header) {
    this->header = header;
}

void Block::setTransactions(std::vector<SignedTransaction> signed_transactions, MiningTransaction mining_transaction) {
    this->transactions = signed_transactions;
    this->mining_transaction = mining_transaction;
}

MiningTransaction Block::getMiningTransaction() const {
    return this->mining_transaction;
}

bool Block::verify(string hash) {
    if (this->getHeader().previous_hash != hash)
        return false;

    for (SignedTransaction transaction : transactions){
        if (!transaction.verify())
            return false;
    }
    return this->verifyMerkleRoot() && this->verifyMiningTransaction();
}

bool Block::verifyMerkleRoot() {
    return this->getHeader().merkle_root == Block::getMerkleRoot(this->transactions, this->mining_transaction);
}

bool Block::verifyMiningTransaction() {
    string hash = this->getHeaderHash();
    cout << hash << '\n';
    for (int i=0; i < Blockchain::kTargetZerosPrefix; i++) {
        if (hash[i] != '0')
            return false;
    }
    return true;
}


string Block::getMerkleRoot(std::vector<SignedTransaction>& signed_transactions, MiningTransaction mining_transaction) {
    vector<string> serialized_transactions;
	for (SignedTransaction signed_transaction: signed_transactions){
		json serialized_transaction = signed_transaction;
		serialized_transactions.push_back(serialized_transaction.dump());
	}
	json serialized_transaction = mining_transaction;
	serialized_transactions.push_back(serialized_transaction.dump());
	return MerkleTree::calculateRoot(serialized_transactions);
}

void Block::updateBalances(std::map<BigInt, double>& balances) {
    balances[mining_transaction.getTransaction().to] += mining_transaction.getTransaction().amount;

    for (SignedTransaction transaction : transactions){
        Transaction t = transaction.getTransaction();
        balances[t.from] -= t.amount;
        balances[t.to] += t.amount;
    }
}


std::vector<SignedTransaction> Block::getSignedTransactions() const {
    return this->transactions;
}

// signed transaction
void SignedTransaction::setSignature(RSA::Signature signature) {
    this->signature = signature;
}

RSA::Signature SignedTransaction::getSignature() const{
    return signature;
}

Transaction SignedTransaction::getTransaction() const{
    return transaction;
}

void SignedTransaction::setTransaction(Transaction transaction){
    this->transaction = transaction;
}

string SignedTransaction::hashTransaction() {
    SHA256 sha;
    string hash;
    json j = transaction;
    strcpy((char*)sha.hash(j.dump()), hash.c_str());
    return hash;
}

bool SignedTransaction::verify() {
    RSA rsa;
	if (this->getTransaction().from == Blockchain::kCoinMintingAddress) return false;
	string transaction_hash = this->hashTransaction();
	return rsa.verify(transaction_hash, this->signature) && this->signature.public_key == this->getTransaction().from;
}

// mining transaction

Transaction MiningTransaction::getTransaction() const {
    return transaction;
}

void MiningTransaction::setTransaction(Transaction transaction){
    this->transaction = transaction;
}

MiningTransaction::MiningTransaction() {}

MiningTransaction::MiningTransaction(BigInt address) {
    Transaction t;
    t.amount = Blockchain::kBlockReward;
    t.from = Blockchain::kCoinMintingAddress;
    t.to = address;
    this->setTransaction(t);
}


bool MiningTransaction::verify() {
    Transaction t = this->getTransaction();
	return t.amount == Blockchain::kBlockReward && t.from == Blockchain::kCoinMintingAddress;
}
