#include "../entities/User.h"
#include "../entities/Wallet.h"
#include "../include/UserFileHelper.h"
#include "../include/hash.h"
#include <iostream>

void insertSeedData() {
    std::string username1 = "admin";
    std::string phone1 = "099";
    std::string password1 = PasswordUtils::hashPassword("123");
    Wallet wallet1;
    User user1(username1, password1, UserRole::User, username1, wallet1.getWalletId(), phone1);
    wallet1.setPoints(1000);



    std::string username2 = "daotung1";
    std::string phone2 = "097";
    std::string password2 = PasswordUtils::hashPassword("123");
    Wallet wallet2;
    User user2(username2, password2, UserRole::User, username2, wallet2.getWalletId(), phone2);
    wallet2.setPoints(2000);

    std::string username3 = "daotung";
    std::string phone3 = "098";
    std::string password3 = PasswordUtils::hashPassword("123");
    Wallet wallet3;
    User user3(username3, password3, UserRole::User, username3, wallet3.getWalletId(), phone3);
    wallet3.setPoints(1000);

    bool ok1 = UserFileHelper::saveNewUser(user1);
    bool ok2 = UserFileHelper::saveNewWallet(wallet1);
    bool ok3 = UserFileHelper::saveNewUser(user2);
    bool ok4 = UserFileHelper::saveNewWallet(wallet2);

    if (ok1 && ok2 && ok3 && ok4) {
        std::cout << "\n\n==> Seed data thanh cong!\n";
    } else {
        std::cerr << "\n\n==> Seed data that bai.\n";
    }
}
