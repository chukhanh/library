//
// Created by ChuKhanhhh on 19/10/24.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "../Common/Common.h"


// Tạo phiếu mượn sách
void createBorrowingSlip();

// In thông tin phiếu mượn sách
void printBorrowingSlip(int slipIndex);

// Hàm thống kê số sách đang được mượn
void countAllBorrowedBooks();

// Kiểm tra xem mã độc giả này đã có phiếu mượn chưa
int findSlipByReaderCode(const char (&readerCode)[MAX_SIZE]);

// Thống kê số sách đang được mượn
int countCurrentlyBorrowedBooks(int slipIndex);

// Số lượng phiếu mượn sách
int countAllBorrowingSlip();

// Tạo phiếu trả sách
void createReturnSlip();

// Xoá phiếu trả sách();
void deleteSlipByIndex(int slipIndex);

// Clear Phiếu mượn sách
void clearSlipData(int slipIndex);

// In kết quả của phiếu trả sách
void printReturnSlip(int slipIndex);

// Số lượng sách trong phiếu trả
int countCurrentlyReturnedBooks(int slipIndex);

// Thống kê danh sách độc giả bị trễ hạn
void listReadersWithLateReturns();

// Kiểm tra sách có tồn tại trong phiếu mượn không
bool isBookInBorrowingSlip(int borrowingSlipIndex, const char (&bookISBN)[MAX_SIZE]);

#endif //TRANSACTION_H
