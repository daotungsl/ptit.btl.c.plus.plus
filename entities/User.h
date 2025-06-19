#ifndef USER_H
#define USER_H

#include <string>
#include "Wallet.h"  // Gắn ví người dùng

// Vai trò người dùng khi đăng nhập thành công (hoặc thất bại)
enum class UserRole {
    Failed,     // Sai tài khoản hoặc mật khẩu
    User,       // Quyền người dùng
    Manager     // Quyền quản lý
};

class User {
private:
    std::string username;
    std::string displayName;
    std::string password;
    UserRole role;
    Wallet wallet;  // Gắn thêm ví

public:
    // Constructor đầy đủ
    User(const std::string& username, const std::string& password,
         UserRole role = UserRole::Failed, const std::string& displayName = "")
        : username(username), displayName(displayName), password(password), role(role), wallet() {}

    // Constructor mặc định
    User() : username(""), displayName(""), password(""), role(UserRole::Failed), wallet() {}

    // Getter
    std::string getUsername() const { return username; }
    std::string getDisplayName() const { return displayName; }
    std::string getPassword() const { return password; }
    UserRole getRole() const { return role; }
    Wallet& getWallet() { return wallet; }
    const Wallet& getWallet() const { return wallet; }

    // Setter
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setDisplayName(const std::string& newDisplayName) { displayName = newDisplayName; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setRole(UserRole newRole) { role = newRole; }

    // Kiểm tra vai trò
    bool isManager() const { return role == UserRole::Manager; }
    bool isUser() const { return role == UserRole::User; }
    bool isFailed() const { return role == UserRole::Failed; }
};

#endif // USER_H
