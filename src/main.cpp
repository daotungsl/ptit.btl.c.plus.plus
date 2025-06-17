#include "login.h"
#include "register.h"
#include "factory.h"

using namespace std;

int main() {
	int choice = -1;

	do {
		printTitle("WELLCOME TO Reward Wallet Management");


		print("1. Login", true);
		print("2. Register", true);
		print("0. Exit", true);

		string choiceStr = input("Choice number: ");
		try {
			choice = stoi(choiceStr);
		}
		catch (...) {
			print("Wrong number!", true);
			continue;
		}

		switch (choice) {
		case 1:
			print("Login call!", true);
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

		if (choice != 0) pause();

	} while (choice != 0);

	return 0;
}
