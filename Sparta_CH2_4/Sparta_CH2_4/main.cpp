#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Book
{
private:
	std::string title;
	std::string author;

public:
	Book(const std::string& bookTitle, const std::string& bookAuthor) : title(bookTitle), author(bookAuthor) {}

    std::string getTitle() const { return title; }

    std::string getAuthor() const { return author; }
};

class BookManager
{
private:
	std::vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
	void addBook(const std::string& bookTitle, const std::string& bookAuthor)
	{
		books.push_back(Book(bookTitle, bookAuthor)); // push_back 사용
		std::cout << "책이 추가되었습니다: " << bookTitle << " by " << bookAuthor << std::endl;
	}

    // 모든 책 출력 메서드
    void displayAllBooks() const
    {
        if (books.empty())
        {
            std::cout << "현재 등록된 책이 없습니다." << std::endl;
            return;
        }

        std::cout << "현재 도서 목록:" << std::endl;
        for (size_t i = 0; i < books.size(); ++i) // 일반적인 for문 사용
        {
            std::cout << "- " << books[i].getTitle() << " by " << books[i].getAuthor() << std::endl;
        }
    }

    Book* findBookByTitle(std::string& titleName)
    {
        for (int i = 0; i < books.size(); ++i)
        {
            std::string currentTitle = books[i].getTitle();

            if (currentTitle.compare(titleName) == 0)
            {
                return &books[i];
            }
        }

        return nullptr;
    }

    Book* findBookByAuthor(std::string& authorName)
    {
        for (int i = 0; i < books.size(); ++i)
        {
            std::string currentAuthor = books[i].getAuthor();

            if (currentAuthor.compare(authorName) == 0)
            {
                return &books[i];
            }
        }

        return nullptr;
    }

    // 검색을 책 제목으로하는 메서드
    // 책 제목이 동일한 경우는 없다고 가정
    void searchByTitle(std::string titleName)
    {
        Book* curBook = findBookByTitle(titleName);

        if (nullptr == curBook)
        {
            std::cout << "책을 찾지 못했습니다!" << std::endl;
        }
        else
        {
            std::cout << "책을 찾았습니다!" << std::endl;
            std::cout << "- " << curBook->getTitle() << " by " << curBook->getAuthor() << std::endl;
        }
    }

    // 검색을 책 작가로하는 메서드
    void searchByAuthor(std::string authorName)
    {
        Book* curBook = findBookByAuthor(authorName);

        if (nullptr == curBook)
        {
            std::cout << "책을 찾지 못했습니다!" << std::endl;
        }
        else
        {
            std::cout << "책을 찾았습니다!" << std::endl;
            std::cout << "- " << curBook->getTitle() << " by " << curBook->getAuthor() << std::endl;
        }
    }

    Book* getBookByTitle(std::string titleName)
    {
        return findBookByTitle(titleName);
    }

    Book* getBookByAuthor(std::string AuthorName)
    {
        return findBookByAuthor(AuthorName);
    }
};

class BorrowManager
{
private:
    std::unordered_map<std::string, int> stock;

public:
    void initializeStock(Book* book, int quantity = 3)
    {
        stock.insert({ book->getTitle(), quantity});
    }

    void displayStock()
    {
        for (auto e : stock)
        {
            std::cout << "- 제목: " << e.first << " 책의 남은 재고는 " << e.second << "개 입니다." << std::endl;
        }
    }

    void brrowBook(std::string title)
    {
        if (stock.find(title) == stock.end())
        {
            std::cout << "재고 목록에서 책을 찾지 못했습니다!" << std::endl;
            return;
        }

        if (0 >= stock[title])
        {
            std::cout << "재고가 남아있지 않아 대여가 불가능합니다!" << std::endl;
            return;
        }

        while (true)
        {
            std::cout << "최대 " << stock[title] << "개 대여 가능합니다." << std::endl;
            std::cout << "몇 개를 대여하시겠습니까?" << std::endl;

            int input;
            std::cin >> input;

            if (0 <= input && stock[title] >= input)
            {
                stock[title] -= input;

                std::cout << input << "개가 대여 됐습니다." << std::endl;
                break;
            }
            else
            {
                std::cout << "잘못된 입력입니다." << std::endl;
            }
        }
    }

    void returnBook(std::string title)
    {
        if (stock.find(title) == stock.end())
        {
            std::cout << "재고 목록에서 책을 찾지 못했습니다!" << std::endl;
            return;
        }

        if (3 <= stock[title])
        {
            std::cout << "대여된 수량이 없습니다." << std::endl;
            return;
        }

        while (true)
        {
            std::cout << "최대 " << 3 - stock[title] << "개 반납 가능합니다." << std::endl;
            std::cout << "몇 개를 반납하시겠습니까?" << std::endl;

            int input;
            std::cin >> input;

            if (0 <= input && 3 - stock[title] >= input)
            {
                stock[title] += input;

                std::cout << input << "개가 반납 됐습니다." << std::endl;
                break;
            }
            else
            {
                std::cout << "잘못된 입력입니다." << std::endl;
            }
        }
    }
};

enum class InputName : int
{
    NONE,
    AddBook,
    DisplayAllBooks,
    SearchByTitle,
    SearchByAuthor,
    DisplayAllStock,
    BorrowByTitle,
    BorrowByAuthor,
    ReturnByTitle,
    ReturnByAuthor,
    End,
};

// 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
// 프로그램 종료를 선택하기 전까지 계속 동작합니다.
void runLibrary(BookManager& bookManager, BorrowManager& borrowManager)
{
    bool bIsRunning = true;
    while (bIsRunning) {
        std::cout << "\n도서관 관리 프로그램" << std::endl;
        std::cout << static_cast<int>(InputName::AddBook) << ". 책 추가" << std::endl; // 책 정보를 입력받아 책 목록에 추가
        std::cout << static_cast<int>(InputName::DisplayAllBooks) << ". 모든 책 출력" << std::endl; // 현재 책 목록에 있는 모든 책 출력
        std::cout << static_cast<int>(InputName::SearchByTitle) << ". 책 제목으로 검색" << std::endl;
        std::cout << static_cast<int>(InputName::SearchByAuthor) << ". 책 작가로 검색" << std::endl;
        std::cout << static_cast<int>(InputName::DisplayAllStock) << ". 모든 책의 재고 출력" << std::endl;
        std::cout << static_cast<int>(InputName::BorrowByTitle) << ". 책 제목으로 대여" << std::endl;
        std::cout << static_cast<int>(InputName::BorrowByAuthor) << ". 책 작가로 대여" << std::endl;
        std::cout << static_cast<int>(InputName::ReturnByTitle) << ". 책 제목으로 반납" << std::endl;
        std::cout << static_cast<int>(InputName::ReturnByAuthor) << ". 책 작가로 반납" << std::endl;
        std::cout << static_cast<int>(InputName::End) << ". 종료" << std::endl; // 프로그램 종료
        std::cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        std::cin >> choice;

        switch (static_cast<InputName>(choice))
        {
        case InputName::AddBook:
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            {
            std::string title, author;
            std::cout << "책 제목: ";
            std::cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(std::cin, title); // 제목 입력 (공백 포함)
            std::cout << "책 저자: ";
            getline(std::cin, author); // 저자명 입력 (공백 포함)
            bookManager.addBook(title, author); // 입력받은 책 정보를 추가
            borrowManager.initializeStock(bookManager.getBookByTitle(title));
            }
            break;
        case InputName::DisplayAllBooks:
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            bookManager.displayAllBooks();
            break;
        case InputName::SearchByTitle:
            // 현재 BookManager에 저장된 책 목록에서 책 이름으로 책을 찾아 출력합니다.
            {
            std::string title;
            std::cout << "검색하려는 책 제목: ";
            std::cin.ignore();
            getline(std::cin, title);
            bookManager.searchByTitle(title);
            }
            break;
        case InputName::SearchByAuthor:
            // 현재 BookManager에 저장된 책 목록에서 책 작가로 책을 찾아 출력합니다.
            {
            std::string author;
            std::cout << "검색하려는 책 작가: ";
            std::cin.ignore();
            getline(std::cin, author);
            bookManager.searchByAuthor(author);
            }
            break;
        case InputName::DisplayAllStock:
            // 현재 BorrowManager에 저장된 책의 재고를 출력합니다.
            borrowManager.displayStock();
            break;
        case InputName::BorrowByTitle:
            {
                std::string title;
                std::cout << "빌리려는 책 제목: ";
                std::cin.ignore();
                getline(std::cin, title);
                Book* curBook = bookManager.getBookByTitle(title);
                if (nullptr != curBook)
                {
                    borrowManager.brrowBook(curBook->getTitle());
                }
                else
                {
                    std::cout << "책을 찾을 수 없습니다." << std::endl;
                }
            }
            break;
        case InputName::BorrowByAuthor:
            {
                std::string author;
                std::cout << "빌리려는 책의 작가: ";
                std::cin.ignore();
                getline(std::cin, author);
                Book* curBook = bookManager.getBookByAuthor(author);
                if (nullptr != curBook)
                {
                    borrowManager.brrowBook(curBook->getTitle());
                }
                else
                {
                    std::cout << "책을 찾을 수 없습니다." << std::endl;
                }
            }
            break;
        case InputName::ReturnByTitle:
            {
                std::string title;
                std::cout << "반납하려는 책 제목: ";
                std::cin.ignore();
                getline(std::cin, title);
                Book* curBook = bookManager.getBookByTitle(title);
                if (nullptr != curBook)
                {
                    borrowManager.returnBook(curBook->getTitle());
                }
            }
            break;
        case InputName::ReturnByAuthor:
            {
                std::string author;
                std::cout << "반납하려는 책 작가: ";
                std::cin.ignore();
                getline(std::cin, author);
                Book* curBook = bookManager.getBookByAuthor(author);
                if (nullptr != curBook)
                {
                    borrowManager.returnBook(curBook->getTitle());
                }
            }
            break;
        case InputName::End:
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            std::cout << "프로그램을 종료합니다." << std::endl;
            bIsRunning = false; // while 루프 종료
            break;
        default:
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            std::cin.clear(); // 오류 상태 초기화
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 버퍼의 입력 가능한 최대 문자의 수만큼 모든 문자를 무시하고 개행 문자를 만나면 중단
            std::cout << "잘못된 입력입니다. 다시 시도하세요." << std::endl;
            break;
        }
    }
}

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    runLibrary(bookManager, borrowManager);
}