# 🎯 Reward Wallet Management System (C++)

Hệ thống quản lý tài khoản người dùng và ví điểm thưởng, được xây dựng bằng ngôn ngữ C++, hỗ trợ đầy đủ các chức năng: đăng ký, đăng nhập, phân quyền, chuyển điểm giữa ví, xác thực OTP và sao lưu dữ liệu.

---

## 🔧 Các chức năng chính

### ✅ 1. Tài khoản người dùng

* Đăng ký tài khoản mới (tự tạo hoặc quản lý tạo hộ).
* Kiểm tra trùng `username`, `phone number`.
* Hỗ trợ sinh mật khẩu tự động.
* Phân quyền: `User`, `Manager`, `SuperAdmin`.
* Lưu trữ định dạng JSON, tự động backup khi cập nhật.

### 🔐 2. Đăng nhập & bảo mật

* Xác thực bằng `username + password`.
* Mật khẩu được hash bằng SHA-256 (`hash.cpp`).
* Nếu là mật khẩu tự sinh → yêu cầu đổi sau khi đăng nhập.
* Hỗ trợ xác thực OTP (hiển thị console).

### 💼 3. Quản lý ví và giao dịch

* Mỗi người dùng có một `Wallet` duy nhất (id tự sinh).
* Giao dịch chuyển điểm từ ví A → B:

  * Kiểm tra số dư.
  * OTP xác thực giao dịch.
  * Cập nhật điểm đồng thời (atomic).
  * Ghi log giao dịch (transaction log).
* Người dùng có thể xem lịch sử giao dịch cá nhân.

### 🧑‍💼 4. Phân quyền

| Tính năng                  | Người dùng | Quản lý  |
| -------------------------- | ---------- | -------- |
| Tạo tài khoản              | ❌          | ✅        |
| Cập nhật tên, mật khẩu     | ✅          | ✅ (giúp) |
| Thống kê toàn hệ thống     | ❌          | ✅        |
| Chuyển điểm, xem giao dịch | ✅          | ✅        |

---

## 📁 Cấu trúc thư mục

```
project-root/
├── main.cpp
├── src/
│   ├── core/
│   │   ├── applogic/           # Hàm chạy chính
│   │   ├── auth/               # Đăng ký, đăng nhập
│   │   ├── menu/               # Menu người dùng & quản lý
│   │   ├── otp/                # Quản lý OTP
│   │   ├── transaction/        # Giao dịch
│   │   └── wallet/             # Chuyển điểm & ví
│   ├── data/                   # Load / seed dữ liệu
│   └── utils/                  # Factory, hash, file helper
├── entities/                  # Định nghĩa lớp User, Wallet, Transaction
├── include/                   # Khai báo hàm, logic kết nối
├── data/
│   ├── users/                 # Lưu user (JSON)
│   ├── wallets/               # Lưu ví (JSON)
│   └── transactions/          # Giao dịch
├── backup/                    # Tự động lưu file cũ khi cập nhật
└── libs/
    └── json.hpp               # Thư viện nlohmann/json
```

---

## ⚙️ Biên dịch & chạy chương trình

### Yêu cầu:

* Trình biên dịch hỗ trợ C++17 trở lên (`g++`, `clang++`).

### Lệnh biên dịch:

```bash
g++ -std=c++17 main.cpp \
    src/utils/*.cpp src/data/*.cpp \
    src/core/*/*.cpp \
    -o app
```

### Chạy chương trình:

```bash
./app
```

Sau khi chạy:

* Menu hiển thị: Đăng nhập, Đăng ký, Seed data.
* Sau đăng nhập: hiện menu tương ứng với quyền.
* Có xác thực OTP khi thay đổi thông tin và giao dịch.

---

## 🌱 Seed dữ liệu mẫu

Bạn có thể chọn mục `3. Insert seed data` trong menu đầu để khởi tạo sẵn người dùng:

* `admin` (Manager) – SĐT: `099`, Pass: `123`
* `daotung1` (User) – SĐT: `097`, Pass: `123`
* `daotung` (User) – SĐT: `098`, Pass: `123`

---

## 🧠 Điểm nổi bật kỹ thuật

* Mã hóa SHA-256 thủ công.
* OTP nội bộ có thời hạn.
* Hệ thống **sao lưu tự động** dữ liệu cũ.
* Quản lý giao dịch và ví nguyên tử.
* Lưu trữ file JSON phân loại rõ ràng.

---

## 📚 Tài liệu tham khảo

1. [nlohmann/json](https://github.com/nlohmann/json) – Thư viện JSON C++
2. [SHA-256 Algorithm](https://en.wikipedia.org/wiki/SHA-2) – Thuật toán băm
3. [OTP – One-time password](https://en.wikipedia.org/wiki/One-time_password)

---

**© 2025 – Đồ án C++ | Hệ thống Quản lý Người dùng & Ví Điểm**
