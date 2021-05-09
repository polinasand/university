#pragma once
#include "merkle_tree.h"
#include "json.hpp"
#include "rsa.h"
#include <fstream>

using json = nlohmann::json;
using namespace std;

struct Transaction{
    int id;
    BigInt from;
    BigInt to;
    double amount;
};

class SignedTransaction {
    RSA::Signature signature;
    Transaction transaction;
    string signTransaction();
public:
    void setTransaction(Transaction);
    Transaction getTransaction() const;
    void setSignature(RSA::Signature signature);
    RSA::Signature getSignature() const;
    bool verify();
    string hashTransaction();
};

class MiningTransaction {
    Transaction transaction;
public:
    MiningTransaction();
	MiningTransaction(BigInt address);
    void setTransaction(Transaction);
    Transaction getTransaction() const;
    bool verify();
};

class Block {
public:

    struct Header {
        int id;
        string merkle_root;
        string previous_hash;
        int nonce;
    };
    static string getMerkleRoot(std::vector<SignedTransaction>& signed_transactions, MiningTransaction mining_transaction);
	bool verify(string previous_block_header_hash);
	string getHeaderHash();
	Block::Header getHeader() const;
	void setHeader(Block::Header header);
	void setTransactions(std::vector<SignedTransaction> signed_transactions, MiningTransaction mining_transaction);
	MiningTransaction getMiningTransaction() const;
	std::vector<SignedTransaction> getSignedTransactions() const;
	bool verifyMiningTransaction();
	void updateBalances(std::map<BigInt, double>& balances);

private:
	Header header;
	std::vector<SignedTransaction> transactions;
	MiningTransaction mining_transaction;
	bool verifyMerkleRoot();
};

class Blockchain{
    vector<Block> blocks;
    vector<SignedTransaction> pool;
    map<BigInt, double> balances;
public:
	const static int kTargetZerosPrefix;
	const static string kZeroBlockHash;
	const static double kBlockReward;
	const static BigInt kCoinMintingAddress;
	const static string kDumpFile;

	static Blockchain load();
	void dump();

	std::vector<SignedTransaction> getPool() const;
	std::vector<Block> getBlocks() const;

	void setPool(vector<SignedTransaction> pool);
	void setBlocks(vector<Block> blocks);

	int getPoolSize();
	bool verify();
	bool addBlock(Block block);
	bool addSignedTransaction(SignedTransaction signed_transaction);
	string getLastBlockHeaderHash();
	int getNumberOfBlocks();

	map<BigInt, double> getBalances(int block = -1);
	double getBalance(BigInt address, int block = -1);
};
