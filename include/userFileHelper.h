#ifndef USERFILEHELPER_H
#define USERFILEHELPER_H

#include "../entities/User.h"
#include <string>

class UserFileHelper {
public:
    static bool saveUserToFile(const User& user);
};

#endif
