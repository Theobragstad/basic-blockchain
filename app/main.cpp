#include <iostream>
#include <fstream>
#include "../components/Blockchain.hpp"

using namespace std;

void handleFailedInput();


int main(int argc, char* argv[])
{
    // menu for interacting with the blockchain

    Blockchain bc;

    int choice;
    string input1;
    string input2;
    string input3;
    bool quit = false;
    bool invalid = false;

    cout << "Welcome to the blockchain!" << endl;


    do {
        cout << endl << "---main menu---" << endl;
        cout << "1. add transaction" << endl;
        cout << "2. verify blockchain" << endl;
        cout << "3. mine pending transactions" << endl;
        cout << "4. display blockchain" << endl;
        cout << "5. get balance of an address" << endl;
        cout << "6. get size of blockchain" << endl;
        cout << "7. quit" << endl;

        cin >> choice;
        handleFailedInput();

        switch(choice) {
            case 1: 
                cout << "enter source address (must be string): " << endl;
                cin >> input1;
                cout << "enter destination address (must be string): " << endl;
                cin >> input2;
                cout << "enter amount (must be integer): " << endl;
                cin >> input3;

                invalid = false;
                for(int i = 0; i < input3.length(); i++) {
                    if(!isdigit(input3[i])) {
                        invalid = true;
                        break;
                    }
                }
                if(invalid) {
                    cout << "invalid transaction amount!" << endl;
                    break;
                }
                
                cout << "adding transaction... ";
                bc.addTransaction(input1, input2, stoi(input3));
                break;
            case 2:
                cout << "verifying validity of blockchain... ";
                if(bc.isChainValid()) {
                    cout << "chain is valid." << endl;
                }
                else {
                    cout << "chain is invalid." << endl;
                }
                break;
            case 3:
                cout << "enter miner address (must be string): " << endl;
                cin >> input1;
                cout << "mining... ";

                if(bc.minePendingTransactions(input1)) {
                    cout << "new block mined sucessfully." << endl;
                }
                else {
                    cout << "nothing to mine." << endl;
                }
                break;
            case 4:
                cout << "printing contents of current blockchain... " << endl << endl;;
                bc.prettyPrint();
                break;
            case 5: 
                cout << "enter address (must be a string): ";
                cin >> input1;
                cout << "The balance of address '" << input1 << "' is " << bc.getBalanceOfAddress(input1) << "." << endl;
                break;
            case 6:
                cout << "There are currently " << bc.getChainSize() << " blocks in the blockchain." << endl;
                break;
            case 7: 
                cout << "quitting... ";
                quit = true;
                break;
            default: cout << "invalid choice!" << endl;
        }
    } while(!quit);

    cout << "thank you for using the blockchain!" << endl;

    return 0;
}


void handleFailedInput() {
    if (cin.fail())
    {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}