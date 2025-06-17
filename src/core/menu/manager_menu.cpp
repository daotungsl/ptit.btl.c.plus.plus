#include "../include/factory.h"

void showManagerMenu() {
    int choice = -1;

    do {
        print("\n===== MANAGER MENU =====", true);
        print("1. Quan ly tai khoan", true);
        print("2. Xem bao cao he thong", true);
        print("0. Dang xuat", true);

        std::string choiceStr = input("Lua chon: ");
        try {
            choice = std::stoi(choiceStr);
        } catch (...) {
            print("Lua chon khong hop le.", true);
            continue;
        }

        switch (choice) {
            case 1:
                print("Quan ly tai khoan...", true);
                // TODO: Gọi hàm quản lý tài khoản ở đây
                break;
            case 2:
                print("Xem bao cao he thong...", true);
                // TODO: Gọi hàm hiển thị báo cáo ở đây
                break;
            case 0:
                print("Dang xuat thanh cong!", true);
                return;
            default:
                print("Lua chon khong hop le.", true);
                break;
        }
    } while (true);
}
