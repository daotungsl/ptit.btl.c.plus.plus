#include "register.h"
#include "factory.h"
#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../include/UserFileHelper.h"
#include "../include/DataStore.h"
#include "../lib/nlohmann/json.hpp"
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

    // Nhập và kiểm tra username
    do {
        username = input("Nhap ten dang nhap: ");
        if (username.empty()) {
            print("Username khong duoc de trong.", true);
            continue;
        }
        if (usernameExists(username)) {
            print("Username da ton tai. Hay nhap lai.", true);
        } else break;
    } while (true);

    // Nhập và kiểm tra số điện thoại
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

    std::string password = input("Nhap mat khau (hoac de trong): ");

    // Tạo ví mới
    Wallet wallet;
    std::string walletId = wallet.getWalletId();

    // Tạo user mới
    User newUser(username, password, UserRole::User, username, walletId, phone);

    // Ghi ra file
    bool okUser = UserFileHelper::saveNewUser(newUser);
    bool okWallet = UserFileHelper::saveNewWallet(wallet);

    if (okUser && okWallet) {
        // Ghi vào bộ nhớ tạm (DataStore)
        allUsers.push_back(newUser);
        allWallets[walletId] = wallet;

        print("Dang ky thanh cong! Tro ve man hinh truoc.", true);
    } else {
        print("Dang ky that bai.", true);
    }
}
