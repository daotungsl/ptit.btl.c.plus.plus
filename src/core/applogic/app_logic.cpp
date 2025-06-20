#include "../entities/User.h"
#include "../include/factory.h"
#include "../../core/menu/manager_menu.h"
#include "../../core/menu/user_menu.h"
#include "../../core/auth/auth.h"

using namespace std;

void runApplication() {
	int choice = -1;
	User user;
	do {
		if (user.getRole() == UserRole::Failed) {
			printTitle("WELLCOME TO Reward Wallet Management");

			print("1. Login", true);
			print("2. Register", true);
			print("0. Exit", true);

			string choiceStr = input("Choice number: ");
			try {
				choice = stoi(choiceStr);
			} catch (...) {
				print("Wrong number!", true);
				continue;
			}

			switch (choice) {
				case 1:
					user = handleLogin();
					if (user.getRole() == UserRole::Failed) pause();
					break;
				case 2:
					handleRegister(); 
					pause();
					break;
				case 0:
					print("Goodbye!", true);
					break;
				default:
					print("Wrong choice.", true);
					break;
			}
		} else {
			// Đã đăng nhập thành công
			if (user.getRole() == UserRole::Manager) {
				showManagerMenu(user);
			} else {
				showUserMenu(user);
			}
			user.setRole(UserRole::Failed);  // Đăng xuất sau khi thoát menu
		}
	} while (choice != 0);
}
