#include "blockchain_client.h"
#include <iostream>
BlockchainClient::BlockchainClient() {
    blockchain = Blockchain::load();
}

bool BlockchainClient::mineBlock(BigInt address) {
    MiningTransaction mining_transaction(address);
    vector<SignedTransaction> pool = this->blockchain.getPool();
    string root = Block::getMerkleRoot(pool, mining_transaction);
    cout << "mining tr created\n";

    Block::Header header;
    header.id = blockchain.getNumberOfBlocks();
    header.merkle_root = root;
    header.previous_hash = blockchain.getLastBlockHeaderHash();
    cout << header.id << " header\n";
    Block block;
    block.setTransactions(pool, mining_transaction);

    for (unsigned int i=0; i<UINT_MAX; i++){
        if (i % 100000 == 0) cout << i << ' ';
        header.nonce = i;
        block.setHeader(header);
        if (block.verifyMiningTransaction())
            return blockchain.addBlock(block);
    }
    return false;
}


void BlockchainClient::addSignedTransaction(RSA from, BigInt to, double amount) {
    Transaction transaction;
    transaction.id = this->blockchain.getPoolSize();
    transaction.from = from.public_key;
    transaction.to = to;
    transaction.amount = amount;

    SignedTransaction signed_transaction;
    signed_transaction.setTransaction(transaction);
    string transaction_hash = signed_transaction.hashTransaction();
    cout << from.public_key << ' ' << to << ' ' << transaction_hash << endl;

    signed_transaction.setSignature(from.sign(transaction_hash));
    cout << "signed ";
    blockchain.addSignedTransaction(signed_transaction);
    cout <<"Succes\n";
}

bool BlockchainClient::verifyBlockchain() {
    return this->blockchain.verify();
}

double BlockchainClient::getBalance(BigInt address, int block)
{
    return this->blockchain.getBalance(address, block);
}

void BlockchainClient::dump() {
    blockchain.dump();
}

map<BigInt, double> BlockchainClient::getBalances(int block) {
    return this->blockchain.getBalances(block);
}

