#ifndef DATASTORE_H
#define DATASTORE_H

#include <unordered_map>
#include <vector>
#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../entities/Transaction.h"

namespace DataStore {
    extern std::unordered_map<std::string, Wallet> allWallets;
    extern std::vector<Transaction> allTransactions;
    extern std::vector<User> allUsers;

    const std::unordered_map<std::string, Wallet>& getAllWallets();
    const std::vector<Transaction>& getAllTransactions();
    const std::vector<User>& getAllUsers();

    Wallet* getWalletById(const std::string& id);
    User* getUserByPhone(const std::string& phone);
}

#endif // DATASTORE_H
