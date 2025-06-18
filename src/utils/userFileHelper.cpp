#include "../include/UserFileHelper.h"
#include "../entities/User.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../lib/nlohmann/json.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

bool UserFileHelper::saveUserToFile(const User& user) {
    std::string folderPath = "./data";
    std::string fileName = user.getUsername() + ".json";
    std::string filePath = folderPath + "/" + fileName;

    // Tạo thư mục nếu chưa tồn tại
    if (!fs::exists(folderPath)) {
        fs::create_directories(folderPath);
    }

    // Chuẩn bị dữ liệu JSON
    json jsonDataUser;
    jsonDataUser["username"] = user.getUsername();
    jsonDataUser["password"] = user.getPassword();
    jsonDataUser["role"] = static_cast<int>(user.getRole()); // chuyển enum sang int

    // Ghi vào file
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << jsonDataUser.dump(4); // format đẹp
        outFile.close();
        std::cout << "Dang ky thanh cong! Da luu vao file: " << filePath << "\n";
        return true;
    } else {
        std::cerr << "Khong the mo file de ghi JSON.\n";
        return false;
    }
}
