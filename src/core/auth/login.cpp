#include <iostream>
#include "factory.h"
#include "../entities/User.h"
using namespace std;

UserRole login() {
    print("===== LOGIN =====", true);

    string userId = input("Nhap ID: ");
    string password = input("Nhap Password: ");

    print("Dang xac thuc...", true);

    if (userId == "admin" && password == "123") {
        print("Dang nhap voi quyen QUAN LY", true);
        return UserRole::Manager;
    } else if (userId == "user" && password == "123") {
        print("Dang nhap voi quyen NGUOI DUNG", true);
        return UserRole::User;
    } else {
        print("Sai ID hoac Password.", true);
        return UserRole::Failed;
    }
}