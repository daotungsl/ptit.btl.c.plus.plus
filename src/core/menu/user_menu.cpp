#include "../../include/factory.h"

void showUserMenu() {
    int choice = -1;

    do {
        print("\n===== USER MENU =====", true);
        print("1. Xem thong tin ca nhan", true);
        print("2. Su dung vi diem", true);
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
                print("Thong tin ca nhan...", true);
                // TODO: Gọi hàm hiển thị thông tin cá nhân
                break;
            case 2:
                print("Su dung vi diem...", true);
                // TODO: Gọi menu ví điểm ở đây
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
