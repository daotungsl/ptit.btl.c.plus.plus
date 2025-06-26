#include <iostream>
#include <limits>
#include "factory.h"
#include <random>

using namespace std;

void print(const string& message, bool addNewLine) {
    cout << message;
    if (addNewLine) {
        cout << endl;
    }
}

string input(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin >> ws, value);
    return value;
}

void printTitle(const string& text) {
    cout << "\n=== " << text << " ===\n";
}

void pause() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

std::string random4Digits() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1000, 9999);
    return std::to_string(dis(gen));
}