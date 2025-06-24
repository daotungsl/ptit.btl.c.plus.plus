#ifndef HASH_H
#define HASH_H

#include <string>

namespace PasswordUtils {
    std::string hashPassword(const std::string& raw);
    bool verifyPassword(const std::string& raw, const std::string& hashed);
}

#endif