#include "../entities/Transaction.h"
#include "../include/UserFileHelper.h"
#include "../include/DataStore.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

Transaction::Transaction(TransactionType type, const std::string& from, const std::string& to, int amount)
    : type(type), fromWalletId(from), toWalletId(to), amount(amount), timestamp(std::time(nullptr)) {}

std::string Transaction::getFromWalletId() const {
    return fromWalletId;
}

std::string Transaction::getToWalletId() const {
    return toWalletId;
}

int Transaction::getAmount() const {
    return amount;
}

std::time_t Transaction::getTimestamp() const {
    return timestamp;
}

TransactionType Transaction::getType() const {
    return type;
}

void Transaction::setTimestamp(std::time_t t) {
    timestamp = t;
}

std::string Transaction::toString() const {
    char buffer[100];
    std::tm timeInfo = {};
    localtime_s(&timeInfo, &timestamp);  // An toàn, tránh warning C4996
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

    std::string typeStr = (type == TransactionType::Deposit) ? "DEPOSIT" : "TRANSFER";

    return "[" + std::string(buffer) + "] " + typeStr +
           " | From: " + fromWalletId +
           " → To: " + toWalletId +
           " | Amount: " + std::to_string(amount);
}

void recordTransaction(const Transaction& tx) {
    // Ghi vào bộ nhớ (RAM)
    DataStore::allTransactions.push_back(tx);

    // Ghi vào file (dạng json riêng)
    if (!UserFileHelper::saveTransactionLog(tx)) {
        std::cerr << "Ghi file log giao dịch thất bại.\n";
    }
}
