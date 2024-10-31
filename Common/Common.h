#ifndef COMMON_H
#define COMMON_H

constexpr int MAX_SIZE = 265;
constexpr int MAX_SIZE_DATE = 11;
constexpr int INVALID_DATA = -1;
constexpr char BLANK_DATA = ' ';
constexpr char DOT_CHAR = '.';
constexpr char SPECIAL_CHAR = '@';
constexpr char FEMALE = 'F';
constexpr char MALE = 'M';
constexpr double PENALTY_DEFAULT_VALUE = 2;
constexpr double LATE_DEFAULT_VALUE = 5000;
constexpr double MONEY_DEFAULT_VALUE = 1000;

// Thông tin thẻ độc giả cần quản lí bao gồm: mã độc giả, họ tên, CMND, ngày tháng
// năm sinh, giới tính, email, địa chỉ, ngày lập thẻ và ngày hết hạn của thẻ (48 tháng
// kể từ ngày lập thẻ).
constexpr char READER_CODE[MAX_SIZE] = "Mã độc giả";
constexpr char READER_NAME[MAX_SIZE] = "Họ tên";
constexpr char READER_NATIONALID[MAX_SIZE] = "CMND, bắt buộc nhập 9 chữ số";
constexpr char READER_YEAR_BIRTHDAY[MAX_SIZE] = "Năm Sinh với format là YYYY";
constexpr char READER_SEX[MAX_SIZE] = "Giới tính. Nếu là Nam nhập M, nếu là Nữ Nhập F";
constexpr char READER_EMAIL[MAX_SIZE] = "Email , ví dụ a@gmail.com";
constexpr char READER_ADDRESS[MAX_SIZE] = "Địa chỉ";
constexpr char READER_CARD_CREATE_TIME[MAX_SIZE] = "Ngày lập thẻ";
constexpr char READER_CARD_END_TIME[MAX_SIZE] = "Ngày hết hạn thẻ";

// Thông tin sách cần quản lí bao gồm: ISBN (mã sách), tên sách, tác giả, nhà xuất
// bản, năm xuất bản, thể loại, giá sách, số quyển sách.
constexpr char BOOK_ISBN[MAX_SIZE] = "ISBN (mã sách)";
constexpr char BOOK_NAME[MAX_SIZE] = "Tên Sách ";
constexpr char BOOK_AUTHOR[MAX_SIZE] = "Tác giả";
constexpr char BOOK_PUBLISHER_EDITION[MAX_SIZE] = "Nhà suất bản";
constexpr char BOOK_YEAR_OF_PUBLICATION[MAX_SIZE] = "Năm suất bản với format là YYYY";
constexpr char BOOK_CATEGORY[MAX_SIZE] = "Thể loại";
constexpr char BOOK_PRICE[MAX_SIZE] = "Giá sách (*1000)";
constexpr char BOOK_NUMBER[MAX_SIZE] = "Số quyển sách";

//Mỗi phiếu mượn/trả sách chứa thông tin về mã độc giả, ngày mượn, ngày trả dự
// kiến, ngày trả thực tế và danh sách ISBN của các sách được mượn. Mỗi sách được
// mượn tối đa trong 7 ngày, nếu quá hạn sẽ bị phạt tiền 5.000 đồng/ngày. Nếu sách
// bị mất thì độc giả đó sẽ bị phạt số tiền tương ứng 200% giá sách.

constexpr char TRANSACTION_SLIP_READER_CODE[MAX_SIZE] = "Mã độc giả";
constexpr char TRANSACTION_SLIP_BOOK_ISBN[MAX_SIZE] = "Mã ISBN (mã sách)";
constexpr char TRANSACTION_SLIP_BORROW_DATE[MAX_SIZE] = "Ngày mượn";
constexpr char TRANSACTION_SLIP_DUE_DATE[MAX_SIZE] = "Ngày trả dự kiến";
constexpr char TRANSACTION_SLIP_ACTUAL_RETURN_DATE[MAX_SIZE] = "Ngày trả thực tế";
constexpr char TRANSACTION_SLIP_STATUS_DATE[MAX_SIZE] = "Trình trạng sách, Nếu vẫn còn nhập 1, Nếu mất nhập 0";
constexpr char TRANSACTION_SLIP_LATE_FEE[MAX_SIZE] = "Phí phạt quá hạn";
constexpr char TRANSACTION_SLIP_LATE_BOOK_PENALTY[MAX_SIZE] = "Phí phạt mất sách";

// Other Text
// Độc giả
constexpr char CHOOSE_NUMBER_OR_BACK_MENU[MAX_SIZE] = "chữ số để chọn chức năng. Nếu muốn quay lại menu chính, nhập -1";
constexpr char CHOOSE_NUMBER_OR_EXIT[MAX_SIZE] =
        "chữ số để tiến hành sử dụng các chức năng. Nếu muốn thoát chương trình, nhập -1";
constexpr char READER_CODE_EDITOR[MAX_SIZE] = "mã độc giả muốn sửa thông tin: ";
constexpr char READER_CODE_DELETE[MAX_SIZE] = "mã độc giả muốn xoá: ";
constexpr char READER_CODE_FIND_CMND[MAX_SIZE] = "CMND muốn tìm: ";
constexpr char READER_CODE_FIND_NAME[MAX_SIZE] = "Tên độc giả muốn tìm: ";

// Sách
constexpr char BOOK_CODE_EDITOR[MAX_SIZE] = "mã quyển sách muốn sửa thông tin";
constexpr char BOOK_CODE_FIND[MAX_SIZE] = "mã quyển sách muốn tìm";
constexpr char BOOK_CODE_FIND_NAME[MAX_SIZE] = "tên quyển sách muốn tìm";
constexpr char CHOOSE_NUMBER_LIST_BOOK_ISBN[MAX_SIZE] = "-1, Nếu muốn thoát nhập mã sách ISBN";
constexpr char CHOOSE_NUMBER_BORROW_BOOK_NUMBER[MAX_SIZE] = "số lượng sách muốn mượn";
constexpr char CHOOSE_NUMBER_RETURN_BOOK_NUMBER[MAX_SIZE] = "số lượng sách muốn mượn";


// Common Function, để tạo input nhập giá trị vào cho từng title phía trên
// Dùng cho char
void createValue(const char (&title)[MAX_SIZE], char (&value)[MAX_SIZE]);

// Dùng cho double
void createValue(const char (&title)[MAX_SIZE], double &value);

// Dùng cho int
void createValue(const char (&title)[MAX_SIZE], int &value);

// Dùng để tạo ngày tháng năm
void createDate(const char (&title)[MAX_SIZE], char (&date)[MAX_SIZE_DATE]);

// Kiêm tra giá trị chuỗi có rỗng hoặc blank không
bool isBlank(const char (&str)[MAX_SIZE]);

// Kiểm tra email từ chuỗi
bool isValidateEmail(const char (&email)[MAX_SIZE]);

// Kiểm tra giới tính từ chuỗi
bool isValidateSex(const char (&sex)[MAX_SIZE]);

// Kiểm tra giá trị nhập vào của CMND
bool isValidNationId(const char (&nationId)[MAX_SIZE]);

#endif //COMMON_H
