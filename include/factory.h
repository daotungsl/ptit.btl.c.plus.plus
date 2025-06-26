#ifndef FACTORY_H
#define FACTORY_H

#include <string>

void print(const std::string& message, bool addNewLine = false);
std::string input(const std::string& prompt);
void printTitle(const std::string& text);
void pause();
std::string random4Digits();
#endif
