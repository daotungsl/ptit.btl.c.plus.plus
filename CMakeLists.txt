cmake_minimum_required(VERSION 3.10)
project(RewardWalletApp)

# Dùng C++17 để dùng std::filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header folders
include_directories(
    include
    entities
)

# Tìm toàn bộ file .cpp trong src và các thư mục con
file(GLOB_RECURSE SOURCES src/*.cpp)

# Tạo executable
add_executable(reward_wallet ${SOURCES})

# (Chỉ cần nếu lỗi liên quan đến filesystem với GCC 8.x)
# target_link_libraries(reward_wallet stdc++fs)
