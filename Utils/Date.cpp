//
// Created by ChuKhanhhh on 13/10/24.
//
#include <iostream>
#include "Date.h"

// Khởi tạo giá trị cho mảng daysInMonth
int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


bool isValidateYear(const int year) {
    return year > 1;
}

bool isValidateMonth(const int month) {
    return 1 <= month && 12 >= month;
}

bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const int day, const int month, const int year) {
    if (!isValidateYear(year)) return false;
    if (!isValidateMonth(month)) return false;

    // Nếu là năm nhuận, tháng 2 có 29 ngày
    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    // Kiểm tra số ngày hợp lệ trong tháng
    return day >= 1 && day <= daysInMonth[month - 1];
}

void createDate(const char (&title)[MAX_SIZE], char (&date)[MAX_SIZE_DATE]) {
    std::cout << "Nhập " << title << ": ";
    int day, month, year;

    while (true) {
        // Nhập ngày, tháng, năm
        std::cout << "\nNhập ngày (dd): ";
        std::cin >> day;

        std::cout << "\nNhập tháng (mm): ";
        std::cin >> month;

        std::cout << "\nNhập năm (yyyy): ";
        std::cin >> year;

        // Kiểm tra tính hợp lệ của ngày tháng năm
        if (!isValidDate(day, month, year)) {
            std::cout << "Ngày không hợp lệ. Vui lòng nhập lại.\n";
        } else {
            // Định dạng ngày theo dd/mm/yyyy và lưu vào chuỗi 'date'
            // Sử dụng sprintf để định dạng ngày tháng năm thành chuỗi C truyền thống
            sprintf(date, "%02d/%02d/%04d", day, month, year);
            break;
        }
    }
}

bool isEndDateGreaterThanStartDate(const char startDate[MAX_SIZE_DATE], const char endDate[MAX_SIZE_DATE]) {
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;

    // Tách ngày tháng năm từ chuỗi
    extractDate(startDate, startDay, startMonth, startYear);
    extractDate(endDate, endDay, endMonth, endYear);

    // So sánh năm
    if (endYear > startYear) {
        return true;
    } else if (endYear == startYear) {
        // So sánh tháng nếu năm bằng nhau
        if (endMonth > startMonth) {
            return true;
        } else if (endMonth == startMonth) {
            // So sánh ngày nếu tháng bằng nhau
            return endDay > startDay;
        }
    }
    return false;  // Trả về false nếu endDate <= startDate
}

// Hàm tách ngày, tháng, năm từ chuỗi
void extractDate(const char date[MAX_SIZE_DATE], int &day, int &month, int &year) {
    // Tách ngày, tháng, năm từ startDate
    day = (date[0] - '0') * 10 + (date[1] - '0');
    month = (date[3] - '0') * 10 + (date[4] - '0');
    year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
                 (date[8] - '0') * 10 + (date[9] - '0');
}

void addDaysToDateManual(const char originalDate[MAX_SIZE_DATE], const int daysToAdd, char (&newDate)[MAX_SIZE_DATE]) {
    // Tách ngày, tháng, năm từ originalDate
    int day, month, year;
    extractDate(originalDate, day, month, year);

    // Cộng thêm số ngày
    day += daysToAdd;

    // Kiểm tra và điều chỉnh tháng/năm
    while (true) {
        // Số ngày trong tháng hiện tại
        const int daysInCurrentMonth = updateDay(month, year);

        // Nếu ngày vượt quá số ngày trong tháng
        if (day > daysInCurrentMonth) {
            day -= daysInCurrentMonth; // Giảm ngày
            month++; // Tăng tháng

            // Nếu tháng vượt quá 12, tăng năm
            if (month > 12) {
                month = 1; // Reset tháng về 1
                year++; // Tăng năm
            }
        } else {
            break; // Ngày hợp lệ
        }
    }

    // Chuyển đổi lại thành chuỗi ngày mới với định dạng dd/mm/yyyy
    sprintf(newDate, "%02d/%02d/%04d", day, month, year);
}

void addMonthsToDateManual(const char originalDate[MAX_SIZE_DATE], const int monthsToAdd, char (&newDate)[MAX_SIZE_DATE]) {
    // Tách ngày, tháng, năm từ originalDate
    int day, month, year;
    extractDate(originalDate, day, month, year);

    // Cộng thêm số tháng
    month += monthsToAdd;

    // Điều chỉnh tháng và năm
    while (month > 12) {
        month -= 12; // Giảm tháng
        year++;      // Tăng năm
    }

    // Kiểm tra và điều chỉnh ngày nếu tháng có ít ngày hơn ngày hiện tại
    const int daysInCurrentMonth = updateDay(month, year);

    // Nếu ngày vượt quá số ngày trong tháng
    if (day > daysInCurrentMonth) {
        day = daysInCurrentMonth; // Đặt ngày thành số ngày cuối cùng của tháng
    }

    // Chuyển đổi lại thành chuỗi ngày mới với định dạng dd/mm/yyyy
    sprintf(newDate, "%02d/%02d/%04d", day, month, year);
}

int daysFromDate(const int day, const int month,const int year) {
    int totalDays = 0;

    // Cộng số ngày của các năm trước
    for (int i = 1; i < year; ++i) {
        totalDays += (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) ? 366 : 365;
    }

    // Cộng số ngày của các tháng trong năm hiện tại
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int i = 1; i < month; ++i) {
        totalDays += daysInMonth[i];
    }

    // Nếu năm hiện tại là năm nhuận và tháng lớn hơn 2, cộng thêm 1
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && month > 2) {
        totalDays += 1;
    }

    // Cộng ngày hiện tại
    totalDays += day;

    return totalDays;
}

int calculateExcessDays(const char startDate[MAX_SIZE_DATE], const char endDate[MAX_SIZE_DATE]) {
    int startDay, startMonth, startYear;
    int endDay, endMonth, endYear;

    // Tách ngày tháng năm
    extractDate(startDate, startDay, startMonth, startYear);
    extractDate(endDate, endDay, endMonth, endYear);

    // Kiểm tra tính hợp lệ của ngày
    if (!isValidDate(startDay, startMonth, startYear) || !isValidDate(endDay, endMonth, endYear)) {
        std::cout << "Một trong hai ngày không hợp lệ." << std::endl;
        return -1; // Trả về -1 nếu ngày không hợp lệ
    }

    // Tính số ngày thừa
    const int excessDay = daysFromDate(endDay, endMonth, endYear) - daysFromDate(startDay, startMonth, startYear);
    return excessDay > 0 ? excessDay : excessDay * -1  ;
}

int updateDay(const int month,const int year) {
    int daysInCurrentMonth = 31; // Mặc định là 31 ngày
    if (month == 2) {
        // Tháng 2
        daysInCurrentMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28; // Năm nhuận
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInCurrentMonth = 30; // Các tháng có 30 ngày
    }
    return daysInCurrentMonth;
}

