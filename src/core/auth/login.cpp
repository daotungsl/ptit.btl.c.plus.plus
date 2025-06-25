#include <iostream>
#include "factory.h"
#include "../entities/User.h"
#include "../include/UserFileHelper.h"
#include "../lib/nlohmann/json.hpp"
#include "../include/hash.h" // ✅ THÊM DÒNG NÀY

using namespace std;
using json = nlohmann::json;

User login() {
    string username, password;

    printTitle("DANG NHAP HE THONG");
    username = input("Tai khoan: ");
    password = input("Mat khau: ");

    string content = UserFileHelper::readStringFromFile(username + ".json", FileCategory::User);
    if (content.empty()) {
        print("Dang nhap that bai. Khong tim thay tai khoan.", true);
        return User(username, password, UserRole::Failed, username);
    }

    try {
        json j = json::parse(content);
        string storedPassword = j.value("password", "");

        if (PasswordUtils::verifyPassword(password, storedPassword)) { // ✅ so sánh hash
            UserRole role = static_cast<UserRole>(j.value("role", 1));
            string displayName = j.value("displayName", "");
            string walletId = j.value("walletId", "");
            string phone = j.value("phoneNumber", "");

            print("Dang nhap thanh cong!", true);
            return User(username, storedPassword, role, displayName, walletId, phone);
        } else {
            print("Sai mat khau.", true);
            return User(username, password, UserRole::Failed, username);
        }
    } catch (...) {
        print("Loi khi doc file tai khoan.", true);
        return User(username, password, UserRole::Failed, username);
    }
}
