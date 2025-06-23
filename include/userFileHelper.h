#ifndef USERFILEHELPER_H
#define USERFILEHELPER_H

#include <string>
#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../entities/Transaction.h"  // nếu có
#include <ctime>

enum class FileCategory {
    User,
    Wallet,
    TransactionLog
};

class UserFileHelper {
public:
    static bool saveNewUser(const User& user);
    static bool saveNewWallet(const Wallet& wallet);
    static bool saveTransactionLog(const Transaction& tx);

    static std::string readStringFromFile(const std::string& fileName, FileCategory category);
    static bool writeStringToFile(const std::string& fileName, const std::string& content, FileCategory category);
    static std::vector<std::string> listFilesInCategory(FileCategory category);
private:
    static std::string buildPath(const std::string& fileName, FileCategory category);
    static void backupOldFileIfExists(const std::string& path);
    static std::string getCurrentDate();
};

#endif // USERFILEHELPER_H
