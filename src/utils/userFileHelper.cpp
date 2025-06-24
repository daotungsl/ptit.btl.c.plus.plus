#include "../include/UserFileHelper.h"
#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../entities/Transaction.h"
#include "../lib/nlohmann/json.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ctime>

namespace fs = std::filesystem;
using json = nlohmann::json;

bool UserFileHelper::writeStringToFile(const std::string& fileName, const std::string& content, FileCategory category) {
    std::string path = buildPath(fileName, category);

    std::ofstream outFile(path);
    if (outFile.is_open()) {
        outFile << content;
        outFile.close();
        return true;
    } else {
        std::cerr << "Khong the mo file de ghi: " << path << "\n";
        return false;
    }
}

std::string UserFileHelper::readStringFromFile(const std::string& fileName, FileCategory category) {
    std::string path = buildPath(fileName, category);

    std::ifstream inFile(path);
    if (inFile.is_open()) {
        std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
        return content;
    } else {
        std::cerr << "Khong the mo file de doc: " << path << "\n";
        return "";
    }
}

std::string UserFileHelper::buildPath(const std::string& fileName, FileCategory category) {
    std::string baseDir;
    switch (category) {
        case FileCategory::User:
            baseDir = "./data/users";
            break;
        case FileCategory::Wallet:
            baseDir = "./data/wallets";
            break;
        case FileCategory::TransactionLog:
            baseDir = "./data/transactions";
            break;
    }

    if (!fs::exists(baseDir)) {
        fs::create_directories(baseDir);
    }

    return baseDir + "/" + fileName;
}

std::string UserFileHelper::getCurrentDate() {
    time_t now = time(nullptr);
    tm t = {};
    localtime_s(&t, &now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &t);
    return std::string(buffer);
}

std::string UserFileHelper::getCurrentDateTime() {
    time_t now = time(nullptr);
    tm t = {};
    localtime_s(&t, &now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", &t);
    return std::string(buffer);
}

void UserFileHelper::backupOldFileIfExists(const std::string& path) {
    if (!fs::exists(path)) return;

    std::string date = getCurrentDate();
    std::string dateTime = getCurrentDateTime();

    std::string backupDir = "./backup/" + date;
    if (!fs::exists(backupDir)) {
        fs::create_directories(backupDir);
    }

    std::string fileName = fs::path(path).stem().string(); // tên không có đuôi
    std::string extension = fs::path(path).extension().string();
    std::string backupPath = backupDir + "/" + fileName + "_" + dateTime + extension;

    fs::copy(path, backupPath, fs::copy_options::overwrite_existing);
}

bool UserFileHelper::saveNewUser(const User& user) {
    json j;
    j["username"] = user.getUsername();
    j["password"] = user.getPassword();
    j["displayName"] = user.getDisplayName();
    j["walletId"] = user.getWalletId();
    j["phoneNumber"] = user.getPhoneNumber();
    j["role"] = static_cast<int>(user.getRole());

    std::string fileName = user.getUsername() + ".json";
    std::string path = buildPath(fileName, FileCategory::User);
    backupOldFileIfExists(path);

    return writeStringToFile(fileName, j.dump(4), FileCategory::User);
}

bool UserFileHelper::saveNewWallet(const Wallet& wallet) {
    json j;
    j["walletId"] = wallet.getWalletId();
    j["points"] = wallet.getPoints();
    j["transactionIds"] = wallet.getTransactionIds();

    std::string fileName = wallet.getWalletId() + ".json";
    std::string path = buildPath(fileName, FileCategory::Wallet);
    backupOldFileIfExists(path);

    return writeStringToFile(fileName, j.dump(4), FileCategory::Wallet);
}

bool UserFileHelper::saveTransactionLog(const Transaction& tx) {
    json j;
    j["transactionId"] = tx.getTransactionId();
    j["type"] = static_cast<int>(tx.getType());
    j["from"] = tx.getFromWalletId();
    j["to"] = tx.getToWalletId();
    j["amount"] = tx.getAmount();
    j["timestamp"] = tx.getTimestamp();

    std::string fileName = tx.getTransactionId() + ".json";
    return writeStringToFile(fileName, j.dump(4), FileCategory::TransactionLog);
}

bool UserFileHelper::saveUpdatedUser(const User& user) {
    return saveNewUser(user);
}

bool UserFileHelper::saveUpdatedWallet(const Wallet& wallet) {
    json j;
    j["walletId"] = wallet.getWalletId();
    j["points"] = wallet.getPoints();
    j["transactionIds"] = wallet.getTransactionIds();

    std::string fileName = wallet.getWalletId() + ".json";
    std::string path = buildPath(fileName, FileCategory::Wallet);
    backupOldFileIfExists(path);

    return writeStringToFile(fileName, j.dump(4), FileCategory::Wallet);
}


std::vector<std::string> UserFileHelper::listFilesInCategory(FileCategory category) {
    std::vector<std::string> files;
    std::string baseDir = buildPath("", category);

    for (const auto& entry : fs::directory_iterator(baseDir)) {
        if (entry.path().extension() == ".json") {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}
