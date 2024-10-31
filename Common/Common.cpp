#include <iostream>
#include "Common.h"
#include <cctype>

// Hàm tạo giá trị và in ra tiêu đề
void createValue(const char (&title)[MAX_SIZE], char (&value)[MAX_SIZE]) {
    std::cout << "\n" << std::endl;
    // In ra tiêu đề là một ký tự duy nhất
    std::cout << "Nhập " << title << ": ";

    // Đọc một ký tự từ người dùng và lưu vào value
    // Sử dụng cin để đọc chuỗi ký tự từ người dùng và lưu vào value
    std::cin.getline(value, MAX_SIZE); // Giả sử kích thước mảng value là 265 ký tự
}

// Function to create and print a value of type double
void createValue(const char (&title)[MAX_SIZE], double &value) {
    std::cout << "\n" << std::endl;

    while (true) {
        std::cout << "Nhập " << title << ": ";
        std::cin >> value;

        // Kiểm tra nếu nhập vào không phải là số thực (double)
        if (std::cin.fail()) {
            std::cin.clear(); // Xóa trạng thái lỗi của cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua tất cả các ký tự không hợp lệ
            std::cout << "Giá trị nhập vào không hợp lệ. Vui lòng nhập một số thực.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Loại bỏ các ký tự thừa trong dòng
            break; // Thoát vòng lặp nếu nhập đúng
        }
    }
}

// Function to create and print a value of type int
void createValue(const char (&title)[MAX_SIZE], int &value) {
    std::cout << "\n" << std::endl;

    while (true) {
        std::cout << "Nhập " << title << ": ";
        std::cin >> value;

        // Kiểm tra nếu nhập vào không phải là số nguyên
        if (std::cin.fail()) {
            std::cin.clear(); // Xóa trạng thái lỗi của cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua tất cả các ký tự đã nhập vào
            std::cout << "Giá trị nhập vào không hợp lệ. Vui lòng nhập một số nguyên.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Loại bỏ ký tự thừa trong dòng
            break; // Thoát vòng lặp nếu nhập đúng
        }
    }
}

bool isBlank(const char (&str)[MAX_SIZE]) {
    // Check if the string is empty
    if (nullptr == str || '\0' == str[0]) {
        return true; // Consider empty string as blank
    }

    // Check each character in the array
    for (int i = 0; i < strlen(str); ++i) {
        if (BLANK_DATA != str[i]) {
            return false; // Found a non-blank character
        }
    }
    return true; // All characters are blank
}

bool isValidateEmail(const char (&email)[MAX_SIZE]) {
    const int length = strlen(email);

    // Kiểm tra độ dài email
    if (length == 0 || length >= MAX_SIZE) {
        return false; // Email không hợp lệ nếu rỗng hoặc quá dài
    }

    // Kiểm tra vị trí ký tự '@'
    int atPos = INVALID_DATA;
    for (int i = 0; i < length; ++i) {
        if (SPECIAL_CHAR == email[i]) {
            if (INVALID_DATA != atPos) {
                return false; // Chỉ được phép một ký tự '@'
            }
            atPos = i;
        }
    }

    // Kiểm tra xem ký tự '@' có tồn tại không
    if (INVALID_DATA == atPos || 0 == atPos || atPos == length - 1) {
        return false; // '@' phải có và không được ở đầu hoặc cuối
    }

    // Kiểm tra phần tên miền
    bool dotFound = false;
    for (int i = atPos + 1; i < length; ++i) {
        if (DOT_CHAR == email[i]) {
            dotFound = true;
        }
    }

    // Kiểm tra xem có ký tự '.' trong phần tên miền không
    if (!dotFound) {
        return false; // Phải có ký tự '.' trong tên miền
    }

    // Kiểm tra rằng không có ký tự đặc biệt nào khác ngoài '@' và '.'
    for (int i = 0; i < length; ++i) {
        if (!(isalnum(email[i]) || SPECIAL_CHAR == email[i] || DOT_CHAR == email[i] || email[i] == '-' || email[i] ==
              '_')) {
            return false; // Email không hợp lệ nếu có ký tự đặc biệt
        }
    }

    return true; // Email hợp lệ
}

bool isValidateSex(const char (&sex)[MAX_SIZE]) {
    // Kiểm tra độ dài chuỗi
    const int length = strlen(sex);

    // Nếu độ dài bằng 0 hoặc lớn hơn kích thước tối đa, không hợp lệ
    if (length == 0 || length >= MAX_SIZE) {
        return false;
    }

    // Kiểm tra giá trị "Nam" hoặc nữ
    return FEMALE == sex[0] || MALE == sex[0];
}

bool isValidNationId(const char (&nationId)[MAX_SIZE]) {
    // Kiểm tra độ dài có phải là 9 không
    if (strlen(nationId) != 9) {
        return false;
    }

    // Kiểm tra từng ký tự trong chuỗi xem có phải là chữ số hay không
    for (int i = 0; i < 9; ++i) {
        if (!isdigit(nationId[i])) {
            return false; // Nếu có ký tự nào không phải là số, trả về false
        }
    }

    // Nếu tất cả đều là số và độ dài là 9, trả về true
    return true;
}