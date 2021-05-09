#include "blockchain.h"

class BlockchainClient {
    Blockchain blockchain;
public:
    BlockchainClient();
	bool mineBlock(BigInt address);
	void addSignedTransaction(RSA from, BigInt to, double amount);
	bool verifyBlockchain();
	double getBalance(BigInt address, int block);
	void dump();
	map<BigInt, double> getBalances(int block);
};
