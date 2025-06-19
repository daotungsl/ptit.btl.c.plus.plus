#include "../entities/Transaction.h"
#include <iostream>
#include <iomanip>
#include <fstream>

Transaction::Transaction(TransactionType type, const std::string& from, const std::string& to, int amount)
    : type(type), fromWalletId(from), toWalletId(to), amount(amount), timestamp(std::time(nullptr)) {}

std::string Transaction::getFromWalletId() const { return fromWalletId; }
std::string Transaction::getToWalletId() const { return toWalletId; }
int Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
TransactionType Transaction::getType() const { return type; }

std::string Transaction::toString() const {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));

    std::string typeStr = (type == TransactionType::Deposit) ? "DEPOSIT" : "TRANSFER";

    return "[" + std::string(buffer) + "] " + typeStr +
           " | From: " + fromWalletId +
           " → To: " + toWalletId +
           " | Amount: " + std::to_string(amount);
}

// Ghi giao dịch vào file (append)
void recordTransaction(const Transaction& tx) {
    std::ofstream out("transactions.log", std::ios::app);
    if (out.is_open()) {
        out << tx.toString() << "\n";
        out.close();
    } else {
        std::cerr << "Khong mo duoc file log giao dich.\n";
    }
}
