#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

enum class TransactionType {
    Deposit,
    Transfer
};

class Transaction {
private:
    TransactionType type;
    std::string fromWalletId;
    std::string toWalletId;
    int amount;
    std::time_t timestamp;

public:
    Transaction(TransactionType type, const std::string& from, const std::string& to, int amount);

    std::string getFromWalletId() const;
    std::string getToWalletId() const;
    int getAmount() const;
    std::time_t getTimestamp() const;
    TransactionType getType() const;

    std::string toString() const;
};

void recordTransaction(const Transaction& tx);  // <- Hàm ghi log, sẽ viết ở transaction.cpp

#endif // TRANSACTION_H
