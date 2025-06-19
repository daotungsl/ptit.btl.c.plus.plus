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
    std::string displayName;
    std::string password;
    UserRole role;
    std::string walletId;  // chỉ lưu mã ví, không lưu đối tượng Wallet

public:
    // Constructor đầy đủ
    User(const std::string& username, const std::string& password,
         UserRole role = UserRole::Failed,
         const std::string& displayName = "",
         const std::string& walletId = "")
        : username(username), displayName(displayName), password(password), role(role), walletId(walletId) {}

    // Constructor mặc định
    User() : username(""), displayName(""), password(""), role(UserRole::Failed), walletId("") {}

    // Getter
    std::string getUsername() const { return username; }
    std::string getDisplayName() const { return displayName; }
    std::string getPassword() const { return password; }
    UserRole getRole() const { return role; }
    std::string getWalletId() const { return walletId; }

    // Setter
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setDisplayName(const std::string& newDisplayName) { displayName = newDisplayName; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setRole(UserRole newRole) { role = newRole; }
    void setWalletId(const std::string& newWalletId) { walletId = newWalletId; }

    // Kiểm tra vai trò
    bool isManager() const { return role == UserRole::Manager; }
    bool isUser() const { return role == UserRole::User; }
    bool isFailed() const { return role == UserRole::Failed; }
};

#endif // USER_H
