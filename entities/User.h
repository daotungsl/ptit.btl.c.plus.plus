#ifndef USER_H
#define USER_H

#include <string>

// Vai trò người dùng khi đăng nhập thành công (hoặc thất bại)
enum class UserRole {
    Failed,     // Sai tài khoản hoặc mật khẩu
    User,       // Quyền người dùng
    Manager     // Quyền quản lý
};

class User {
private:
    std::string username;
    std::string password;
    UserRole role;

public:
    // Constructor
    User(const std::string& username, const std::string& password, UserRole role = UserRole::Failed)
        : username(username), password(password), role(role) {}

    // Getter
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    UserRole getRole() const { return role; }

    // Setter
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setRole(UserRole newRole) { role = newRole; }

    // Kiểm tra có phải quản lý không
    bool isManager() const { return role == UserRole::Manager; }

    // Kiểm tra có phải người dùng không
    bool isUser() const { return role == UserRole::User; }

    // Kiểm tra đăng nhập thất bại
    bool isFailed() const { return role == UserRole::Failed; }
};

#endif // USER_H
