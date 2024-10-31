//
// Created by ChuKhanhhh on 7/10/24.
//

#ifndef BOOK_H
#define BOOK_H
#include "../Common/Common.h"

// Xem danh sách các sách trong thư viện
void getAllBook();

// Thêm sách
void addNewBook();

// Chỉnh sửa thông tin một quyển sách
void editBook(const char (&bookISBN)[MAX_SIZE], const char (&bookName)[MAX_SIZE],
              const char (&bookAuthor)[MAX_SIZE], const char (&bookPublisherEdition)[MAX_SIZE],
              const int (&bookYearOfPublication), const char (&bookCategory)[MAX_SIZE],
              const double &bookPrice, const int &bookNumber);

void editBook(const char (&bookISBN)[MAX_SIZE], const int &bookNumber);

// Xóa thông tin sách
void deleteBook(const char (&bookISBN)[MAX_SIZE]);

// Tìm kiếm sách theo ISBN
void findBookByISBN(const char (&bookISBN)[MAX_SIZE]);

// Tìm kiếm sách theo tên sách
void findBookByName(const char (&bookName)[MAX_SIZE]);

// Kiếm index từ readerCode
int findIndexBookByISBN(const char (&bookISBN)[MAX_SIZE]);

// Hàm in thông tin của sách
void printBook(int index);

// Hàm in Thống kê số lượng sách trong thư viện
void numberOfBook();

int countBook();

// Hàm in Thống kê số lượng sách dựa theo mã sách
int numberOfBook(const char (&bookISBN)[MAX_SIZE]);

// thống kê số lượng sách theo thể loại
void countBooksByCategory();

// In ra giá tiền của sách
double printBookPriceByIndex(int index);

// xoá sách trong phiếu mượn
void removeBookFromBorrowingSlip(int slipIndex, const char (&bookISBN)[MAX_SIZE]);

#endif //BOOK_H
