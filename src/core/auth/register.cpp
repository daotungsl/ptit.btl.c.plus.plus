#include "register.h"
#include "../include/factory.h"
#include "../include/hash.h"
#include <fstream>
#include <filesystem>

void registerUser() {
    print("===== DANG KY =====", true);

    std::string username = input("Nhap ten dang nhap: ");
    std::string password = input("Nhap mat khau (de trong de tu dong sinh): ");

    if (password.empty()) {
        password = "123456";  // Tạm thời dùng default
        print("Da sinh mat khau mac dinh: 123456", true);
    }

    std::string role = input("Nhap vai tro (User/Manager): ");

    std::ofstream fout("data/users/" + username + ".txt");
    // fout << hashPassword(password) << "\n";
    fout << role << "\n";
    fout.close();

    print("Dang ky thanh cong!", true);
}
