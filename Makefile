build: components/Block.cpp components/Blockchain.cpp components/Transaction.cpp components/sha256.cpp app/main.cpp components/Block.hpp components/Blockchain.hpp components/Transaction.hpp components/sha256.hpp Makefile
  g++ components/Block.cpp components/Blockchain.cpp components/Transaction.cpp components/sha256.cpp app/main.cpp -std=c++20
