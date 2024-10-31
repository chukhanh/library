//
// Created by ChuKhanhhh on 6/10/24.
//

#ifndef Reader_H
#define Reader_H
#include "../Common/Common.h"

// Xem danh sách độc giả trong thư viện
void getAllReader();

// Thêm độc giả
void addNewReader();

// Chỉnh sửa thông tin một độc giả
void editReader(const char (&readerCodeRequest)[MAX_SIZE], const char (&name)[MAX_SIZE],
                const char (&nationalId)[MAX_SIZE],
                const int (&birthYear), const char (&sex)[MAX_SIZE], const char (&email)[MAX_SIZE],
                const char (&address)[MAX_SIZE], const char (&cardCreateDate)[MAX_SIZE_DATE],
                const char (&cardEndDate)[MAX_SIZE_DATE]);


// Xoá thông tin một độc giả
void deleteReader(const char (&readerCode)[MAX_SIZE]);

//Tìm kiếm độc giả theo CMND
void findReaderByNationalId(const char (&nationalId)[MAX_SIZE]);

// Tìm kiếm sách theo họ tên
void findReaderByFullName(const char (&fullName)[MAX_SIZE]);

// Tìm kiếm độc giả theo mã độc giả
void findReaderByReaderCode(const char (&readerCode)[MAX_SIZE]);

// Hàm in thông tin của một độc giả
void printReader(int index);

// Kiếm index từ readerCode;
int findIndexReaderByCode(const char (&readerCode)[MAX_SIZE]);

// Thống kê số lượng độc giả
void numberOfReader();

int countOfReader();

// Thống kê số lượng độc giả theo giới tính
void numberOfReaderBySex();

// in Kết quả hết hạn thẻ của độc giả
void getReaderCardEndDateByIndex(int index, char (&readerCardEndDate)[MAX_SIZE_DATE]);

#endif //Reader_H
