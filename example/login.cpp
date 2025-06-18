#include <iostream>
#include "factory.h"
#include "../entities/User.h"
using namespace std;

User login() {
    string username, password;

	printTitle("DANG NHAP HE THONG");
    username = input("Tai khoan: ");
    password = input("Mat khau: ");

    if (username == "admin" && password == "123") {
        print("Dang nhap thanh cong voi vai tro QUAN LY.", true);
        return User(username, password, UserRole::Manager);
    } else if (username == "user" && password == "123") {
        print("Dang nhap thanh cong voi vai tro NGUOI DUNG.", true);
        return User(username, password, UserRole::User);
    } else {
        print("Dang nhap that bai. Sai tai khoan hoac mat khau.", true);
        return User(username, password, UserRole::Failed);
    }
}