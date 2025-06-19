#include <iostream>
#include "factory.h"
#include "../entities/User.h"
using namespace std;

User login() {
// viết nội dung màn hình và xử lý đăng nhập tại đây.
// tài khoản của quản lý là: admin. Tài khoản của người dùng là user
// mật khẩu đều là 123
// hàm yêu cầu trả về class user khi đăng nhập xong
    string username, password;

	printTitle("DANG NHAP HE THONG");
    username = input("Tai khoan: ");
    password = input("Mat khau: ");

    if (username == "admin" && password == "123") {
        print("Dang nhap thanh cong voi vai tro QUAN LY.", true);
        return User(username, password, UserRole::Manager,username);
    } else if (username == "user" && password == "123") {
        print("Dang nhap thanh cong voi vai tro NGUOI DUNG.", true);
        return User(username, password, UserRole::User,username);
    } else {
        print("Dang nhap that bai. Sai tai khoan hoac mat khau.", true);
        return User(username, password, UserRole::Failed,username);
    }
}