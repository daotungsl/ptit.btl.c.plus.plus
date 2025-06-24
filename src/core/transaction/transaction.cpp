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

    return "[" + std::string(buffer) + "] " + typeStr +
           " | From: " + fromWalletId +
           " → To: " + toWalletId +
           " | Amount: " + std::to_string(amount);
}

void recordTransaction(const Transaction& tx) {
    Wallet* from = DataStore::getWalletById(tx.getFromWalletId());
    Wallet* to = DataStore::getWalletById(tx.getToWalletId());

    if (from) {
        from->addTransactionId(tx.getTransactionId());
        UserFileHelper::saveNewWallet(*from);
    }

    if (to) {
        to->addTransactionId(tx.getTransactionId());
        UserFileHelper::saveNewWallet(*to);
    }

    UserFileHelper::saveTransactionLog(tx);
}
