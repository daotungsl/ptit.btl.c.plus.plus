#include "../entities/Wallet.h"
#include "../entities/Transaction.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>

// Danh sách tất cả các ví trong hệ thống, phải được định nghĩa bên ngoài
extern std::unordered_map<std::string, Wallet> allWallets;

// Hàm chuyển điểm giữa hai ví, đảm bảo nguyên tắc giao dịch atomic
bool transferPointsBetweenWallets(const std::string& fromId, const std::string& toId, int amount) {
    // 1. Tìm, mở ví A (ví nguồn)
    auto fromIt = allWallets.find(fromId);
    if (fromIt == allWallets.end()) {
        std::cout << "Không tìm thấy ví nguồn.\n";
        return false;
    }

    // 2. Tìm, mở ví B (ví đích)
    auto toIt = allWallets.find(toId);
    if (toIt == allWallets.end()) {
        std::cout << "Không tìm thấy ví đích.\n";
        return false;
    }

    Wallet& from = fromIt->second;
    Wallet& to = toIt->second;

    // Ghi lại trạng thái ban đầu để rollback nếu cần
    int originalFrom = from.getPoints();
    int originalTo = to.getPoints();

    // 3. Giao dịch nguyên tử
    try {
        // 3.1 Kiểm tra số dư và trừ điểm
        if (originalFrom < amount) {
            std::cout << "Low balance. Cannot proceed.\n";
            return false;
        }
        from.setPoints(originalFrom - amount);

        // 3.2 Cộng điểm vào ví B
        to.setPoints(originalTo + amount);

        // 3.3 Ghi log giao dịch
        Transaction tx(TransactionType::Transfer, fromId, toId, amount);
        recordTransaction(tx);

        std::cout << "Giao dịch chuyển " << amount << " điểm thành công.\n";
        return true;

    } catch (const std::exception& e) {
        // 3.4 Rollback nếu có lỗi
        from.setPoints(originalFrom);
        to.setPoints(originalTo);
        std::cerr << "Giao dịch thất bại do lỗi: " << e.what() << ". Đã khôi phục trạng thái.\n";
        return false;
    } catch (...) {
        from.setPoints(originalFrom);
        to.setPoints(originalTo);
        std::cerr << "Giao dịch thất bại do lỗi không xác định. Đã khôi phục trạng thái.\n";
        return false;
    }
}
