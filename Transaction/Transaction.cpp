//
// Created by ChuKhanhhh on 19/10/24.
//

#include "Transaction.h"
#include <iostream>

#include "../Book/Book.h"
#include "../Common/Common.h"
#include "../Reader/Reader.h"
#include "../Utils/Date.h"

char borrowingReaderCodes[MAX_SIZE][MAX_SIZE]; // Mã độc giả
char borrowingBookISBNs[MAX_SIZE][MAX_SIZE][MAX_SIZE]; // Mã quyển sách
char borrowingDates[MAX_SIZE][MAX_SIZE_DATE]; // Ngày mượn sách
char borrowingDueDates[MAX_SIZE][MAX_SIZE_DATE]; // Ngày trả sách dự kiến

char returnSlipReaderCodes[MAX_SIZE][MAX_SIZE]; // Mã độc giả
char returnSlipBookISBNs[MAX_SIZE][MAX_SIZE][MAX_SIZE]; // Mã quyển sách
int returnSlipBookStatus[MAX_SIZE][MAX_SIZE]; // Tình trạng sách
char returnSlipDueDates[MAX_SIZE][MAX_SIZE_DATE]; // Ngày trả sách
double returnSlipLateFee[MAX_SIZE]; // Phí phạt quá hạn
double returnSlipLateBookPenalty[MAX_SIZE]; // Phí phạt mất sách

char returnSlipReaderCodesLate[MAX_SIZE][MAX_SIZE]; // Mã độc giả trả quá hạn

int borrowSlipIndex = 0; // index cho phiếu mua sách
int returnSlipIndex = 0; // index cho phiếu trả sách
int latelyIndex = 0; // index cho phiếu trả sách

void createBorrowingSlip() {
    const int numberOfReaderInSystem = countOfReader();

    if (0 == numberOfReaderInSystem) {
        printf("\nHiện tại không có tồn tại độc giả nào trong hệ thống\n");
        return;
    }

    const int numberOfBookInSystem = countBook();

    if (0 == numberOfBookInSystem) {
        printf("\nHiện tại không có tồn tại quyển sách nào trong hệ thống\n");
        return;
    }

    char transactionSlipReaderCode[MAX_SIZE]; // Mã độc giả
    int numberOfBooksBorrow; // Số sách mượn

    // Người dùng nhập mã độc giả
    createValue(TRANSACTION_SLIP_READER_CODE, transactionSlipReaderCode);
    const int indexReader = findIndexReaderByCode(transactionSlipReaderCode);
    // Kiểm tra xem mã độc giả có tồn tại trong hệ thống không
    if (INVALID_DATA == findIndexReaderByCode(transactionSlipReaderCode)) {
        printf("Không tồn tại thông tin mã độc giả (%s) trong hệ thống ", transactionSlipReaderCode);
        return; // Kết thúc hàm nếu mã độc giả không hợp lệ
    }

    const int existingSlipIndex = findSlipByReaderCode(transactionSlipReaderCode);
    if (INVALID_DATA != existingSlipIndex) {
        char borrowingBookISBNTemps[MAX_SIZE][MAX_SIZE]; // Mảng tạm lưu mã ISBN
        // Độc giả đã có phiếu mượn, gộp phiếu mượn cũ với sách mới
        printf("Độc giả %s đã có phiếu mượn, sẽ gộp phiếu mới.\n", transactionSlipReaderCode);

        // Nhập số lượng sách mượn mới
        createValue(CHOOSE_NUMBER_BORROW_BOOK_NUMBER, numberOfBooksBorrow);

        // Kiểm tra xem số lượng sách mượn có vượt quá số sách còn lại có thể mượn không
        const int currentBooksOnSlip = countCurrentlyBorrowedBooks(existingSlipIndex); // Số sách đã mượn trong phiếu cũ
        if (currentBooksOnSlip + numberOfBooksBorrow > MAX_SIZE) {
            std::cout << "Không thể mượn quá " << numberOfBookInSystem << " sách trong một phiếu.\n";
            return; // Kết thúc hàm nếu số lượng sách mượn vượt quá giới hạn
        }
        // Gộp thêm sách vào phiếu mượn cũ
        for (int i = currentBooksOnSlip; i < currentBooksOnSlip + numberOfBooksBorrow; ++i) {
            char transactionSlipBookISBN[MAX_SIZE];
            // Người dùng nhập mã ISBN của sách
            createValue(TRANSACTION_SLIP_BOOK_ISBN, transactionSlipBookISBN);

            // Kiểm tra mã ISBN của sách có tồn tại trong hệ thống không
            if (INVALID_DATA == findIndexBookByISBN(transactionSlipBookISBN)) {
                printf("Không tồn tại thông tin quyển sách (%s) trong hệ thống ", transactionSlipBookISBN);
                return; // Kết thúc hàm nếu mã sách không hợp lệ
            }

            const int currentNumberOfBook = numberOfBook(transactionSlipBookISBN); // Số sách hiện có
            // Kiểm tra nếu số sách hiện có là 0
            if (0 == currentNumberOfBook) {
                printf("\nSố lượng quyển sách (%s) trong hệ thống đã hết. Độc giả không thể mượn được ",
                       transactionSlipBookISBN);
                return; // Kết thúc hàm nếu không còn sách
            }

            // Lưu mã ISBN vào mảng tạm thời
            strcpy(borrowingBookISBNTemps[i], transactionSlipBookISBN);
        }

        // Lưu các ISBN sách từ mảng tạm thời vào mảng BorrowingBookISBNs của phiếu mượn cũ
        for (int i = 0; i < numberOfBooksBorrow; ++i) {
            if (isBlank(borrowingBookISBNTemps[i])) break;
            strcpy(borrowingBookISBNs[existingSlipIndex][currentBooksOnSlip + i], borrowingBookISBNTemps[i]);
            // Giảm số lượng sách trong kho
            editBook(borrowingBookISBNTemps[i], numberOfBook(borrowingBookISBNTemps[i]) - 1);
        }

        printBorrowingSlip(borrowSlipIndex);
    } else {
        char transactionSlipBorrowDate[MAX_SIZE_DATE]; // Ngày mượn sách
        char transactionSlipDueDate[MAX_SIZE_DATE]; // Ngày trả dự kiến
        char newDate[MAX_SIZE_DATE]; // Ngày mới để kiểm tra
        char readerCardEndDate[MAX_SIZE_DATE]; // Ngày mới để kiểm tra
        char borrowingBookISBNTemps[MAX_SIZE][MAX_SIZE]; // Mảng tạm lưu mã ISBN
        // Nhập số lượng sách mượn
        createValue(CHOOSE_NUMBER_BORROW_BOOK_NUMBER, numberOfBooksBorrow);
        const int currentNumberOfBooks = countBook(); // Số sách có thể mượn

        // Kiểm tra xem số lượng sách mượn có vượt quá số sách có thể mượn không
        if (numberOfBooksBorrow > currentNumberOfBooks) {
            std::cout << "Không thể mượn quá " << currentNumberOfBooks << " sách trong một lần.\n";
            return; // Kết thúc hàm nếu số lượng sách mượn không hợp lệ
        }

        // Nhập và lưu mã ISBN của các sách được mượn
        for (int i = 0; i < numberOfBooksBorrow; ++i) {
            char transactionSlipBookISBN[MAX_SIZE];
            // Tạo tiêu đề cho sách mượn
            std::cout << TRANSACTION_SLIP_BOOK_ISBN << " thứ " << (i + 1) << ":";
            createValue(TRANSACTION_SLIP_BOOK_ISBN, transactionSlipBookISBN);

            // Kiểm tra mã ISBN của sách có tồn tại trong hệ thống không
            if (INVALID_DATA == findIndexBookByISBN(transactionSlipBookISBN)) {
                printf("Không tồn tại thông tin quyển sách (%s) trong hệ thống ", transactionSlipBookISBN);
                return; // Kết thúc hàm nếu mã sách không hợp lệ
            }

            const int currentNumberOfBook = numberOfBook(transactionSlipBookISBN); // Số sách hiện có
            // Kiểm tra nếu số sách hiện có là 0
            if (0 == currentNumberOfBook) {
                printf("\nSố lượng quyển sách (%s) trong hệ thống đã hết. Độc giả không thể mượn được ",
                       transactionSlipBookISBN);
                return; // Kết thúc hàm nếu không còn sách
            }

            // Lưu mã ISBN vào mảng BorrowingBookISBN
            strcpy(borrowingBookISBNTemps[i], transactionSlipBookISBN);
        }

        // Người dùng nhập ngày mượn
        createDate(TRANSACTION_SLIP_BORROW_DATE, transactionSlipBorrowDate);

        getReaderCardEndDateByIndex(indexReader, readerCardEndDate);

        // Kiểm tra xem ngày hết hạn thẻ có lớn hơn ngày mượn không
        if (!isEndDateGreaterThanStartDate(transactionSlipBorrowDate, readerCardEndDate)) {
            printf("Ngày hết hạn thẻ của độc giả (%s) bé hơn ngày mượn (%s)\n", transactionSlipBorrowDate,
                   transactionSlipBorrowDate);
            return; // Kết thúc hàm nếu ngày trả không hợp lệ
        }

        // Người dùng nhập ngày trả dự kiến
        createDate(TRANSACTION_SLIP_DUE_DATE, transactionSlipDueDate);

        // Kiểm tra xem ngày trả có lớn hơn ngày mượn không
        if (!isEndDateGreaterThanStartDate(transactionSlipBorrowDate, transactionSlipDueDate)) {
            printf("Ngày trả dự kiến (%s) phải lớn hơn ngày mượn. (%s)\n", transactionSlipDueDate,
                   transactionSlipBorrowDate);
            return; // Kết thúc hàm nếu ngày trả không hợp lệ
        }

        // Tính toán ngày trả sách tối đa (7 ngày sau ngày mượn)
        addDaysToDateManual(transactionSlipBorrowDate, 7, newDate);

        // Kiểm tra số ngày mượn có vượt quá 7 ngày không
        if (isEndDateGreaterThanStartDate(newDate, transactionSlipDueDate)) {
            // Tính số ngày thừa nếu có
            const int excessDays = calculateExcessDays(newDate, transactionSlipDueDate);

            if (INVALID_DATA == excessDays) return; // Kết thúc hàm nếu tính toán số ngày thừa không hợp lệ

            // Kiểm tra nếu số ngày thừa lớn hơn 0
            if (excessDays > 0) {
                // Thông báo cho người dùng về tình trạng mượn sách
                printf("Ngày mượn sách là: %s\n", transactionSlipBorrowDate);
                printf("Ngày trả sách dự kiến là: %s\n", transactionSlipDueDate);
                printf("Số lượng quyển sách mượn: %d\n", numberOfBooksBorrow);
                printf("Thời gian mượn sách tối đa là 7 ngày, tuy nhiên bạn đã mượn thêm %d ngày.\n", excessDays);
                printf("Phí phát sinh là: %f đồng (5000 đồng/ngày cho mỗi quyển sách).\n",
                       excessDays * LATE_DEFAULT_VALUE * numberOfBooksBorrow);
            } else {
                // Thông báo nếu không có phí phát sinh
                printf("Ngày trả sách (%s) là hợp lệ và không có phí phát sinh.\n", transactionSlipDueDate);
            }
        }

        // Gán mã độc giả vào mảng readerCodes tại vị trí borrowSlipIndex để lưu trữ riêng các mã độc giả
        strcpy(borrowingReaderCodes[borrowSlipIndex], transactionSlipReaderCode);
        strcpy(borrowingDates[borrowSlipIndex], transactionSlipBorrowDate);
        strcpy(borrowingDueDates[borrowSlipIndex], transactionSlipDueDate);

        // Lưu tất cả ISBN sách vào mảng BorrowingBookISBN sau khi vòng lặp kết thúc
        for (int i = 0; i < numberOfBooksBorrow; ++i) {
            if(isBlank(borrowingBookISBNTemps[i])) break;
            strcpy(borrowingBookISBNs[borrowSlipIndex][i], borrowingBookISBNTemps[i]);

            // Giảm số lượng sách trong kho
            editBook(borrowingBookISBNTemps[i], numberOfBook(borrowingBookISBNTemps[i]) - 1);
        }
        // In ra phiếu mượn sách
        printBorrowingSlip(borrowSlipIndex);
        borrowSlipIndex++; // Tăng chỉ số cho phiếu mượn tiếp theo
    }
}


void printBorrowingSlip(const int slipIndex) {
    // Kiểm tra xem chỉ số phiếu mượn có hợp lệ không
    if (slipIndex > MAX_SIZE) {
        std::cout << "Chỉ số phiếu mượn không hợp lệ. Vì số lượng phiếu mượn lớn hơn quy định 265 phiếu" << std::endl;
        return;
    }

    // In ra thông tin phiếu mượn sách
    std::cout << "===== PHIẾU MƯỢN SÁCH =====" << std::endl;
    std::cout << "Mã độc giả: " << borrowingReaderCodes[slipIndex] << std::endl;
    std::cout << "Ngày mượn: " << borrowingDates[slipIndex] << std::endl;
    std::cout << "Ngày trả dự kiến: " << borrowingDueDates[slipIndex] << std::endl;
    std::cout << "Danh sách sách mượn:" << std::endl;

    for (int i = 0; i < MAX_SIZE; ++i) {
        // Kiểm tra xem có mã ISBN nào đã được lưu không
        if (strlen(borrowingBookISBNs[slipIndex][i]) > 0) {
            std::cout << "  - Quyển sách ISBN: " << borrowingBookISBNs[slipIndex][i] << std::endl;
        } else {
            break; // Dừng lại nếu không còn mã sách nào
        }
    }
    std::cout << "============================" << std::endl;
}

void countAllBorrowedBooks() {
    int totalBorrowedBooks = 0; // Khởi tạo biến đếm số sách mượn

    // Duyệt qua tất cả các phiếu mượn
    for (int i = 0; i < borrowSlipIndex; i++) {
        // Đếm số sách trong mỗi phiếu mượn
        for (int j = 0; j < MAX_SIZE; j++) {
            // Kiểm tra xem mã ISBN có tồn tại không (không rỗng)
            if (strlen(borrowingBookISBNs[i][j]) > 0) {
                totalBorrowedBooks++; // Tăng biến đếm
            }
        }
    }

    // In ra số sách đang được mượn
    printf("Tổng số sách đang được mượn: %d\n", totalBorrowedBooks);
}

int findSlipByReaderCode(const char (&readerCode)[MAX_SIZE]) {
    // Duyệt qua tất cả các phiếu mượn đã tạo
    for (int i = 0; i < borrowSlipIndex; i++) {
        // So sánh mã độc giả trong từng phiếu mượn với mã độc giả cần tìm
        if (strcmp(borrowingReaderCodes[i], readerCode) == 0) {
            // Trả về chỉ số của phiếu mượn nếu tìm thấy mã độc giả
            return i;
        }
    }
    // Trả về INVALID_DATA nếu không tìm thấy mã độc giả trong bất kỳ phiếu mượn nào
    return INVALID_DATA;
}

int countAllBorrowingSlip() {
    int count = 0;
    for (int i = 0; i < borrowSlipIndex; i++) {
        // So sánh mã độc giả trong từng phiếu mượn với mã độc giả cần tìm
        if (!isBlank(borrowingReaderCodes[i])) {
            // Trả về chỉ số của phiếu mượn nếu tìm thấy mã độc giả
            count++;
        }
    }
    return count;
}

int countCurrentlyBorrowedBooks(const int slipIndex) {
    int bookCount = 0;

    // Kiểm tra chỉ số phiếu mượn hợp lệ
    if (slipIndex < 0 || slipIndex >= borrowSlipIndex) {
        return INVALID_DATA; // Trả về giá trị không hợp lệ nếu chỉ số không đúng
    }

    // Duyệt qua danh sách ISBN các sách trong phiếu mượn tại vị trí slipIndex
    for (int i = 0; i < MAX_SIZE; ++i) {
        // Kiểm tra nếu ISBN không rỗng thì tăng biến đếm
        if (strlen(borrowingBookISBNs[slipIndex][i]) > 0) {
            ++bookCount;
        }
    }

    // Trả về số lượng sách trong phiếu mượn
    return bookCount;
}

void createReturnSlip() {
    // Đếm số lượng phiếu mượn hiện có trong hệ thống
    const int countBorrowingSlips = countAllBorrowingSlip();
    if (0 == countBorrowingSlips) {
        std::cout << "Hiện tại không có phiếu mượn sách nào trong hệ thống." << std::endl;
        return; // Kết thúc hàm nếu không có phiếu mượn
    }

    char returnSlipReaderCode[MAX_SIZE];

    // Người dùng nhập mã độc giả cho phiếu trả
    createValue(TRANSACTION_SLIP_READER_CODE, returnSlipReaderCode);

    // Kiểm tra mã độc giả có tồn tại trong hệ thống không
    if (INVALID_DATA == findIndexReaderByCode(returnSlipReaderCode)) {
        printf("Không tồn tại thông tin mã độc giả (%s) trong hệ thống\n", returnSlipReaderCode);
        return; // Kết thúc hàm nếu mã độc giả không hợp lệ
    }

    // Tìm chỉ số phiếu mượn của độc giả
    const int existingSlipIndex = findSlipByReaderCode(returnSlipReaderCode);
    if (INVALID_DATA == existingSlipIndex) {
        printf("Độc giả (%s) chưa mượn sách trong hệ thống\n", returnSlipReaderCode);
        return; // Kết thúc hàm nếu độc giả chưa mượn sách
    }

    int numberOfBooksReturnSlip; // Số lượng sách muốn trả
    double penalty = 0; // Tổng tiền phạt do mất sách
    double feeLateLy = 0; // Phí phát sinh do trả sách trễ
    char returnBookISBNTemps[MAX_SIZE][MAX_SIZE]; // Mảng tạm lưu mã ISBN

    // Nhập số lượng sách mà độc giả muốn trả
    createValue(CHOOSE_NUMBER_RETURN_BOOK_NUMBER, numberOfBooksReturnSlip);

    // Kiểm tra số lượng sách hiện đang mượn trên phiếu
    const int currentBooksOnSlip = countCurrentlyBorrowedBooks(existingSlipIndex);
    if (numberOfBooksReturnSlip > currentBooksOnSlip) {
        std::cout << "Không thể trả quá " << currentBooksOnSlip << " sách trong phiếu mượn.\n";
        return; // Kết thúc hàm nếu số sách trả vượt quá số sách đã mượn
    }

    // Duyệt qua số lượng sách độc giả muốn trả
    for (int i = 0; i < numberOfBooksReturnSlip; ++i) {
        char transactionSlipBookISBN[MAX_SIZE];

        // Yêu cầu người dùng nhập ISBN của sách cần trả
        std::cout << TRANSACTION_SLIP_BOOK_ISBN << "[ " <<(i) <<" ]";
        createValue(TRANSACTION_SLIP_BOOK_ISBN, transactionSlipBookISBN);

        // Tìm chỉ số của sách trong hệ thống theo ISBN
        const int indexBook = findIndexBookByISBN(transactionSlipBookISBN);
        if (INVALID_DATA == indexBook) {
            printf("Không tồn tại thông tin quyển sách (%s) trong hệ thống\n", transactionSlipBookISBN);
            return; // Kết thúc hàm nếu mã ISBN không hợp lệ
        }

        // Kiểm tra sách có tồn tại trong phiếu mượn không
        if (!isBookInBorrowingSlip(existingSlipIndex, transactionSlipBookISBN)) {
            printf("Sách (%s) không có trong phiếu mượn của độc giả.\n", transactionSlipBookISBN);
            return; // Kết thúc hàm nếu sách không có trong phiếu mượn
        }
        // Lưu mã ISBN và tình trạng sách vào phiếu trả qua mảng tạm
        strcpy(returnBookISBNTemps[i], transactionSlipBookISBN);
    }

    // Nhập ngày trả sách từ người dùng
    char returnSlipDueDate[MAX_SIZE_DATE], newDate[MAX_SIZE_DATE], transactionSlipBorrowDate[MAX_SIZE_DATE];
    createDate(TRANSACTION_SLIP_ACTUAL_RETURN_DATE, returnSlipDueDate);

    // Lấy ngày mượn sách và tính ngày trả tối đa (sau 7 ngày)
    strcpy(transactionSlipBorrowDate, borrowingDates[existingSlipIndex]);
    addDaysToDateManual(borrowingDates[existingSlipIndex], 7, newDate);

    // Kiểm tra nếu ngày trả sách hợp lệ (không quá hạn)
    if (!isEndDateGreaterThanStartDate(newDate, returnSlipDueDate)) {
        const int excessDays = calculateExcessDays(newDate, returnSlipDueDate);

        if (INVALID_DATA == excessDays) return; // Kết thúc nếu tính toán không hợp lệ

        // Nếu có số ngày trả sách trễ, tính phí trễ hạn
        if (excessDays > 0) {
            printf("Bạn đã trả trễ %d ngày. Phí trễ hạn là %d đồng (5000 đồng/ngày cho mỗi quyển sách).\n", excessDays,
                   excessDays * 5000);
            feeLateLy += excessDays * numberOfBooksReturnSlip * LATE_DEFAULT_VALUE;
        } else {
            printf("Ngày trả sách (%s) hợp lệ, không có phí trễ hạn.\n", newDate);
        }
    }

    // Duyệt qua số lượng sách độc giả muốn trả
    for (int i = 0; i < numberOfBooksReturnSlip; ++i) {
        int status;
        char transactionSlipBookISBN[MAX_SIZE];

        // Set transactionSlipBookISBN từ mảng tạm
        strcpy(transactionSlipBookISBN, returnBookISBNTemps[i]);
        // Nhập tình trạng sách (0: mất, 1: bình thường)
        createValue(TRANSACTION_SLIP_STATUS_DATE, status);

        // Lấy số lượng sách hiện có trong hệ thống theo ISBN
        const int currentNumberOfBook = numberOfBook(transactionSlipBookISBN);

        // Tăng số lượng sách trong kho do sách đã được trả
        editBook(transactionSlipBookISBN, currentNumberOfBook + 1);

        strcpy(returnBookISBNTemps[i], transactionSlipBookISBN);

        returnSlipBookStatus[returnSlipIndex][i] = status;

        // Nếu sách bị mất, tính tiền phạt (200% giá sách)
        if (0 == status) {
            printf("Độc giả (%s) đã làm mất sách (%s). Phạt 200%% giá trị sách.\n", returnSlipReaderCode,
                   transactionSlipBookISBN);
            penalty += printBookPriceByIndex(findIndexBookByISBN(transactionSlipBookISBN)) * MONEY_DEFAULT_VALUE *
                    PENALTY_DEFAULT_VALUE;
        }

        // Xóa sách đã trả khỏi phiếu mượn
        removeBookFromBorrowingSlip(existingSlipIndex, transactionSlipBookISBN);
    }

    // Lưu các khoản phạt vào phiếu trả
    returnSlipLateFee[returnSlipIndex] = feeLateLy;
    returnSlipLateBookPenalty[returnSlipIndex] = penalty;

    if(0 != feeLateLy) {
        // Lưu mã độc giả có liên quan đến việc trả sách trễ
        strcpy(returnSlipReaderCodesLate[latelyIndex], returnSlipReaderCode);

        // Lưu mã độc giả có liên quan đến việc trả sách trễ
        latelyIndex++;
    }
    // Tăng chỉ số phiếu trả để chuẩn bị cho phiếu tiếp theo
    returnSlipIndex++;

    // In phiếu trả sách
    printReturnSlip(existingSlipIndex);

    // Cập nhật phiếu mượn còn lại nếu chưa trả hết sách
    if (numberOfBooksReturnSlip < currentBooksOnSlip) {
        std::cout << "Độc giả vẫn còn " << (currentBooksOnSlip - numberOfBooksReturnSlip) << " sách chưa trả.\n";
    } else {
        // Nếu tất cả sách đã trả, xóa phiếu mượn
        deleteSlipByIndex(existingSlipIndex);
    }
}

void clearSlipData(const int slipIndex) {
    // Xóa mã độc giả
    borrowingReaderCodes[slipIndex][0] = '\0'; // Đặt ký tự null cho chuỗi mã độc giả

    // Xóa mã ISBN các quyển sách
    for (int i = 0; i < MAX_SIZE; ++i) {
        borrowingBookISBNs[slipIndex][i][0] = '\0'; // Đặt ký tự null cho mỗi chuỗi ISBN
    }

    // Xóa ngày mượn sách
    borrowingDates[slipIndex][0] = '\0'; // Đặt ký tự null cho chuỗi ngày mượn

    // Xóa ngày trả sách dự kiến
    borrowingDueDates[slipIndex][0] = '\0'; // Đặt ký tự null cho chuỗi ngày trả sách
}

void deleteSlipByIndex(const int slipIndex) {
    const int totalSlips = countAllBorrowingSlip(); // Tổng số phiếu mượn

    // Kiểm tra nếu chỉ số phiếu mượn không hợp lệ
    if (slipIndex < 0 || slipIndex >= totalSlips) {
        std::cout << "Chỉ số phiếu mượn không hợp lệ." << std::endl;
        return; // Kết thúc hàm nếu chỉ số không hợp lệ
    }

    // Dịch chuyển các phiếu mượn còn lại về trước 1 vị trí, ghi đè lên phiếu mượn cần xóa
    for (int i = slipIndex; i < totalSlips - 1; ++i) {
        // Sao chép mã độc giả từ phiếu sau đến phiếu hiện tại
        strcpy(borrowingReaderCodes[i], borrowingReaderCodes[i + 1]);

        // Sao chép mã ISBN các quyển sách trong phiếu mượn
        for (int j = 0; j < MAX_SIZE; ++j) {
            strcpy(borrowingBookISBNs[i][j], borrowingBookISBNs[i + 1][j]);
        }

        // Sao chép ngày mượn sách
        strcpy(borrowingDates[i], borrowingDates[i + 1]);

        // Sao chép ngày trả sách dự kiến
        strcpy(borrowingDueDates[i], borrowingDueDates[i + 1]);
    }

    // Xóa phiếu mượn cuối cùng do đã được sao chép lên vị trí trước
    clearSlipData(totalSlips - 1);

    // Cập nhật số lượng phiếu mượn
    borrowSlipIndex--;

    std::cout << "Phiếu mượn tại chỉ số (" << slipIndex << ") đã được xóa thành công." << std::endl;
}

void removeBookFromBorrowingSlip(const int slipIndex, const char (&bookISBN)[MAX_SIZE]) {
    // Lấy số lượng sách hiện đang mượn trong phiếu mượn
    const int currentBooksOnSlip = countCurrentlyBorrowedBooks(slipIndex);

    // Duyệt qua danh sách sách trong phiếu mượn để tìm quyển sách cần xóa
    for (int i = 0; i < currentBooksOnSlip; ++i) {
        // Nếu tìm thấy mã ISBN khớp với sách cần xóa
        if (strcmp(borrowingBookISBNs[slipIndex][i], bookISBN) == 0) {
            // Dịch chuyển các sách sau vị trí này lên trên
            for (int j = i; j < currentBooksOnSlip - 1; ++j) {
                strcpy(borrowingBookISBNs[slipIndex][j], borrowingBookISBNs[slipIndex][j + 1]);
            }
            // Xóa sách cuối cùng trong danh sách (do đã dịch chuyển lên)
            borrowingBookISBNs[slipIndex][currentBooksOnSlip - 1][0] = '\0';
            // Đặt chuỗi rỗng để thể hiện rằng không có sách ở vị trí này

            std::cout << "Đã xóa sách có mã ISBN (" << bookISBN << ") khỏi phiếu mượn.\n";
            return; // Thoát ra khỏi hàm sau khi xóa sách
        }
    }

    // Nếu không tìm thấy mã ISBN trong phiếu mượn
    std::cout << "Không tìm thấy sách có mã ISBN (" << bookISBN << ") trong phiếu mượn.\n";
}

void printReturnSlip(const int slipIndex) {
    // Kiểm tra nếu chỉ số phiếu trả hợp lệ
    if (slipIndex < 0 || slipIndex >= returnSlipIndex) {
        std::cout << "Phiếu trả không tồn tại.\n";
        return;
    }

    // In mã độc giả
    std::cout << "Phiếu trả sách của độc giả: " << returnSlipReaderCodes[slipIndex] << "\n";

    // Lấy số lượng sách trong phiếu trả
    const int numberOfBooksInSlip = countCurrentlyReturnedBooks(slipIndex);

    // Nếu không có sách nào trong phiếu trả
    if (numberOfBooksInSlip == 0) {
        std::cout << "Không có sách nào trong phiếu trả này.\n";
        return;
    }

    // Duyệt qua danh sách sách đã trả và in thông tin
    for (int i = 0; i < numberOfBooksInSlip; ++i) {
        std::cout << "Sách " << i + 1 << ":\n";
        std::cout << " - Mã ISBN: " << borrowingBookISBNs[slipIndex][i] << "\n";
        std::cout << " - Tình trạng: " << (returnSlipBookStatus[slipIndex][i] == 0 ? "Mất" : "Bình thường") << "\n";
    }

    // In tổng số tiền phạt nếu có
    const double totalPenalty = returnSlipLateBookPenalty[slipIndex];
    if (totalPenalty > 0) {
        std::cout << "Tổng tiền phạt: " << totalPenalty << " đồng\n";
    } else {
        std::cout << "Không có tiền phạt.\n";
    }

    // In ngày trả sách
    std::cout << "Ngày trả sách: " << returnSlipDueDates[slipIndex] << "\n";
}

int countCurrentlyReturnedBooks(const int slipIndex) {
    // Kiểm tra nếu chỉ số phiếu trả hợp lệ
    if (slipIndex < 0 || slipIndex >= returnSlipIndex) {
        return 0; // Không hợp lệ, trả về 0
    }

    int count = 0; // Biến đếm số lượng sách đã trả

    // Duyệt qua tất cả các sách trong phiếu trả
    for (int i = 0; i < MAX_SIZE; ++i) {
        // Kiểm tra nếu mã ISBN của sách không rỗng
        if (strlen(borrowingBookISBNs[slipIndex][i]) > 0) {
            count++; // Tăng biến đếm nếu sách đã được trả
        } else {
            break; // Dừng vòng lặp khi gặp sách không còn trong phiếu
        }
    }

    return count; // Trả về số lượng sách đã trả
}

// Hàm thống kê danh sách độc giả bị trễ hạn
void listReadersWithLateReturns() {
    std::cout << "Danh sách độc giả bị trễ hạn:\n";
    bool foundLate = false; // Cờ kiểm tra xem có độc giả nào bị trễ hạn hay không

    // Duyệt qua tất cả các phiếu trả
    for (int i = 0; i < returnSlipIndex; ++i) {
        // Kiểm tra nếu phiếu trả có tiền phạt trễ hạn
        if (returnSlipLateBookPenalty[i] > 0) {
            std::cout << "Độc giả: " << returnSlipReaderCodes[i]
                    << "\nTiền phạt: " << returnSlipLateBookPenalty[i] + returnSlipLateBookPenalty[i]
                    << " đồng\n";
            foundLate = true; // Đánh dấu đã tìm thấy ít nhất một độc giả bị trễ hạn
        }
    }

    // Nếu không tìm thấy độc giả nào bị trễ hạn
    if (!foundLate) {
        std::cout << "Không có độc giả nào bị trễ hạn.\n";
    }
}

// Kiểm tra sách có trong phiếu mượn hay không
bool isBookInBorrowingSlip(const int borrowingSlipIndex, const char (&bookISBN)[MAX_SIZE]) {
    // Giả sử borrowingSlipBooks[borrowingSlipIndex] là mảng lưu các ISBN sách đã mượn
    // countCurrentlyBorrowedBooks[borrowingSlipIndex] là số lượng sách hiện đang mượn trong phiếu
    for (int i = 0; i < countCurrentlyBorrowedBooks(borrowingSlipIndex); ++i) {
        // So sánh từng ISBN trong phiếu mượn với ISBN cần tìm
        if (strcmp(borrowingBookISBNs[borrowingSlipIndex][i], bookISBN) == 0) {
            return true; // Sách được tìm thấy trong phiếu mượn
        }
    }
    return false; // Sách không tồn tại trong phiếu mượn
}
