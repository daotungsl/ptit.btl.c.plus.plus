#include <iostream>
#include "factory.h"
#include "../entities/User.h"
using namespace std;

User login() {
// viết nội dung màn hình và xử lý đăng nhập tại đây.
// tài khoản của quản lý là: admin. Tài khoản của người dùng là user
// mật khẩu đều là 123
// hàm yêu cầu trả về class user khi đăng nhập xong
return User("abcd","123",UserRole::Failed);
}