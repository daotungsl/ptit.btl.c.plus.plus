// user_menu.cpp - cập nhật dùng DataStore::syncUser thay vì gọi UserFileHelper trực tiếp
#include "../include/factory.h"
#include "../entities/User.h"
#include "../include/walletService.h"
#include "../include/DataStore.h"

void showUserMenu(User currentUser) {
    int choice = -1;

    do {
        print("\n===== USER MENU =====", true);
        print("1. Xem thong tin ca nhan", true);
        print("2. Thay doi ten hien thi", true);
        print("3. Thay doi mat khau", true);
        print("4. Vi diem", true);
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
                print("\n=== THONG TIN CA NHAN ===", true);
                print("Ten dang nhap: " + currentUser.getUsername(), true);
                print("Ten hien thi: " + currentUser.getDisplayName(), true);
                break;
            case 2: {
                std::string newName = input("Nhap ten hien thi moi: ");
                currentUser.setDisplayName(newName);
                DataStore::syncUser(currentUser.getUsername()); // ✅ đồng bộ user sau thay đổi tên
                print("Da cap nhat ten hien thi!", true);
                break;
            }
            case 3: {
                std::string newPass = input("Nhap mat khau moi: ");
                currentUser.setPassword(newPass);
                DataStore::syncUser(currentUser.getUsername()); // ✅ đồng bộ user sau đổi mật khẩu
                print("Da cap nhat mat khau!", true);
                break;
            }
            case 4:
                showWalletMenu(currentUser);
                break;
            case 0:
                DataStore::syncUser(currentUser.getUsername()); // ✅ backup user trước khi đăng xuất
                print("Dang xuat thanh cong!", true);
                return;
            default:
                print("Lua chon khong hop le.", true);
                break;
        }

    } while (true);
}
