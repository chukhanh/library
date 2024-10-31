//
// Created by ChuKhanhhh on 7/10/24.
//

#include "Book.h"
#include <iostream>

#include "../Utils/Date.h"

// Mảng lưu trữ các thông tin của sách (thay cho struct)
char bookISBNs[MAX_SIZE][MAX_SIZE]; // Mảng ISBN (mã sách)
char bookNames[MAX_SIZE][MAX_SIZE]; // Tên Sách
char bookAuthors[MAX_SIZE][MAX_SIZE]; // Mảng Tác giả
char bookPublisherEditions[MAX_SIZE][MAX_SIZE]; // Mảng Nhà suất bản
int bookYearOfPublications[MAX_SIZE]; // Mảng Năm suất bản
char bookCategories[MAX_SIZE][MAX_SIZE]; // Mảng Thể loại
double bookPrices[MAX_SIZE]; // Mảng Giá sách
int bookNumbers[MAX_SIZE]; // Mảng Số quyển sách
int bookIndex = 0;

// Hàm in thông tin của sách
void printBook(const int index) {
    if (strlen(bookISBNs[index]) == 0) {
        return;
    }
    printf("\nThông tin quyển sách thứ [%d] trong hệ thống là: ", index);
    std::cout << "\nISBN (mã sách): " << bookISBNs[index] << std::endl;
    std::cout << "\nTên Sách: " << bookNames[index] << std::endl;
    std::cout << "\nTác giả: " << bookAuthors[index] << std::endl;
    std::cout << "\nNhà suất bản: " << bookPublisherEditions[index] << std::endl;
    std::cout << "\nNăm suất bản: " << bookYearOfPublications[index] << std::endl;
    std::cout << "\nThể loại: " << bookCategories[index] << std::endl;
    std::cout << "\nGiá sách: " << bookPrices[index] * MONEY_DEFAULT_VALUE << std::endl;
    std::cout << "\nSố quyển sách: " << bookNumbers[index] << std::endl;
}

void editBook(const char (&bookISBN)[MAX_SIZE], const char (&bookName)[MAX_SIZE],
              const char (&bookAuthor)[MAX_SIZE], const char (&bookPublisherEdition)[MAX_SIZE],
              const int (&bookYearOfPublication), const char (&bookCategory)[MAX_SIZE],
              const double &bookPrice, const int &bookNumber) {
    // Kiểm tra nếu bookISBN được nhập vào tồn tại trong hệ thống, in ra kết quả
    const int index = findIndexBookByISBN(bookISBN);
    if (INVALID_DATA == index) {
        printf("Không tồn tại thông tin quyển sách (%s) trong hệ thống ", bookISBN);
        return;
    }

    if (!isValidateYear(bookYearOfPublication)) {
        std::cout << "Năm suất bản của sách không hợp lệ. Vui lòng nhập lại.\n";
        return;
    }

    // Gán tên sách (bookName) mới vào mảng bookNames tại vị trí index
    strcpy(bookNames[index], bookName);
    // Gán tên tác giả (bookAuthor) mới vào mảng bookAuthors tại vị trí index
    strcpy(bookAuthors[index], bookAuthor);
    // Gán năm sủa bảm (bookYearOfPublication) mới vào mảng bookYearOfPublications tại vị trí index
    bookYearOfPublications[index] = bookYearOfPublication;
    // Gán thể loại sách (bookCategory)mới vào mảng bookCategories tại vị trí index
    strcpy(bookCategories[index], bookCategory);
    // Gán giá sách (bookPrice) mới vào mảng bookPrices tại vị trí index
    bookPrices[index] = bookPrice;
    // Gán số lượng sách (bookNumber) mới vào mảng bookNumbers tại vị trí index
    bookNumbers[index] = bookNumber;
    // Gán nhà suất bản (bookPublisherEdition) mới vào mảng bookPublisherEditions tại vị trí index
    strcpy(bookPublisherEditions[index], bookPublisherEdition);

    std::cout << "Sửa thông tin quyển sách thành công!" << std::endl;
}

void editBook(const char (&bookISBN)[MAX_SIZE], const int &bookNumber) {
    // Kiểm tra nếu bookISBN được nhập vào tồn tại trong hệ thống, in ra kết quả
    const int index = findIndexBookByISBN(bookISBN);
    if (INVALID_DATA == index) {
        printf("Không tồn tại thông tin quyển sách (%s) trong hệ thống ", bookISBN);
        return;
    }

    // Gán số lượng sách (bookNumber) mới vào mảng bookNumbers tại vị trí index
    bookNumbers[index] = bookNumber;
}

void addNewBook() {
    // Tối đa số lượng sách chỉ có 100, nếu số lượng lớn hơn 100 in ra kết quả
    if (MAX_SIZE == bookIndex) {
        printf("Đã đạt giới hạn %d số lượng sách. ", MAX_SIZE);
        return;
    }

    char bookISBN[MAX_SIZE],
            bookName[MAX_SIZE],
            bookAuthor[MAX_SIZE],
            bookPublisherEdition[MAX_SIZE],
            bookCategory[MAX_SIZE];
    double bookPrice;
    int bookNumber, bookYearOfPublication;

    // Người dùng nhập mã sách
    createValue(BOOK_ISBN, bookISBN);

    // Kiểm tra nếu bookISBN được nhập vào tồn tại và hợp lệ trong hệ thống
    const int index = findIndexBookByISBN(bookISBN);


    if (isBlank(bookISBN)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại mã độc giả. Mã không được để trống." << std::endl;
        return;
    }

    // Kiểm tra nếu bookISBN được nhập vào tồn tại trong hệ thống, in ra kết quả
    if (INVALID_DATA != index) {
        printf("\nĐã tồn tại thông tin sách (%s) trong hệ thống ", bookISBN);
        return;
    }

    // Người dùng nhập tên của sách
    createValue(BOOK_NAME, bookName);

    if (isBlank(bookName)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại tên sách. Tên không được để trống." << std::endl;
        return;
    }
    // Người dùng nhập tác giả của sách
    createValue(BOOK_AUTHOR, bookAuthor);

    if (isBlank(bookAuthor)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại tác giả. Tên tác giả không được để trống." << std::endl;
        return;
    }
    // Người dùng nhập tên nhà suất bản
    createValue(BOOK_PUBLISHER_EDITION, bookPublisherEdition);

    if (isBlank(bookPublisherEdition)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại nhà suất bản. Tên nhà suất bản không được để trống." << std::endl;
        return;
    }
    // Người dùng nhập năm suất bản
    createValue(BOOK_YEAR_OF_PUBLICATION, bookYearOfPublication);

    if (!isValidateYear(bookYearOfPublication)) {
        std::cout << "\nBắt buộc phải nhập lại năm suất bản sách độc giả. Bị sai format. Bắt buộc nhập YYYY" <<
                std::endl;
        return;
    }

    // Người dùng nhập thể loại sách
    createValue(BOOK_CATEGORY, bookCategory);

    if (isBlank(bookCategory)) {
        // In ra thông báo lỗi nếu readerCode là null hoặc chuỗi rỗng
        std::cout << "\nBắt buộc phải nhập lại thể loại sách. Thể loại sách không được để trống." << std::endl;
        return;
    }
    // Người dùng nhập giá sách
    createValue(BOOK_PRICE, bookPrice);
    if (0 > bookPrice) {
        std::cout << "\nBắt buộc phải nhập lại số tiền sách. Bắt buộc số tiền > 0" << std::endl;
        return;
    }
    // Người dùng nhập số lượng sách
    createValue(BOOK_NUMBER, bookNumber);

    if (0 > bookNumber) {
        std::cout << "\nBắt buộc phải nhập lại số lượng sách. Bắt buộc số lượng sách > 0" << std::endl;
        return;
    }
    // Gán mã sách vào mảng bookISBN tại vị trí bookIndex để lưu trữ riêng các mã sách
    strcpy(bookISBNs[bookIndex], bookISBN);
    // Gán tên sách (bookName) vào mảng bookNames tại vị trí bookIndex
    strcpy(bookNames[bookIndex], bookName);
    // Gán tên tác giả (bookAuthor) vào mảng bookAuthors tại vị trí bookIndex
    strcpy(bookAuthors[bookIndex], bookAuthor);
    // Gán năm suất bản (bookYearOfPublication) vào mảng bookYearOfPublications tại vị trí bookIndex
    bookYearOfPublications[bookIndex] = bookYearOfPublication;
    // Gán thể loại sách (bookCategory) vào mảng bookCategories tại vị trí bookIndex
    strcpy(bookCategories[bookIndex], bookCategory);
    // Gán giá sách (bookPrice) vào mảng bookPrices tại vị trí bookIndex
    bookPrices[bookIndex] = bookPrice;
    // Gán số lượng sách (bookNumber) vào mảng bookNumbers tại vị trí bookIndex
    bookNumbers[bookIndex] = bookNumber;
    // Gán nhà suất bản (bookPublisherEdition) vào mảng bookPublisherEditions tại vị trí bookIndex
    strcpy(bookPublisherEditions[bookIndex], bookPublisherEdition);

    // In thông tin sách vừa nhập
    printBook(bookIndex);

    // Tăng biến đếm sách (bookIndex) lên 1 để chuẩn bị cho lần nhập tiếp theo
    bookIndex++;
}


int findIndexBookByISBN(const char (&bookISBN)[MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(bookISBNs[i], bookISBN) == 0) {
            return i;
        }
    }
    return -1;
}

void findBookByName(const char (&bookName)[MAX_SIZE]) {
    bool isFind = false; // Biến kiểm tra xem đã tìm thấy độc giả hay chưa

    // Duyệt qua tất cả các chỉ số trong mảng bookNames
    for (int i = 0; i < MAX_SIZE; i++) {
        if (strcmp(bookNames[i], bookName) == 0) {
            // So sánh tên sách
            printBook(i); // In thông tin
            isFind = true; // Đánh dấu là đã tìm thấy
        }
    }

    // In thông báo nếu không tìm thấy độc giả
    if (!isFind) {
        std::cout << "Không tồn tại sách có tên (" << bookName << ") trong hệ thống." << std::endl;
    }
}

void findBookByISBN(const char (&bookISBN)[MAX_SIZE]) {
    // Kiểm tra nếu bookISBN được nhập vào tồn tại trong hệ thống, in ra kết quả
    const int index = findIndexBookByISBN(bookISBN);
    if (INVALID_DATA == index) {
        printf("Không tồn tại thông tin sách (%s) trong hệ thống ", bookISBN);
        return;
    }
    printBook(index);
}

void deleteBook(const char (&bookISBN)[MAX_SIZE]) {
    // Kiểm tra nếu bookISBN được nhập vào tồn tại trong hệ thống, in ra kết quả
    const int index = findIndexBookByISBN(bookISBN);
    if (INVALID_DATA == index) {
        printf("Không tồn tại thông tin sách (%s) trong hệ thống ", bookISBN);
        return;
    }

    // Dịch chuyển tất cả các phần tử sau vị trí cần xóa lên một vị trí
    for (int i = index; i < bookIndex - 1; i++) {
        strcpy(bookISBNs[i], bookISBNs[i + 1]);
        strcpy(bookNames[i], bookNames[i + 1]);
        strcpy(bookAuthors[i], bookAuthors[i + 1]);
        strcpy(bookCategories[i], bookCategories[i + 1]);
        strcpy(bookPublisherEditions[i], bookPublisherEditions[i + 1]);
        bookYearOfPublications[i] = bookYearOfPublications[i + 1];
        bookPrices[i] = bookPrices[i + 1];
        bookNumbers[i] = bookNumbers[i + 1];
    }

    // Giảm chỉ số bookIndex sau khi xóa
    bookIndex--;

    // (Tùy chọn) Xóa giá trị cuối cùng bằng cách đặt lại giá trị mặc định
    strcpy(bookISBNs[bookIndex], "");
    strcpy(bookNames[bookIndex], "");
    strcpy(bookAuthors[bookIndex], "");
    strcpy(bookCategories[bookIndex], "");
    strcpy(bookPublisherEditions[bookIndex], "");

    std::cout << "\nSách đã được xóa thành công!" << std::endl;
}

void getAllBook() {
    if (isBlank(bookISBNs[0])) {
        printf("\nHiện tại không có tồn tại quyển sách nào trong hệ thống\n");
    } else {
        for (int i = 0; i < MAX_SIZE; i++) {
            printBook(i);
        }
    }
}

void numberOfBook() {
    int sum = 0;
    for (int const bookNumber: bookNumbers) {
        if (0 == bookNumber) continue;
        sum += bookNumber;
    }
    if (0 == sum) {
        printf("Không tồn tại sách nào trong hệ thống\n ");
    } else {
        std::cout << "Số lượng sách trong hệ thống: " << sum << "\n" << std::endl;
    }
}

int countBook() {
    int sum = 0;
    for (int const bookNumber: bookNumbers) {
        if (0 == bookNumber) continue;
        sum += bookNumber;
    }
    return sum;
}

int numberOfBook(const char (&bookISBN)[MAX_SIZE]) {
    const int index = findIndexBookByISBN(bookISBN);
    if (INVALID_DATA == index) {
        printf("Không tồn tại thông tin sách (%s) trong hệ thống ", bookISBN);
        return 0;
    }

    return bookNumbers[index];
}

void countBooksByCategory() {
    char uniqueCategories[MAX_SIZE][MAX_SIZE]; // Mảng lưu các thể loại đã xuất hiện
    int categoryCount[MAX_SIZE] = {0};         // Mảng lưu tổng số lượng sách cho từng thể loại
    int uniqueCategoryCount = 0;               // Số lượng các thể loại duy nhất đã xuất hiện

    // Duyệt qua tất cả các sách
    for (int i = 0; i < MAX_SIZE; ++i) {
        char bookCategorie[MAX_SIZE];
        strcpy(bookCategorie, bookCategories[i]);
        const int bookNumber = bookNumbers[i];

        if (strlen(bookCategorie) > 0) { // Kiểm tra nếu thể loại sách không phải chuỗi trống
            bool found = false;

            // Kiểm tra xem thể loại đã có trong mảng uniqueCategories chưa
            for (int j = 0; j < uniqueCategoryCount; ++j) {
                if (strcmp(bookCategorie, uniqueCategories[j]) == 0) {
                    // Nếu thể loại đã tồn tại, cộng thêm số lượng sách của thể loại đó
                    categoryCount[j] += bookNumber;
                    found = true;
                    break;
                }
            }

            // Nếu thể loại chưa có trong mảng uniqueCategories, thêm nó vào
            if (!found) {
                strcpy(uniqueCategories[uniqueCategoryCount], bookCategorie);
                categoryCount[uniqueCategoryCount] = bookNumber;
                uniqueCategoryCount++;
            }
        }
    }

    // Kiểm tra nếu không có thể loại sách nào được tìm thấy
    if (uniqueCategoryCount == 0) {
        std::cout << "Không tìm thấy quyển sách nào trong hệ thống\n" << std::endl;
    } else {
        // In kết quả thống kê
        std::cout << "Thống kê số lượng sách theo thể loại:\n";
        for (int i = 0; i < uniqueCategoryCount; ++i) {
            std::cout << "Thể loại: " << uniqueCategories[i] << " - Số lượng: " << categoryCount[i] << std::endl;
        }
        std::cout << "\n";
    }
}

double printBookPriceByIndex(const int index) {
    return bookPrices[index];
}
