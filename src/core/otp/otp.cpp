#include "otp.h"
#include <random>
#include <ctime>

static std::unordered_map<std::string, std::pair<std::string, std::time_t>> otpStorage;

std::string random4Digits() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1000, 9999);
    return std::to_string(dis(gen));
}

namespace OtpManager {
    std::string generateOtp(const std::string& phone) {
        std::string otp = random4Digits();
        otpStorage[phone] = {otp, std::time(nullptr)};
        return otp;
    }

    bool verifyOtp(const std::string& phone, const std::string& otp) {
        auto it = otpStorage.find(phone);
        if (it == otpStorage.end()) return false;

        auto [storedOtp, timestamp] = it->second;
        if (std::time(nullptr) - timestamp > 300) return false; // 5 phút
        return storedOtp == otp;
    }
}
