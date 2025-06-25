#include "../entities/Transaction.h"
#include "../include/UserFileHelper.h"
#include "../include/DataStore.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>

static std::string generateTransactionId() {
    std::stringstream ss;
    ss << "tx_" << std::time(nullptr);
    return ss.str();
}

Transaction::Transaction(TransactionType type, const std::string& from, const std::string& to, int amount)
    : type(type), fromWalletId(from), toWalletId(to), amount(amount), timestamp(std::time(nullptr)) {
    transactionId = generateTransactionId();
}

std::string Transaction::getTransactionId() const { return transactionId; }
void Transaction::setTransactionId(const std::string& id) { transactionId = id; }

std::string Transaction::getFromWalletId() const { return fromWalletId; }
std::string Transaction::getToWalletId() const { return toWalletId; }
int Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
TransactionType Transaction::getType() const { return type; }
void Transaction::setTimestamp(std::time_t t) { timestamp = t; }

std::string Transaction::toString() const {
    char buffer[100];
    std::tm timeInfo = {};
    localtime_s(&timeInfo, &timestamp);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

    std::string typeStr = (type == TransactionType::Deposit) ? "DEPOSIT" : "TRANSFER";

    // 🔎 Tìm người gửi
    std::string senderInfo = fromWalletId;
    std::string receiverInfo = toWalletId;
    const auto& users = DataStore::getAllUsers();
    for (const auto& user : users) {
        if (user.getWalletId() == fromWalletId) {
            senderInfo = user.getPhoneNumber() + " (" + user.getDisplayName() + ")";
        }
        if (user.getWalletId() == toWalletId) {
            receiverInfo = user.getPhoneNumber() + " (" + user.getDisplayName() + ")";
        }
    }

    return "[" + std::string(buffer) + "] " + typeStr +
           " | TxID: " + transactionId +
           " | From: " + senderInfo +
           " To: " + receiverInfo +
           " | Amount: " + std::to_string(amount);
}


void recordTransaction(const Transaction& tx) {
    Wallet* from = DataStore::getWalletById(tx.getFromWalletId());
    Wallet* to = DataStore::getWalletById(tx.getToWalletId());

    if (from) {
        from->addTransactionId(tx.getTransactionId());
        DataStore::syncWallet(from->getWalletId());  // ✅ dùng hàm sync từ DataStore
    }

    if (to) {
        to->addTransactionId(tx.getTransactionId());
        DataStore::syncWallet(to->getWalletId());    // ✅ dùng hàm sync từ DataStore
    }

    UserFileHelper::saveTransactionLog(tx); // vẫn ghi log trực tiếp
}
