#include "register.h"
#include "factory.h"
#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../include/UserFileHelper.h"
#include "../include/DataStore.h"
#include "../lib/nlohmann/json.hpp"
#include "../include/hash.h" // ✅ THÊM DÒNG NÀY
#include <iostream>
#include <filesystem>
#include <vector>

using json = nlohmann::json;
using namespace DataStore;

bool usernameExists(const std::string& username) {
    for (const auto& u : allUsers) {
        if (u.getUsername() == username) return true;
    }
    return false;
}

bool phoneExists(const std::string& phone) {
    for (const auto& u : allUsers) {
        if (u.getPhoneNumber() == phone) return true;
    }
    return false;
}

void registerNewUser() {
    std::string username;
    std::string phone;

    do {
        username = input("Tao ten dang nhap: ");
        if (username.empty()) {
            print("Username khong duoc de trong.", true);
            continue;
        }
        if (usernameExists(username)) {
            print("Username da ton tai. Hay nhap lai.", true);
        } else break;
    } while (true);

    do {
        phone = input("Nhap so dien thoai: ");
        if (phone.empty()) {
            print("So dien thoai khong duoc de trong.", true);
            continue;
        }
        if (phoneExists(phone)) {
            print("So dien thoai da ton tai. Hay nhap lai.", true);
        } else break;
    } while (true);

    std::string rawPassword = input("Nhap mat khau (hoac de trong): ");
    std::string hashedPassword = PasswordUtils::hashPassword(rawPassword); // ✅ hash

    Wallet wallet;
    std::string walletId = wallet.getWalletId();

    User newUser(username, hashedPassword, UserRole::User, username, walletId, phone);

    bool okUser = UserFileHelper::saveNewUser(newUser);
    bool okWallet = UserFileHelper::saveNewWallet(wallet);

    if (okUser && okWallet) {
        allUsers.push_back(newUser);
        allWallets[walletId] = wallet;

        print("Dang ky thanh cong! Tro ve man hinh truoc.", true);
    } else {
        print("Dang ky that bai.", true);
    }
}
