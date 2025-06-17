cmake_minimum_required(VERSION 3.10)
project(RewardWalletApp)

# Include header folders
include_directories(
    include
    entities
)

# Tìm toàn bộ file .cpp trong src và các thư mục con
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Tạo executable
add_executable(reward_wallet ${SOURCES})
