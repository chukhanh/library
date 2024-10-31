//
// Created by ChuKhanhhh on 6/10/24.
//

#include "Menu.h"
#include <iostream>

#include "../Book/Book.h"
#include "../Common/Common.h"
#include "../Reader/Reader.h"
#include "../Transaction/Transaction.h"


void startMenuManagement() {
    // Vòng lặp vô hạn để tiếp tục hiển thị menu và nhận lựa chọn từ người dùng
    while (true) {
        int number; // Biến lưu trữ lựa chọn từ người dùng

        // Hiển thị menu chức năng chính
        std::cout << "\n1: Quản lý độc giả  " << std::endl;
        std::cout << "\n2: Quản lý sách  " << std::endl;
        std::cout << "\n3: Lập phiếu mượn sách  " << std::endl;
        std::cout << "\n4: Lập phiếu trả sách  " << std::endl;
        std::cout << "\n5: Các thống kê cơ bản  " << std::endl;

        // Yêu cầu người dùng nhập lựa chọn
        createValue(CHOOSE_NUMBER_OR_EXIT, number);

        // Nếu người dùng nhập -1, thoát khỏi vòng lặp và kết thúc chương trình
        if (number == INVALID_DATA) {
            std::cout << "\nChương trình đã kết thúc. Xin hẹn gặp lại!" << std::endl;
            break;
        }

        // Xử lý các lựa chọn của người dùng
        switch (number) {
            case 1:
                startReaderManagement(); // Gọi hàm quản lý độc giả
                break;
            case 2:
                startBookManagement(); // Gọi hàm quản lý sách
                break;
            case 3:
                std::cout << "\nBạn đã chọn chức năng Lập phiếu mượn sách." << std::endl;
                createBorrowingSlip();
                break;
            case 4:
                std::cout << "\nBạn đã chọn chức năng Lập phiếu trả sách." << std::endl;
                createReturnSlip();
                break;
            case 5:
                std::cout << "\nBạn đã chọn chức năng Các thống kê cơ bản." << std::endl;
                startBasicStatisticsManagement();
                break;
            default:
                std::cout << "\nLựa chọn không hợp lệ. Vui lòng nhập lại." << std::endl;
                break;
        }
    }
}

void startReaderManagement() {
    // Vòng lặp vô hạn để tiếp tục hiển thị menu quản lý độc giả
    while (true) {
        // Biến để lưu trữ dữ liệu độc giả
        char readerCodeRequest[MAX_SIZE];
        char readerNameRequest[MAX_SIZE];
        char readerNationalIdRequest[MAX_SIZE];
        int readerYearBirthdayRequest;
        char readerSexRequest[MAX_SIZE];
        char readerEmailRequest[MAX_SIZE];
        char readerAddressRequest[MAX_SIZE];
        char readerCardCreateTimeRequest[MAX_SIZE_DATE];
        char readerCardEndTimeRequest[MAX_SIZE_DATE];
        int number; // Biến lưu trữ lựa chọn từ người dùng

        // Hiển thị các chức năng quản lý độc giả
        std::cout << "\nChương trình quản lý độc giả có các chức năng sau:" << std::endl;
        std::cout << "\n1: Xem danh sách độc giả trong thư viện" << std::endl;
        std::cout << "\n2: Thêm độc giả" << std::endl;
        std::cout << "\n3: Chỉnh sửa thông tin độc giả" << std::endl;
        std::cout << "\n4: Xóa độc giả" << std::endl;
        std::cout << "\n5: Tìm kiếm độc giả theo CMND" << std::endl;
        std::cout << "\n6: Tìm kiếm sách theo họ tên độc giả" << std::endl;

        // Yêu cầu người dùng nhập lựa chọn
        createValue(CHOOSE_NUMBER_OR_BACK_MENU, number);

        // Nếu người dùng nhập -1, quay lại menu chính
        if (number == INVALID_DATA) {
            std::cout << "\nQuay lại menu chính..." << std::endl;
            break; // Thoát khỏi vòng lặp và quay lại menu chính
        }

        // Xử lý các lựa chọn trong menu quản lý độc giả
        switch (number) {
            case 1:
                std::cout << "\nBạn đã chọn chức năng Xem danh sách độc giả." << std::endl;
                getAllReader();
                break;
            case 2:
                std::cout << "\nBạn đã chọn chức năng Thêm độc giả." << std::endl;
                addNewReader();
                break;
            case 3:
                std::cout << "\nBạn đã chọn chức năng Chỉnh sửa thông tin độc giả." << std::endl;

                createValue(READER_CODE_EDITOR, readerCodeRequest);

                if(INVALID_DATA == findIndexReaderByCode(readerCodeRequest)) {
                    printf("Không tồn tại thông tin độc giả (%s) trong hệ thống\n", readerCodeRequest);
                }else {
                    createValue(READER_NAME, readerNameRequest);
                    createValue(READER_NATIONALID, readerNationalIdRequest);
                    createValue(READER_YEAR_BIRTHDAY, readerYearBirthdayRequest);
                    createValue(READER_SEX, readerSexRequest);
                    createValue(READER_EMAIL, readerEmailRequest);
                    createValue(READER_ADDRESS, readerAddressRequest);
                    createDate(READER_CARD_CREATE_TIME, readerCardCreateTimeRequest);
                    createDate(READER_CARD_END_TIME, readerCardEndTimeRequest);

                    editReader(readerCodeRequest, readerNameRequest, readerNationalIdRequest,
                               readerYearBirthdayRequest, readerSexRequest, readerEmailRequest,
                               readerAddressRequest, readerCardCreateTimeRequest, readerCardEndTimeRequest);
                }
                    break;
            case 4:
                std::cout << "\nBạn đã chọn chức năng Xóa độc giả." << std::endl;
                // Reset fields before entering new data
                createValue(READER_CODE_DELETE, readerCodeRequest);
                deleteReader(readerCodeRequest);
                break;
            case 5:
                std::cout << "\nBạn đã chọn chức năng Tìm kiếm độc giả theo CMND." << std::endl;
                createValue(READER_CODE_FIND_CMND, readerNationalIdRequest);
                findReaderByNationalId(readerNationalIdRequest);
                break;
            case 6:
                std::cout << "\nBạn đã chọn chức năng Tìm kiếm sách theo họ tên độc giả." << std::endl;
                createValue(READER_CODE_FIND_NAME, readerNameRequest);
                findReaderByFullName(readerNameRequest);
                break;
            default:
                std::cout << "\nLựa chọn không hợp lệ. Vui lòng nhập lại." << std::endl;
                break;
        }
    }
}

void startBookManagement() {
    // Biến để lưu trữ dữ liệu quyển sách
    char bookISBN[MAX_SIZE]
            , bookName[MAX_SIZE]
            , bookAuthor[MAX_SIZE]
            , bookPublisherEdition[MAX_SIZE]
            , bookCategory[MAX_SIZE];
    double bookPrice;
    int bookNumber, bookYearOfPublication;

    // Vòng lặp vô hạn để tiếp tục hiển thị menu quản lý sách
    while (true) {
        int number; // Biến lưu trữ lựa chọn từ người dùng

        // Hiển thị các chức năng quản lý độc giả
        std::cout << "\nChương trình quản lý sách có các chức năng sau:" << std::endl;
        std::cout << "\n1: Xem danh sách các sách trong thư viện" << std::endl;
        std::cout << "\n2: Thêm sách" << std::endl;
        std::cout << "\n3: Chỉnh sửa thông tin một quyển sách" << std::endl;
        std::cout << "\n4: Xóa thông tin sách" << std::endl;
        std::cout << "\n5: Tìm kiếm sách theo ISBN" << std::endl;
        std::cout << "\n6: Tìm kiếm sách theo tên sách" << std::endl;

        // Yêu cầu người dùng nhập lựa chọn
        createValue(CHOOSE_NUMBER_OR_BACK_MENU, number);

        // Nếu người dùng nhập -1, quay lại menu chính
        if (number == INVALID_DATA) {
            std::cout << "\nQuay lại menu chính..." << std::endl;
            break; // Thoát khỏi vòng lặp và quay lại menu chính
        }

        // Xử lý các lựa chọn trong menu quản lý độc giả
        switch (number) {
            case 1:
                std::cout << "\nBạn đã chọn chức năng Xem danh sách các sách." << std::endl;
                getAllBook();
                break;
            case 2:
                std::cout << "\nBạn đã chọn chức năng Thêm sách mới." << std::endl;
                addNewBook();
                break;
            case 3:
                std::cout << "\nBạn đã chọn chức năng Chỉnh sửa thông tin một quyển sách." << std::endl;

                createValue(BOOK_CODE_EDITOR, bookISBN);


                if(INVALID_DATA == findIndexBookByISBN(bookISBN)) {
                    printf("Không tồn tại thông tin quyển sách (%s) trong hệ thống\n", bookISBN);
                }else {
                    // Người dùng nhập tên của sách
                    createValue(BOOK_NAME, bookName);
                    // Người dùng nhập tác giả của sách
                    createValue(BOOK_AUTHOR, bookAuthor);
                    // Người dùng nhập tên nhà suất bản
                    createValue(BOOK_PUBLISHER_EDITION, bookPublisherEdition);
                    // Người dùng nhập năm suất bản
                    createValue(BOOK_YEAR_OF_PUBLICATION, bookYearOfPublication);
                    // Người dùng nhập thể loại sách
                    createValue(BOOK_CATEGORY, bookCategory);
                    // Người dùng nhập giá sách
                    createValue(BOOK_PRICE, bookPrice);
                    // Người dùng nhập số lượng sách
                    createValue(BOOK_NUMBER, bookNumber);

                    editBook(bookISBN, bookName, bookAuthor,
                             bookPublisherEdition, bookYearOfPublication, bookCategory,
                             bookPrice, bookNumber);
                }
                break;
            case 4:
                std::cout << "\nBạn đã chọn chức năng Xóa một quyển sách." << std::endl;
                createValue(BOOK_CODE_EDITOR, bookISBN);
                deleteBook(bookISBN);
                break;
            case 5:
                std::cout << "\nBạn đã chọn chức năng Tìm kiếm sách theo ISBN." << std::endl;
                createValue(BOOK_CODE_FIND, bookISBN);
                findBookByISBN(bookISBN);
                break;
            case 6:
                std::cout << "\nBạn đã chọn chức năng Tìm kiếm sách theo tên sách." << std::endl;
                createValue(BOOK_CODE_FIND_NAME, bookName);
                findBookByName(bookName);
                break;
            default:
                std::cout << "\nLựa chọn không hợp lệ. Vui lòng nhập lại." << std::endl;
                break;
        }
    }
}

void startBasicStatisticsManagement() {
    // Vòng lặp vô hạn để tiếp tục hiển thị menu quản lý sách
    while (true) {
        int number; // Biến lưu trữ lựa chọn từ người dùng

        // Hiển thị các chức năng quản lý độc giả
        std::cout << "\nThống kê cơ bản có các chức năng sau:" << std::endl;
        std::cout << "\n1: Thống kê số lượng sách trong thư viện" << std::endl;
        std::cout << "\n2: Thống kê số lượng sách theo thể loại" << std::endl;
        std::cout << "\n3: Thống kê số lượng độc giả" << std::endl;
        std::cout << "\n4: Thống kê số lượng độc giả theo giới tính" << std::endl;
        std::cout << "\n5: Thống kê số sách đang được mượn" << std::endl;
        std::cout << "\n6: Thống kê danh sách độc giả bị trễ hạn" << std::endl;

        // Yêu cầu người dùng nhập lựa chọn
        createValue(CHOOSE_NUMBER_OR_BACK_MENU, number);

        // Nếu người dùng nhập -1, quay lại menu chính
        if (number == INVALID_DATA) {
            std::cout << "\nQuay lại menu chính..." << std::endl;
            break; // Thoát khỏi vòng lặp và quay lại menu chính
        }

        // Xử lý các lựa chọn trong menu quản lý độc giả
        switch (number) {
            case 1:
                std::cout << "\nBạn đã chọn chức năng Thống kê số lượng sách trong thư viện " <<std::endl;
                numberOfBook();
                break;
            case 2:
                std::cout << "\nBạn đã chọn chức năng Thống kê số lượng sách theo thể loại." << std::endl;
                countBooksByCategory();
                break;
            case 3:
                std::cout << "\nBạn đã chọn chức năng Thống kê số lượng độc giả " <<std::endl;
                numberOfReader();
                break;
            case 4:
                std::cout << "\nBạn đã chọn chức năng Thống kê số lượng độc giả theo giới tính." << std::endl;
                numberOfReaderBySex();
                break;
            case 5:
                std::cout << "\nBạn đã chọn chức năng Thống kê số sách đang được mượn" << std::endl;
                countAllBorrowedBooks();
                break;
            case 6:
                std::cout << "\nBạn đã chọn chức năng Thống kê danh sách độc giả bị trễ hạn." << std::endl;
                listReadersWithLateReturns();
                break;
            default:
                std::cout << "\nLựa chọn không hợp lệ. Vui lòng nhập lại." << std::endl;
                break;
        }
    }
}
