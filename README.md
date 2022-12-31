# Basic-Blockchain

## Interface for a simple blockchain-based cryptocurrency

This project provides the infrastructure and interface for a basic blockchain-based cryptocurrency that implements the core features/concepts of a real blockchain that can be added to, mined, checked for validity, and more.  

It uses SHA-256 for hashing and nonce values for mining, along with a variety of data structures that are useful in the application of a blockchain.

### How to run
- Download or clone this repository and navigate to the folder in the terminal
- Compile: in lieu of a makefile, you can run the following from the home directory    

g++ -std=c++20 components/Block.cpp components/Blockchain.cpp components/Transaction.cpp components/sha256.cpp app/main.cpp
- Run: ./a.out

**Note** you may get a warning stating that a function in sha256.cpp is deprecated. This warning did not exist at the time this project was developed. This project is not for intended for official release or production so this does not pose any risk. The project still functions as written and as expected.
