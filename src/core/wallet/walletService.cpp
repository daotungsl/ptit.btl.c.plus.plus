#include "../include/walletService.h"
#include "../entities/Wallet.h"
#include "../entities/Transaction.h"
#include "../entities/User.h"
#include "../include/factory.h"
#include "../include/DataStore.h"
#include "../include/UserFileHelper.h"
#include "../include/otp.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>

using namespace DataStore;

void showWalletMenu(User& user) {
    Wallet* wallet = getWalletById(user.getWalletId());
    if (wallet) {
        print("\n===== VI DIEM =====", true);
        print("So du hien tai: " + std::to_string(wallet->getPoints()) + " diem", true);
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
                showTransactionHistory(user);
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
    User* receiverUser = getUserByPhone(phone);

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

    std::string confirm = input("Ban co chac chan muon chuyen " + std::to_string(amount) +
                                " diem cho " + receiverUser->getUsername() + "? (y/n): ");
    if (confirm != "y" && confirm != "Y") {
        print("Huy giao dich.", true);
        return;
    }

    if (!OtpManager::confirmOtpForAction(user.getPhoneNumber())) {
        print("❌ Xac thuc OTP that bai. Huy giao dich.", true);
        return;
    }

    bool success = transferPointsBetweenWallets(user.getWalletId(), receiverUser->getWalletId(), amount);
    if (!success) {
        print("Chuyen diem that bai.", true);
    }
}

bool transferPointsBetweenWallets(const std::string& fromId, const std::string& toId, int amount) {
    Wallet* from = getWalletById(fromId);
    Wallet* to = getWalletById(toId);

    if (!from || !to) {
        std::cerr << "Khong tim thay vi nguon hoac vi dich.\n";
        return false;
    }

    if (from->getPoints() < amount) {
        std::cerr << "So du khong du. Khong the chuyen.\n";
        return false;
    }

    from->deductPoints(amount);
    to->addPoints(amount);

    Transaction tx(TransactionType::Transfer, fromId, toId, amount);
    UserFileHelper::saveTransactionLog(tx);  // log vẫn dùng trực tiếp

    from->addTransactionId(tx.getTransactionId());
    to->addTransactionId(tx.getTransactionId());

    DataStore::syncWallet(from->getWalletId());  // ✅ gọi qua DataStore
    DataStore::syncWallet(to->getWalletId());

    std::cout << "Chuyen " << amount << " diem thanh cong!\n";
    return true;
}

void showTransactionHistory(User& user) {
    std::string walletId = user.getWalletId();
    DataStore::loadAllTransactions();
    const auto& transactions = getAllTransactions();

    print("\n===== LICH SU GIAO DICH =====", true);
    bool found = false;
    for (const auto& tx : transactions) {
        if (tx.getFromWalletId() == walletId || tx.getToWalletId() == walletId) {
            print(tx.toString(), true);
            found = true;
        }
    }
    if (!found) {
        print("Khong co giao dich nao lien quan toi vi cua ban.", true);
    }
}
