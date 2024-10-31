//
// Created by ChuKhanhhh on 6/10/24.
//
#include "Reader.h"
#include <iostream>

#include "../Utils/Date.h"

// Mảng lưu trữ các thông tin của độc giả
char readerCodes[MAX_SIZE][MAX_SIZE]; // Mã độc giả
char readerNames[MAX_SIZE][MAX_SIZE]; // Họ tên
char readerNationalIds[MAX_SIZE][MAX_SIZE]; // CMND
int readerBirthYears[MAX_SIZE]; // Năm sinh
char readerSexes[MAX_SIZE][MAX_SIZE]; // Giới tính
char readerEmails[MAX_SIZE][MAX_SIZE]; // Email
char readerAddresses[MAX_SIZE][MAX_SIZE]; // Địa chỉ
char readerCardCreateDates[MAX_SIZE][MAX_SIZE_DATE]; // Ngày lập thẻ
char readerCardEndDates[MAX_SIZE][MAX_SIZE_DATE]; // Ngày hết hạn thẻ (48 tháng kể từ ngày lập thẻ)
int readerIndex = 0;

void printReader(const int index) {
    if (isBlank(readerCodes[index])) {
        return; // The character is blank
    }
    printf("\nThông tin độc giả thứ [%d] trong hệ thống là: ", index);
    std::cout << "\nMã độc giả: " << readerCodes[index] << std::endl;
    std::cout << "\nHọ tên: " << readerNames[index] << std::endl;
    std::cout << "\nCMND: " << readerNationalIds[index] << std::endl;
    std::cout << "\nNăm sinh: " << readerBirthYears[index] << std::endl;
    std::cout << "\nGiới tính: " << readerSexes[index]
            << " (" << (readerSexes[index][0] == MALE ? "Nam" : "Nữ")
            << " )" << std::endl;
    std::cout << "\nĐịa chỉ: " << readerAddresses[index] << std::endl;
    std::cout << "\nNgày lập thẻ: " << readerCardCreateDates[index] << std::endl;
    std::cout << "\nNgày hết hạn thẻ: " << readerCardEndDates[index] << std::endl;
}

void addNewReader() {
    // Tối đã số lượng đọc giả chỉ có 100 , nếu số lượng lớn hơn 100 reader in ra kết quả
    if (MAX_SIZE == readerIndex) {
        printf("Đã đạt giới hạn %d số lượng độc giả. ", MAX_SIZE);
        return;
    }

    // Tạo field để người dùng nhập vào
    char readerCode[MAX_SIZE];
    char readerNameRequest[MAX_SIZE];
    char readerNationalIdRequest[MAX_SIZE];
    int readerYearBirthdayRequest;
    char readerSexRequest[MAX_SIZE];
    char readerEmailRequest[MAX_SIZE];
    char readerAddressRequest[MAX_SIZE];
    char readerCardCreateTimeRequest[MAX_SIZE_DATE];
    char readerCardEndTimeRequest[MAX_SIZE_DATE];
    // Người dùng nhập mã độc giả
    createValue(READER_CODE, readerCode);

    // Kiểm tra nếu readerCode được nhập vào tồn tại và hợp lệ trong hệ thống
    const int index = findIndexReaderByCode(readerCode);

    if (isBlank(readerCode)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại mã độc giả. Mã không được để trống." << std::endl;
        return;
    }

    // Kiểm tra nếu readerCode được nhập vào tồn tại trong hệ thống, in ra kết quả
    if (INVALID_DATA != index) {
        std::cout << "\nĐã tồn tại độc giả ( " << readerCode << " ) trong hệ thống";
        return;
    }


    // Người dùng nhập Họ và Tên của độc giả
    createValue(READER_NAME, readerNameRequest);

    if (isBlank(readerCode)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại tên độc giả. Tên không được để trống." << std::endl;
        return;
    }
    // Người dùng nhập CMND của độc giả
    createValue(READER_NATIONALID, readerNationalIdRequest);

    if (!isValidNationId(readerNationalIdRequest)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại CMND độc giả. Bắt buộc nhập 9 kí tự và toàn là số" << std::endl;
        return;
    }
    // Người dùng nhập Năm Sinh của độc giả
    createValue(READER_YEAR_BIRTHDAY, readerYearBirthdayRequest);

    // Kiểm tra nếu readerCode được nhập vào tồn tại và hợp lệ trong hệ thống
    if (!isValidateYear(readerYearBirthdayRequest)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại năm sinh độc giả. Bị sai format. Bắt buộc nhập YYYY" << std::endl;
        return;
    }

    // Người dùng nhập giới tính của độc giả
    createValue(READER_SEX, readerSexRequest);

    if (!isValidateSex(readerSexRequest)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại giới tính độc giả. Nếu là Nam nhập M, nếu là Nữ Nhập F." << std::endl;
        return;
    }

    // Người dùng nhập email của độc giả
    createValue(READER_EMAIL, readerEmailRequest);

    if (!isValidateEmail(readerEmailRequest)) {
        std::cout << "\nBắt buộc phải nhập lại email của độc giả. Bị sai format. Ví dụ: a@gmail.com" << std::endl;
        return;
    }
    // Người dùng nhập địa chỉ của độc giả
    createValue(READER_ADDRESS, readerAddressRequest);
    // Người dùng nhập ngày lập thẻ của độc giả
    createDate(READER_CARD_CREATE_TIME, readerCardCreateTimeRequest);

    char next48Month[MAX_SIZE_DATE];
    addMonthsToDateManual(readerCardCreateTimeRequest, 48, next48Month);

    // Người dùng nhập ngày hết hạn độc giả
    printf("%s .Ngày hết hạn thẻ phải lớn hơn %s\n", READER_CARD_END_TIME, next48Month);
    createDate(READER_CARD_END_TIME, readerCardEndTimeRequest);

    if (!isEndDateGreaterThanStartDate(readerCardCreateTimeRequest, readerCardEndTimeRequest)) {
        printf("Ngày hết hạn thẻ %s phải lớn hơn ngày mượn thẻ %s.\n", readerCardEndTimeRequest, readerCardCreateTimeRequest);
        return;
    }


    if (!isEndDateGreaterThanStartDate(next48Month, readerCardEndTimeRequest)) {
        printf("Ngày hết hạn thẻ %s phải từ 48 tháng kể từ ngày lập thẻ %s. Ngày hết hạn thẻ phải lớn hơn %s \n", readerCardEndTimeRequest, readerCardCreateTimeRequest, next48Month);
        return;
    }

    // Gán mã độc giả vào mảng readerCodes tại vị trí readerIndex để lưu trữ riêng các mã độc giả
    strcpy(readerCodes[readerIndex], readerCode);
    // Gán tên độc giả (readerName) vào mảng readerNames tại vị trí readerIndex
    strcpy(readerNames[readerIndex], readerNameRequest);
    // Gán CMND (readerNationalId) vào mảng readerNationalIds tại vị trí readerIndex
    strcpy(readerNationalIds[readerIndex], readerNationalIdRequest);
    // Gán năm sinh (readerYearBirthday) vào mảng readerBirthYears tại vị trí readerIndex
    readerBirthYears[readerIndex] = readerYearBirthdayRequest;
    // Gán giới tính (readerSex) vào mảng readerSexes tại vị trí readerIndex
    strcpy(readerSexes[readerIndex], readerSexRequest);
    // Gán địa chỉ (readerAddress) vào mảng readerAddresses tại vị trí readerIndex
    strcpy(readerAddresses[readerIndex], readerAddressRequest);
    // Gán ngày lập thẻ (readerCardCreateTime) vào mảng readerCardCreateDates tại vị trí readerIndex
    strcpy(readerCardCreateDates[readerIndex], readerCardCreateTimeRequest);
    // Gán ngày hết hạn thẻ (readerCardEndTime) vào mảng readerCardEndDates tại vị trí readerIndex
    strcpy(readerCardEndDates[readerIndex], readerCardEndTimeRequest);
    // Gán ngày hết hạn thẻ (readerEmail) vào mảng readerEmails tại vị trí readerIndex
    strcpy(readerEmails[readerIndex], readerEmailRequest);
    // In ra kết quả của reader vừa nhập
    printReader(readerIndex);

    // Tăng biến đếm độc giả (readerIndex) lên 1 để chuẩn bị cho lần nhập tiếp theo
    readerIndex++;
}

void findReaderByReaderCode(const char (&readerCode)[MAX_SIZE]) {
    if (0 == readerIndex) {
        printf("Không tìm thấy độc giả (%s) trong hệ thống ", readerCode);
        return;
    }

    const int index = findIndexReaderByCode(readerCode);
    if (INVALID_DATA == index) {
        printf("Không tồn tại độc giả (%s) trong hệ thống ", readerCode);
        return;
    }

    printf("Thông tin độc giả thứ [%d] trong hệ thống là: ", index);
    printReader(index);
}

void getAllReader() {
    if (isBlank(readerCodes[0])) {
        printf("\nHiện tại không có tồn tại độc giả nào trong hệ thống\n");
    } else {
        for (int i = 0; i < MAX_SIZE; i++) {
            printReader(i);
        }
    }
}

int findIndexReaderByCode(const char (&readerCode)[MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(readerCode, readerCodes[i]) == 0) {
            // Compare content of strings
            return i;
        }
    }
    return -1;
}


void editReader(const char (&readerCodeRequest)[MAX_SIZE], const char (&name)[MAX_SIZE],
                const char (&nationalId)[MAX_SIZE],
                const int (&birthYear), const char (&sex)[MAX_SIZE], const char (&email)[MAX_SIZE],
                const char (&address)[MAX_SIZE], const char (&cardCreateDate)[MAX_SIZE_DATE],
                const char (&cardEndDate)[MAX_SIZE_DATE]) {
    // Kiểm tra nếu readerCode được nhập vào tồn tại trong hệ thống, in ra kết quả
    const int index = findIndexReaderByCode(readerCodeRequest);
    if (INVALID_DATA == index) {
        printf("Không tồn tại độc giả (%s) trong hệ thống ", readerCodeRequest);
        return;
    }

    int startDay, startMonth, startYear;
    extractDate(cardCreateDate, startDay, startMonth, startYear);
    if (!isValidDate(startDay, startMonth, startYear)) {
        std::cout << "Ngày bắt đầu không hợp lệ. Vui lòng nhập lại.\n";
        return;
    }

    int endDay, endMonth, endYear;
    extractDate(cardEndDate, endDay, endMonth, endYear);
    if (!isValidDate(endDay, endMonth, endYear)) {
        std::cout << "Ngày hết hạn thẻ không hợp lệ. Vui lòng nhập lại.\n";
        return;
    }

    if (!isEndDateGreaterThanStartDate(cardCreateDate, cardEndDate)) {
        std::cout << "Ngày kết thúc không lớn hơn ngày bắt đầu. Vui lòng nhập lại ngày hết hạn thẻ \n";
        return;
    }

    if (!isValidateEmail(email)) {
        std::cout << "\nEmail bị sai format. Ví dụ: a@gmail.com" << std::endl;
        return;
    }

    if (!isValidNationId(nationalId)) {
        std::cout << "\nCMND Bắt buộc nhập 9 kí tự" << std::endl;
        return;
    }

    if (!isValidateYear(birthYear)) {
        std::cout << "\nBắt buộc phải nhập lại năm sinh độc giả. Bị sai format. Bắt buộc nhập YYYY" << std::endl;
        return;
    }

    // Gán tên độc giả (readerName) vào mảng readerNames tại vị trí readerIndex
    strcpy(readerNames[index], name);
    // Gán CMND (readerNationalId) vào mảng readerNationalIds tại vị trí readerIndex
    strcpy(readerNationalIds[index], nationalId);
    // Gán năm sinh (readerYearBirthday) vào mảng readerBirthYears tại vị trí readerIndex
    readerBirthYears[index] = birthYear;
    // Gán giới tính (readerSex) vào mảng readerSexes tại vị trí readerIndex
    strcpy(readerSexes[index], sex);
    // Gán địa chỉ (readerAddress) vào mảng readerAddresses tại vị trí readerIndex
    strcpy(readerAddresses[index], address);
    // Gán ngày lập thẻ (readerCardCreateTime) vào mảng readerCardCreateDates tại vị trí readerIndex
    strcpy(readerCardCreateDates[index], cardCreateDate);
    // Gán ngày hết hạn thẻ (readerCardEndTime) vào mảng readerCardEndDates tại vị trí readerIndex
    strcpy(readerCardEndDates[index], cardEndDate);
    // Gán ngày hết hạn thẻ (readerEmail) vào mảng readerEmails tại vị trí readerIndex
    strcpy(readerEmails[index], email);

    std::cout << "Sửa thông tin Độc giả thành công!" << std::endl;
}

void deleteReader(const char (&readerCode)[MAX_SIZE]) {
    // Check if the readerCode exists in the system and get the index
    const int index = findIndexReaderByCode(readerCode);
    if (INVALID_DATA == index) {
        std::cout << "Không tồn tại độc giả (" << readerCode << ") trong hệ thống." << std::endl;
        return;
    }

    // Shift all elements after the index up one position
    for (int i = index; i < readerIndex - 1; i++) {
        strcpy(readerCodes[i], readerCodes[i + 1]);
        strcpy(readerNames[i], readerNames[i + 1]);
        strcpy(readerNationalIds[i], readerNationalIds[i + 1]);
        readerBirthYears[i] = readerBirthYears[i + 1];
        strcpy(readerSexes[i], readerSexes[i + 1]);
        strcpy(readerAddresses[i], readerAddresses[i + 1]);
        strcpy(readerCardCreateDates[i], readerCardCreateDates[i + 1]);
        strcpy(readerCardEndDates[i], readerCardEndDates[i + 1]);
    }

    // Decrease the readerIndex after deletion
    readerIndex--;

    // Clear the last entry after shifting
    strcpy(readerCodes[readerIndex], "");
    strcpy(readerNames[readerIndex], "");
    strcpy(readerNationalIds[readerIndex], "");
    strcpy(readerSexes[readerIndex], "");
    strcpy(readerAddresses[readerIndex], "");
    strcpy(readerCardCreateDates[readerIndex], "");
    strcpy(readerCardEndDates[readerIndex], "");

    std::cout << "Độc giả đã được xóa thành công!" << std::endl;
}

// Hàm tìm kiếm độc giả theo CMND
void findReaderByNationalId(const char (&nationalId)[MAX_SIZE]) {
    bool isFind = false; // Biến kiểm tra xem đã tìm thấy độc giả hay chưa

    // Duyệt qua tất cả các chỉ số trong mảng readerNationalIds
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(readerNationalIds[i], nationalId) == 0) {
            // So sánh CMND
            printReader(i); // In thông tin độc giả
            isFind = true; // Đánh dấu là đã tìm thấy
        }
    }

    // In thông báo nếu không tìm thấy độc giả
    if (!isFind) {
        std::cout << "Không tồn tại độc giả có CMND (" << nationalId << ") trong hệ thống." << std::endl;
    }
}

// Hàm tìm kiếm độc giả theo CMND
void findReaderByFullName(const char (&fullName)[MAX_SIZE]) {
    bool isFind = false; // Biến kiểm tra xem đã tìm thấy độc giả hay chưa

    // Duyệt qua tất cả các chỉ số trong mảng readerNationalIds
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(readerNames[i], fullName) == 0) {
            // So sánh CMND
            printReader(i); // In thông tin độc giả
            isFind = true; // Đánh dấu là đã tìm thấy
        }
    }

    // In thông báo nếu không tìm thấy độc giả
    if (!isFind) {
        std::cout << "Không tồn tại độc giả có tên (" << fullName << ") trong hệ thống." << std::endl;
    }
}

void numberOfReader() {
    int count = 0;
    for (const auto &readerCode: readerCodes) {
        if (!isBlank(readerCode)) {
            count++;
        }
    }

    if (0 == count) {
        printf("Không tồn tại độc giả trong hệ thống \n");
    } else {
        std::cout << "Số lượng độc giả trong hệ thống : " << count << "\n" << std::endl;
    }
}

int countOfReader() {
    int count = 0;
    for (const auto &readerCode: readerCodes) {
        if (!isBlank(readerCode)) {
            count++;
        }
    }

    return count;
}

void numberOfReaderBySex() {
    int maleCount = 0;
    int femaleCount = 0;

    // Duyệt qua mảng readerSexes để đếm số lượng nam và nữ
    for (auto &readerSexe: readerSexes) {
        if (isBlank(readerSexe)) {
            continue;
        } else {
            if (readerSexe[0] == MALE) {
                maleCount++;
            } else if (readerSexe[0] == FEMALE) {
                femaleCount++;
            }
        }
    }

    // In ra kết quả thống kê
    std::cout << "Số lượng độc giả Nam: " << maleCount << "\n" << std::endl;
    std::cout << "Số lượng độc giả Nữ: " << femaleCount << "\n" << std::endl;
}

void getReaderCardEndDateByIndex(const int index, char (&readerCardEndDate)[MAX_SIZE_DATE]) {
    // Ensure index is within bounds
    if (index < 0 || index >= MAX_SIZE) {
        std::cout << "Index out of bounds." << std::endl;
        return; // Return if the index is invalid
    }

    // Copy the end date to the provided buffer
    strcpy(readerCardEndDate, readerCardEndDates[index]);
}

void isExistedReadCode(const char (&readerCode)[MAX_SIZE]) {
    const int index = findIndexReaderByCode(readerCode);
    if (INVALID_DATA == index) {
        std::cout << "Không tồn tại độc giả (" << readerCode << ") trong hệ thống." << std::endl;
    }
}
