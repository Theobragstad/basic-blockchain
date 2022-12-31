#include<iostream>
#include <sstream>

#include "Transaction.hpp"
#include "Block.hpp"
#include "Blockchain.hpp"
#include<vector>

using namespace std;

Blockchain::Blockchain() {
    Transaction genesis("BFC","BFC",0);
    pending.push_back(genesis);

    Block gBlock(pending, time(nullptr), "In the beginning..");
    chain.push_back(gBlock);

    Transaction freeMoney("BFC","make money by mining",0);
    pending.push_back(freeMoney);

    difficulty = 4;
    miningReward = 10;
}

Block Blockchain::getLatestBlock() { 
    return chain.back();
}

void Blockchain::addTransaction(string src, string dst, int coins) {
    if(src == dst) {
        cout << "error. source and destination cannot be the same." << endl;
        return;
    }
    if(coins <= 0) {
        cout << "error. you must enter a value greater than zero." << endl;
        return;
    }

    int nonPendingBalace = getBalanceOfAddress(src); // calculate the non-pending/official blockchain balance
    int pendingBalance = getBalanceOfAddressIncludingPending(src); // calculate the balance including the pending transactions

    // only add the transaction if the chain is valid
    // also make sure both the non-pending and pending balances are greater than or equal to the transaction amount
    if(isChainValid() && nonPendingBalace >= coins && pendingBalance >= coins) { 
        Transaction t(src, dst, coins); // make a new transaction
        pending.push_back(t); // add the transaction to the list of pending transactions
        cout << "transaction added successfully." << endl;
    }
    else { // otherwise, output an error message and don't add a new transaction
        cout << "error. transaction amount exceeds current balance of the source address." << endl;
    }
}

// check if the current chain is structured correctly
bool Blockchain::isChainValid() { 
    // create a string with the correct number of zeroes to check the current hash against
    string zeroes;
    for(int i = 0; i < difficulty; i++) {
        zeroes += "0";
    }

    // loop through the chain (excluding the first block)
    for(int i = 1; i < chain.size(); i++) {
        // make sure that the previous block's hash matches the current block's previous hash
        // also make sure that the current block's hash has the correct number of leading zeroes
        if(chain[i-1].getHash() != chain[i].getPreviousHash() || chain[i].getHash().substr(0, difficulty) != zeroes) {
            return false;
        }
    }
    return true;
}

// mine the currently pending transactions into a new block on the chain
bool Blockchain::minePendingTransactions(string minerAddress) {
    // nothing to mine if there is nothing pending (in practice this will never happen, but is here just in case)
    if(pending.size() == 0) {
        return false;
    }

    // just like Bitcoin, increase difficulty for every 2016 blocks in the chain
    if(chain.size() % 2016 == 0) {
        difficulty++;
    }

    // make a new block. Pass in the pending transactions, current time, and the hash of the latest block as the new block's previous hash
    Block b(pending, time(nullptr), getLatestBlock().getHash());

    // mine the block by calling mineBlock
    b.mineBlock(difficulty);

    // clear pending transactions
    pending.clear();
    // add the new block to the chain
    chain.push_back(b);

    // make a new transaction to reward the miner of the new block
    Transaction reward("BFC", minerAddress, miningReward);
    // add the transaction to the list of pending transactions
    pending.push_back(reward);

    return true;
}

// returns balance of the input address as represented by the blockchain (this is the official balance)
int Blockchain::getBalanceOfAddress(string address) {
    int balance = 0; // balance is initially 0
    vector<Transaction> transactions; // vector to hold the transactions for each block
    
    for(Block b: chain) { // loop through every block in the chain
        transactions = b.getTransactions(); // set transactions to the current block's transaction list
        for(Transaction t: transactions) { // go through every transaction in the list of transactions
            if(address == t.getSender()) { // if the address is the sender, subtract the amount
                balance -= t.getAmount();
                // check if balance is negative (this should never happen but is here just in case)
                if(balance < 0) {
                    cout << "error. this address is associated with a negative balance history." << endl;
                    return -1;
                }
            }
            else if(address == t.getReceiver()) { // if the address is the receiver, add the amount
                balance += t.getAmount();
            }
        }  
    }

    return balance; // return the balance
}

// returns balance of the input address as represented by both the blockchain and the list of currently pending transactions.
// this function is used to ensure that an address cannot send more than their non-pending/official/blockchain balance. 

/* For example, address 'A' with non-pending balance 10 could not send 10 coins to address 'B' and 10 coins to address 'C', 
because their pending balance after sending 10 coins to 'B' is 0, although their non-pending balance is 
still 10 because nothing has been mined/updated yet. */

int Blockchain::getBalanceOfAddressIncludingPending(string address) {
    // first get the balance as represented in the chain only
    int balance = getBalanceOfAddress(address);

    // go through every pending transaction
    for(Transaction t: pending) {
        if(address == t.getSender()) { // if the address is the sender, subtract the amount
            balance -= t.getAmount();
            if(balance < 0) {
                cout << "error. this address is associated with a negative balance history." << endl;
                return -1;
            }
        }
        else if(address == t.getReceiver()) { // if the address is the receiver, add the amount
            balance += t.getAmount();
        }
    }

    // return the balance which now includes pending transactions
    return balance;
}

// display the contents of the chain
void Blockchain::prettyPrint() {
    // loop through every block in the chain
    for(int i = 0; i < chain.size(); i++) {
        // output the block's number and its information
        // format is the same as the format of toString in the block class
        cout << i+1 << ": " << chain[i].toString() << endl;
    }
}

// returns the size of the current blockchain
int Blockchain::getChainSize() {
    return chain.size();
}