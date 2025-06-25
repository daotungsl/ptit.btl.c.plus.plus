#include "otp.h"
#include "../include/factory.h"
#include <random>
#include <ctime>

static std::unordered_map<std::string, std::pair<std::string, std::time_t>> otpStorage;

std::string random4Digits() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1000, 9999);
    return std::to_string(dis(gen));
}

namespace OtpManager {

    bool confirmOtpForAction(const std::string& phone) {
        std::string otp = generateOtp(phone);
        print("OTP da duoc gui toi so: " + phone, true);
        print("OTP cua ban la: " + otp, true);

        std::string userOtp = input("Nhap ma OTP de xac nhan thao tac: ");
        if (!verifyOtp(phone, userOtp)) {
            print("OTP khong dung hoac het han.", true);
            return false;
        }
        return true;
    }

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
