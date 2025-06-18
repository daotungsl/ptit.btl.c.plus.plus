#include <iostream>
#include <limits>
#include "factory.h"


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
