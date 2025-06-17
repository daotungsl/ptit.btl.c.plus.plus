#include "../../include/login.h"
#include "../../include/register.h"
#include "../../include/factory.h"
#include "../../entities/User.h"

#include "../core/manager_menu.h"  
#include "../core/user_menu.h"     

using namespace std;

void runApplication() {
	int choice = -1;
	UserRole role = UserRole::Failed;

	do {
		if (role == UserRole::Failed) {
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
					role = login();
					if (role == UserRole::Failed) pause();
					break;
				case 2:
					print("Register call!", true);
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
			if (role == UserRole::Manager) {
				showManagerMenu();
			} else {
				showUserMenu();
			}
			role = UserRole::Failed;  // Đăng xuất sau khi thoát menu
		}
	} while (choice != 0);
}
