#include <iostream>
#include "factory.h"
#include "../entities/User.h"
using namespace std;

User login() {
    string username, password;

    cout << "===== DANG NHAP HE THONG =====" << endl;
    cout << "Tai khoan: ";
    cin >> username;
    cout << "Mat khau: ";
    cin >> password;

    if (username == "admin" && password == "123") {
        cout << "Dang nhap thanh cong voi vai tro QUAN LY.\n";
        return User(username, password, UserRole::Manager);
    } else if (username == "user" && password == "123") {
        cout << "Dang nhap thanh cong voi vai tro NGUOI DUNG.\n";
        return User(username, password, UserRole::User);
    } else {
        cout << "Dang nhap that bai. Sai tai khoan hoac mat khau.\n";
        return User(username, password, UserRole::Failed);
    }
}
