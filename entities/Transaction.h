#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

enum class TransactionType {
    Deposit,   // Nạp điểm
    Transfer   // Chuyển điểm
};

class Transaction {
private:
    TransactionType type;
    std::string fromUsername;   // Nếu là nạp thì có thể là "SYSTEM"
    std::string toUsername;     // Nếu là nạp thì là chính người nhận
    int amount;
    std::time_t timestamp;      // Thời gian thực hiện

public:
    // Constructor
    Transaction(TransactionType type, const std::string& from, const std::string& to, int amount)
        : type(type), fromUsername(from), toUsername(to), amount(amount), timestamp(std::time(nullptr)) {}

    // Getter
    TransactionType getType() const { return type; }
    std::string getFromUsername() const { return fromUsername; }
    std::string getToUsername() const { return toUsername; }
    int getAmount() const { return amount; }
    std::time_t getTimestamp() const { return timestamp; }

    // Trả về chuỗi mô tả giao dịch
    std::string toString() const {
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));

        std::string typeStr = (type == TransactionType::Deposit) ? "Nap diem" : "chuyen diem";
        return "[" + std::string(buffer) + "] " + typeStr +
               " | tu: " + fromUsername +
               " → den: " + toUsername +
               " | so diem: " + std::to_string(amount);
    }
};

#endif // TRANSACTION_H
