#ifndef USER_ROLE_H
#define USER_ROLE_H
// Vai trò người dùng khi đăng nhập thành công (hoặc thất bại)
enum class UserRole {
    Failed,     // Sai tài khoản hoặc mật khẩu
    User,       // Quyền người dùng
    Manager     // Quyền quản lý
};
#endif