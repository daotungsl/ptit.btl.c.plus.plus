#include "register.h"
#include "../include/factory.h"
#include "../include/UserFileHelper.h"
#include <iostream>
#include <random>

using namespace std;

// Hàm tạo mật khẩu ngẫu nhiên
string generateRandomPassword() {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string password;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, chars.size() - 1);

    for (int i = 0; i < 8; ++i) {
        password += chars[dist(gen)];
    }

    return password;
}

// Hàm tạo đối tượng User mới (mặc định role là User)
User buildUser(const string& username, const string& password) {
    return User(username, password, UserRole::User);
}

// Hàm đăng ký người dùng
void registerUser() {
    string username, password;

    printTitle("DANG KY TAI KHOAN MOI");

    username = input("Nhap ten tai khoan: ");
    password = input("Nhap mat khau (bo trong de tao mat khau ngau nhien): ");

    if (password.empty()) {
        password = generateRandomPassword();
        print("Mat khau ngau nhien cua ban la: " + password, true);
    }

    User newUser = buildUser(username, password);

    if (UserFileHelper::saveUserToFile(newUser)) {
        print("Dang ky thanh cong!", true);
    } else {
        print("Loi khi luu thong tin nguoi dung.", true);
    }
}
