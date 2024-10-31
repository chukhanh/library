//
// Created by ChuKhanhhh on 13/10/24.
//

#ifndef DATE_H
#define DATE_H
#include "../Common/Common.h"

// Tạo mảng cho ngày
extern int daysInMonth[];

// Kiểm có phải năm nhuận không
bool isLeapYear(int year);

// Kiểm tra tính hợp lệ của ngày tháng năm
bool isValidDate(int day, int month, int year);

//Kiểm tra năm
bool isValidateYear(int year);

// Kiểm tra tháng
bool isValidateMonth(int month);

// Kiểm tra endDate có lớn hơn startDate không
bool isEndDateGreaterThanStartDate(const char startDate[MAX_SIZE_DATE], const char endDate[MAX_SIZE_DATE]);

// Hàm tách ngày, tháng, năm từ chuỗi
void extractDate(const char date[MAX_SIZE_DATE], int &day, int &month, int &year);

// Hàm cộng thêm số ngày vào ngày đã nhập
void addDaysToDateManual(const char originalDate[MAX_SIZE_DATE], int daysToAdd, char (&newDate)[MAX_SIZE_DATE]);

// Hàm cộng thêm số tháng vào ngày đã nhập
void addMonthsToDateManual(const char originalDate[MAX_SIZE_DATE], int monthsToAdd, char (&newDate)[MAX_SIZE_DATE]);

// Hàm tính số ngày từ ngày nhập vào
int daysFromDate(int day, int month, int year);

// Hàm tính số ngày thừa giữa hai ngày
int calculateExcessDays(const char startDate[MAX_SIZE_DATE], const char endDate[MAX_SIZE_DATE]);

// cập nhật ngày
int updateDay(int month, int year);

#endif //DATE_H
