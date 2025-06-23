#include "../include/walletService.h"
#include "../entities/Wallet.h"
#include "../entities/Transaction.h"
#include "../entities/User.h"
#include "../include/factory.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>

// Danh sách tất cả các ví và giao dịch trong hệ thống
extern std::unordered_map<std::string, Wallet> allWallets;
extern std::vector<Transaction> allTransactions;
extern std::vector<User> allUsers;

void showWalletMenu(User& user) {
    // Hiển thị số dư luôn khi vào menu
    auto it = allWallets.find(user.getWalletId());
    if (it != allWallets.end()) {
        print("\n===== VI DIEM =====", true);
        print("So du hien tai: " + std::to_string(it->second.getPoints()) + " diem", true);
    } else {
        print("Khong tim thay vi cua ban.", true);
        return;
    }

    int choice = -1;
    do {
        print("\n1. Chuyen diem", true);
        print("2. Xem lich su giao dich", true);
        print("0. Quay lai", true);

        std::string choiceStr = input("Lua chon: ");
        try {
            choice = std::stoi(choiceStr);
        } catch (...) {
            print("Lua chon khong hop le.", true);
            continue;
        }

        switch (choice) {
            case 1:
                transferPointsUI(user);
                break;
            case 2:
                showTransactionHistory(user);  // sẽ gọi hàm bên transactionService sau
                break;
            case 0:
                return;
            default:
                print("Lua chon khong hop le.", true);
                break;
        }
    } while (true);
}

void transferPointsUI(User& user) {
    std::string phone = input("Nhap so dien thoai nguoi nhan: ");

    // Tìm user theo số điện thoại
    User* receiverUser = nullptr;
    for (auto& u : allUsers) {
        if (u.getPhoneNumber() == phone) {
            receiverUser = &u;
            break;
        }
    }

    if (!receiverUser) {
        print("Khong tim thay nguoi nhan voi so dien thoai da nhap.", true);
        return;
    }

    std::string amountStr = input("Nhap so diem muon chuyen: ");
    int amount = 0;
    try {
        amount = std::stoi(amountStr);
    } catch (...) {
        print("So diem khong hop le.", true);
        return;
    }

    if (amount <= 0) {
        print("So diem phai lon hon 0.", true);
        return;
    }

    // Xac nhan
    std::string confirm = input("Ban co chac chan muon chuyen " + std::to_string(amount) + 
                                " diem cho " + receiverUser->getUsername() + "? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        print("Huy giao dich.", true);
        return;
    }

    bool success = transferPointsBetweenWallets(user.getWalletId(), receiverUser->getWalletId(), amount);
    if (!success) {
        print("Chuyen diem that bai.", true);
    }
}

// Giao dịch chuyển điểm giữa hai ví
bool transferPointsBetweenWallets(const std::string& fromId, const std::string& toId, int amount) {
    auto fromIt = allWallets.find(fromId);
    if (fromIt == allWallets.end()) {
        std::cout << "Không tìm thấy ví nguồn.\n";
        return false;
    }

    auto toIt = allWallets.find(toId);
    if (toIt == allWallets.end()) {
        std::cout << "Không tìm thấy ví đích.\n";
        return false;
    }

    Wallet& from = fromIt->second;
    Wallet& to = toIt->second;

    int originalFrom = from.getPoints();
    int originalTo = to.getPoints();

    try {
        if (originalFrom < amount) {
            std::cout << "So du khong du. Khong the chuyen.\n";
            return false;
        }

        from.setPoints(originalFrom - amount);
        to.setPoints(originalTo + amount);

        Transaction tx(TransactionType::Transfer, fromId, toId, amount);
        recordTransaction(tx);  // Ghi log
        std::cout << "Giao dịch chuyển " << amount << " điểm thành công.\n";
        return true;

    } catch (const std::exception& e) {
        from.setPoints(originalFrom);
        to.setPoints(originalTo);
        std::cerr << "Giao dịch thất bại: " << e.what() << ". Đã khôi phục trạng thái.\n";
        return false;
    } catch (...) {
        from.setPoints(originalFrom);
        to.setPoints(originalTo);
        std::cerr << "Giao dịch thất bại do lỗi không xác định. Đã khôi phục trạng thái.\n";
        return false;
    }
}
