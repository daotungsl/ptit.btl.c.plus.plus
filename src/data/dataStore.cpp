#include "../include/DataStore.h"

namespace DataStore {
    std::unordered_map<std::string, Wallet> allWallets;
    std::vector<Transaction> allTransactions;
    std::vector<User> allUsers;

    const std::unordered_map<std::string, Wallet>& getAllWallets() {
        return allWallets;
    }

    const std::vector<Transaction>& getAllTransactions() {
        return allTransactions;
    }

    const std::vector<User>& getAllUsers() {
        return allUsers;
    }

    Wallet* getWalletById(const std::string& id) {
        auto it = allWallets.find(id);
        if (it != allWallets.end()) return &it->second;
        return nullptr;
    }

    User* getUserByPhone(const std::string& phone) {
        for (auto& user : allUsers) {
            if (user.getPhoneNumber() == phone)
                return &user;
        }
        return nullptr;
    }
}
