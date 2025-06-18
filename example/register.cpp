#include "register.h"
#include "../include/factory.h"
#include "../include/UserFileHelper.h"
#include <iostream>
#include <random>

using namespace std;

// Hàm tạo mật khẩu ngẫu nhiên
std::string generateRandomPassword() {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string password;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    for (int i = 0; i < 8; ++i) {
        password += chars[dist(gen)];
    }

    return password;
}

// Hàm tạo đối tượng User mới (tách logic cho rõ ràng)
User buildUser(const std::string& username, const std::string& password) {
    return User(username, password, UserRole::User);
}

// Hàm đăng ký người dùng
void registerUser() {
    std::string username, password;

    std::cout << "===== DANG KY TAI KHOAN MOI =====" << std::endl;
    std::cout << "Nhap ten tai khoan: ";
    std::cin >> username;

    std::cout << "Nhap mat khau (bo trong de tao mat khau ngau nhien): ";
    std::cin.ignore(); // loại bỏ ký tự newline
    std::getline(std::cin, password);

    if (password.empty()) {
        password = generateRandomPassword();
        std::cout << "Mat khau ngau nhien cua ban la: " << password << std::endl;
    }

    // Tạo user
    User newUser = buildUser(username, password);

    // Lưu user vào file
    if (!UserFileHelper::saveUserToFile(newUser)) {
        std::cerr << "Loi khi luu thong tin nguoi dung.\n";
    }
}
