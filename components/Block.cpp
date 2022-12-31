#include<iostream>
#include <sstream>


#include "Transaction.hpp"
#include "Block.hpp"
#include "sha256.hpp"

using namespace std;

Block::Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash) {
    nonce = -1; // initial value of nonce is -1
    transactions = _transactions;
    previousHash = _previousHash;
    timestamp = _timestamp;
    hash = calculateHash();
}

// setter function for previous hash
void Block::setPreviousHash(string _previousHash) {
    // TODO
    previousHash = _previousHash;
}

string Block::calculateHash() {
    // TODO
    // call sha256 function on the string that represents the contents of the block
    return sha256(toString());   
}

// mine the block so it can be added to the chain
void Block::mineBlock(unsigned int difficulty) {
    // TODO
    string currentHash; // holds the current hash we are checking

    // create a string with the correct number of zeroes to check the current hash against
    string zeroes;
    for(int i = 0; i < difficulty; i++) {
        zeroes += "0";
    }

    // increase nonce and calculate the hash until the first n (difficulty) characters of the hash are 0's
    do {
        nonce++;
        currentHash = calculateHash();
    } while(currentHash.substr(0, difficulty) != zeroes);

    hash = currentHash; // set the resultant hash
}

// create a string to hold the block's information
string Block::toString() {
    // TODO
    // create stringstream object and append necessary information about the block
    stringstream ss;

    ss << nonce << ", " << previousHash << ", " << timestamp;
    // go through every transaction stored in the block
    for(Transaction t: transactions) {
        ss << ", (" << t.getSender() << ", " << t.getReceiver() << ", " << t.getAmount() << ")";
    }

    return ss.str();
    // format: nonce, previousHash, timestamp, (S, R, 1), (S, R, 1)  ...
}

// returns the block's previous hash
string Block::getPreviousHash() {
    return previousHash;
}

// returns the block's hash
string Block::getHash() {
    return hash;
}

// returns the vector of transactions stored in the block
vector<Transaction> Block::getTransactions() {
    return transactions;
}