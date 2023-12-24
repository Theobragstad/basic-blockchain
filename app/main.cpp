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

    cout << "Welcome to basic blockchain!" << endl;


    do {
        cout << endl << "---Main Menu---" << endl;
        cout << "1. Add transaction" << endl;
        cout << "2. Verify blockchain" << endl;
        cout << "3. Mine pending transactions" << endl;
        cout << "4. Display blockchain" << endl;
        cout << "5. Get balance of an address" << endl;
        cout << "6. Get size of blockchain" << endl;
        cout << "7. Quit" << endl;

        cin >> choice;
        handleFailedInput();

        switch(choice) {
            case 1: 
                cout << "Enter source address (must be string): " << endl;
                cin >> input1;
                cout << "Enter destination address (must be string): " << endl;
                cin >> input2;
                cout << "Enter amount (must be integer): " << endl;
                cin >> input3;

                invalid = false;
                for(int i = 0; i < input3.length(); i++) {
                    if(!isdigit(input3[i])) {
                        invalid = true;
                        break;
                    }
                }
                if(invalid) {
                    cout << "Invalid transaction amount!" << endl;
                    break;
                }
                
                cout << "Adding transaction... ";
                bc.addTransaction(input1, input2, stoi(input3));
                break;
            case 2:
                cout << "Verifying validity of blockchain... ";
                if(bc.isChainValid()) {
                    cout << "Chain is valid." << endl;
                }
                else {
                    cout << "Chain is invalid." << endl;
                }
                break;
            case 3:
                cout << "Enter miner address (must be string): " << endl;
                cin >> input1;
                cout << "Mining... ";

                if(bc.minePendingTransactions(input1)) {
                    cout << "New block mined sucessfully." << endl;
                }
                else {
                    cout << "Nothing to mine." << endl;
                }
                break;
            case 4:
                cout << "Printing contents of current blockchain... " << endl << endl;;
                bc.prettyPrint();
                break;
            case 5: 
                cout << "Enter address (must be a string): ";
                cin >> input1;
                cout << "The balance of address '" << input1 << "' is " << bc.getBalanceOfAddress(input1) << "." << endl;
                break;
            case 6:
                cout << "There are currently " << bc.getChainSize() << " blocks in the blockchain." << endl;
                break;
            case 7: 
                cout << "Quitting... ";
                quit = true;
                break;
            default: cout << "Invalid choice!" << endl;
        }
    } while(!quit);

    cout << "Thank you for using the blockchain!" << endl;

    return 0;
}


void handleFailedInput() {
    if (cin.fail())
    {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}