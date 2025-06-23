#include "register.h"
#include "factory.h"
#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../include/UserFileHelper.h"
#include "../lib/nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
using json = nlohmann::json;

std::vector<User> loadAllUsers() {
    std::vector<User> users;
    std::vector<std::string> filenames = UserFileHelper::listFilesInCategory(FileCategory::User);

    for (const auto& fileName : filenames) {
        std::string content = UserFileHelper::readStringFromFile(fileName, FileCategory::User);
        if (!content.empty()) {
            json j = json::parse(content);
            User u;
            u.setUsername(j.value("username", ""));
            u.setPassword(j.value("password", ""));
            u.setDisplayName(j.value("displayName", ""));
            u.setWalletId(j.value("walletId", ""));
            u.setPhoneNumber(j.value("phoneNumber", ""));
            u.setRole(static_cast<UserRole>(j.value("role", 1)));
            users.push_back(u);
        }
    }
    return users;
}

bool usernameExists(const std::vector<User>& users, const std::string& username) {
    for (const auto& u : users) {
        if (u.getUsername() == username) return true;
    }
    return false;
}

bool phoneExists(const std::vector<User>& users, const std::string& phone) {
    for (const auto& u : users) {
        if (u.getPhoneNumber() == phone) return true;
    }
    return false;
}

void registerNewUser() {
    std::vector<User> users = loadAllUsers();
    std::string username;
    std::string phone;

    // Nhập và kiểm tra username
    do {
        username = input("Nhap ten dang nhap: ");
        if (username.empty()) {
            print("Username khong duoc de trong.", true);
            continue;
        }
        if (usernameExists(users, username)) {
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
        if (phoneExists(users, phone)) {
            print("So dien thoai da ton tai. Hay nhap lai.", true);
        } else break;
    } while (true);

    std::string password = input("Nhap mat khau (hoac de trong): ");

    // Tạo ví mới
    Wallet wallet;
    std::string walletId = wallet.getWalletId();

    // Tạo user mới
    User newUser(username, password, UserRole::User, username, walletId, phone);

    // Tạo JSON
    json j;
    j["username"] = newUser.getUsername();
    j["password"] = newUser.getPassword();
    j["displayName"] = newUser.getDisplayName();
    j["walletId"] = newUser.getWalletId();
    j["phoneNumber"] = newUser.getPhoneNumber();
    j["role"] = static_cast<int>(newUser.getRole());

    // Ghi ra file bằng helper mới
    bool ok = UserFileHelper::writeStringToFile(username + ".json", j.dump(4), FileCategory::User);
    if (ok) {
        extern std::unordered_map<std::string, Wallet> allWallets;
        allWallets[walletId] = wallet;
        print("Dang ky thanh cong! Tro ve man hinh truoc.", true);
    } else {
        print("Dang ky that bai.", true);
    }
}
