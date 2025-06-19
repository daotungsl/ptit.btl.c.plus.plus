#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <random>
#include <sstream>

class Wallet {
private:
    std::string walletId;  // Mã định danh duy nhất
    int points;

    // Tạo mã ID ngẫu nhiên (8 ký tự hex)
    static std::string generateUniqueId() {
        std::stringstream ss;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);
        for (int i = 0; i < 8; ++i) {
            ss << std::hex << dis(gen);
        }
        return ss.str();
    }

public:
    // Constructor mặc định
    Wallet() : walletId(generateUniqueId()), points(0) {}

    // Getter
    std::string getWalletId() const { return walletId; }
    int getPoints() const { return points; }

    // Setter
    void setPoints(int newPoints) { points = newPoints; }

    // Nạp/trừ điểm
    void addPoints(int amount) { points += amount; }
    bool deductPoints(int amount) {
        if (amount > points) return false;
        points -= amount;
        return true;
    }
};

#endif // WALLET_H
