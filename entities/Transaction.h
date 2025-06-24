#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

// Loại giao dịch: chuyển điểm, nạp điểm...
enum class TransactionType {
    Transfer = 1,
    Deposit = 2
};

class Transaction {
private:
    TransactionType type;
    std::string fromWalletId;
    std::string toWalletId;
    int amount;
    std::time_t timestamp;

public:
    // Constructor
    Transaction(TransactionType type, const std::string& from, const std::string& to, int amount);

    // Getter
    std::string getFromWalletId() const;
    std::string getToWalletId() const;
    int getAmount() const;
    std::time_t getTimestamp() const;
    TransactionType getType() const;

    // Setter bổ sung cho việc load từ file
    void setTimestamp(std::time_t t);

    // In ra định dạng chuỗi
    std::string toString() const;
};

// Ghi giao dịch vào bộ nhớ và file log
void recordTransaction(const Transaction& tx);

#endif // TRANSACTION_H
