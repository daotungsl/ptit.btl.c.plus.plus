#ifndef USER_H
#define USER_H

#include <string>

enum class UserRole {
    Failed,
    User,
    Manager
};

class User {
private:
    std::string username;
    std::string displayName;
    std::string password;
    UserRole role;
    std::string walletId;
    std::string phoneNumber; // << THÊM DÒNG NÀY

public:
    // Constructor đầy đủ
    User(const std::string& username, const std::string& password,
         UserRole role = UserRole::Failed,
         const std::string& displayName = "",
         const std::string& walletId = "",
         const std::string& phoneNumber = "") // << THÊM DÒNG NÀY
        : username(username), displayName(displayName), password(password),
          role(role), walletId(walletId), phoneNumber(phoneNumber) {}

    User() : username(""), displayName(""), password(""),
             role(UserRole::Failed), walletId(""), phoneNumber("") {}

    // Getter
    std::string getUsername() const { return username; }
    std::string getDisplayName() const { return displayName; }
    std::string getPassword() const { return password; }
    UserRole getRole() const { return role; }
    std::string getWalletId() const { return walletId; }
    std::string getPhoneNumber() const { return phoneNumber; } // << THÊM

    // Setter
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setDisplayName(const std::string& newDisplayName) { displayName = newDisplayName; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
    void setRole(UserRole newRole) { role = newRole; }
    void setWalletId(const std::string& newWalletId) { walletId = newWalletId; }
    void setPhoneNumber(const std::string& newPhone) { phoneNumber = newPhone; } // << THÊM

    // Kiểm tra vai trò
    bool isManager() const { return role == UserRole::Manager; }
    bool isUser() const { return role == UserRole::User; }
    bool isFailed() const { return role == UserRole::Failed; }
};

#endif // USER_H
