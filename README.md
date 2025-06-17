## 🚀 Hướng dẫn sử dụng CMake với Visual Studio Code

Dự án này được viết bằng **C++** và sử dụng **CMake** làm hệ thống build. Bạn có thể biên dịch và chạy dễ dàng trong **Visual Studio Code**.

---

### 📦 Yêu cầu cài đặt

1. [Visual Studio Code](https://code.visualstudio.com/)
2. [CMake](https://cmake.org/download/)
3. Trình biên dịch C++:
   - **Windows:** MinGW hoặc Visual Studio Build Tools
   - **Linux/macOS:** g++ / clang
4. Các extension sau trong VS Code:
   - ✅ **CMake Tools** (`ms-vscode.cmake-tools`)
   - ✅ **C/C++** (`ms-vscode.cpptools`)

---

### 📁 Cấu trúc dự án


---

### ⚙️ Cài đặt và build với Visual Studio Code

#### 1. Mở thư mục dự án

- Mở VS Code
- Chọn `File` → `Open Folder...` → chọn thư mục chứa dự án (nơi có `CMakeLists.txt`)

#### 2. Chọn trình biên dịch (lần đầu tiên)

- Nhấn `Ctrl + Shift + P` → tìm `CMake: Select a Kit`
- Chọn `GCC` hoặc `MinGW` hoặc `Visual Studio` tùy hệ điều hành

#### 3. Cấu hình dự án

- Nhấn `Ctrl + Shift + P` → chọn `CMake: Configure`
- VS Code sẽ tạo thư mục `build` và file cấu hình bên trong

#### 4. Biên dịch chương trình

- Nhấn `Ctrl + Shift + P` → chọn `CMake: Build`
- Hoặc nhấn biểu tượng 🛠️ (build) ở thanh trạng thái dưới cùng

#### 5. Chạy chương trình

- Nhấn `Ctrl + Shift + P` → `CMake: Run Without Debugging`
- Hoặc nhấn nút ▶️ trên thanh trạng thái (nếu hiện)

---

### ❓ Khắc phục lỗi thường gặp

| Vấn đề                     | Giải pháp |
|---------------------------|-----------|
| Không thấy trình biên dịch | Cài đặt MinGW / MSVC và thêm vào PATH |
| CMake báo lỗi không tìm thấy nguồn | Kiểm tra lại file `CMakeLists.txt` và `main.cpp` |
| Không thấy nút Run         | Đảm bảo bạn đã chọn đúng `CMake Target` trong thanh trạng thái |

---

### 📘 Tài liệu tham khảo

- [CMake Documentation](https://cmake.org/documentation/)
- [CMake Tools Extension Guide](https://github.com/microsoft/vscode-cmake-tools)

---

🎉 **Giờ bạn đã sẵn sàng để build và chạy ứng dụng C++ với CMake trong VS Code rồi!**
