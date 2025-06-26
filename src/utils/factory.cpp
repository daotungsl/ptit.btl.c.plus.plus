#include <iostream>
#include <limits>
#include "factory.h"
#include <random>


using namespace std;



void setColor(ConsoleColor color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

void resetColor() {
    setColor(ConsoleColor::Default);
}

void print(const string& message, bool addNewLine, ConsoleColor color) {
    setColor(color);
    cout << message;
    if (addNewLine) {
        cout << endl;
    }
    resetColor();
}


string input(const string& prompt, ConsoleColor color) {
    string value;
    setColor(color);
    cout << prompt;
    resetColor();
    getline(cin >> ws, value);
    return value;
}


void printTitle(const string& text, ConsoleColor color) {
    setColor(color);
    cout << "\n=== " << text << " ===\n";
    resetColor();
}


void pause(ConsoleColor color) {
    setColor(color);
    cout << "\nNhan Enter de tiep tuc...";
    resetColor();

    // Xoá bộ đệm trước khi đợi Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

std::string random4Digits() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1000, 9999);
    return std::to_string(dis(gen));
}