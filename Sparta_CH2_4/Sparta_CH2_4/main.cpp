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
	std::vector<Book> books; // å ��� ����

public:
    // å �߰� �޼���
	void addBook(const std::string& bookTitle, const std::string& bookAuthor)
	{
		books.push_back(Book(bookTitle, bookAuthor)); // push_back ���
		std::cout << "å�� �߰��Ǿ����ϴ�: " << bookTitle << " by " << bookAuthor << std::endl;
	}

    // ��� å ��� �޼���
    void displayAllBooks() const
    {
        if (books.empty())
        {
            std::cout << "���� ��ϵ� å�� �����ϴ�." << std::endl;
            return;
        }

        std::cout << "���� ���� ���:" << std::endl;
        for (size_t i = 0; i < books.size(); ++i) // �Ϲ����� for�� ���
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

    // �˻��� å ���������ϴ� �޼���
    // å ������ ������ ���� ���ٰ� ����
    void searchByTitle(std::string titleName)
    {
        Book* curBook = findBookByTitle(titleName);

        if (nullptr == curBook)
        {
            std::cout << "å�� ã�� ���߽��ϴ�!" << std::endl;
        }
        else
        {
            std::cout << "å�� ã�ҽ��ϴ�!" << std::endl;
            std::cout << "- " << curBook->getTitle() << " by " << curBook->getAuthor() << std::endl;
        }
    }

    // �˻��� å �۰����ϴ� �޼���
    void searchByAuthor(std::string authorName)
    {
        Book* curBook = findBookByAuthor(authorName);

        if (nullptr == curBook)
        {
            std::cout << "å�� ã�� ���߽��ϴ�!" << std::endl;
        }
        else
        {
            std::cout << "å�� ã�ҽ��ϴ�!" << std::endl;
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
            std::cout << "- ����: " << e.first << " å�� ���� ���� " << e.second << "�� �Դϴ�." << std::endl;
        }
    }

    void brrowBook(std::string title)
    {
        if (stock.find(title) == stock.end())
        {
            std::cout << "��� ��Ͽ��� å�� ã�� ���߽��ϴ�!" << std::endl;
            return;
        }

        if (0 >= stock[title])
        {
            std::cout << "��� �������� �ʾ� �뿩�� �Ұ����մϴ�!" << std::endl;
            return;
        }

        while (true)
        {
            std::cout << "�ִ� " << stock[title] << "�� �뿩 �����մϴ�." << std::endl;
            std::cout << "�� ���� �뿩�Ͻðڽ��ϱ�?" << std::endl;

            int input;
            std::cin >> input;

            if (0 <= input && stock[title] >= input)
            {
                stock[title] -= input;

                std::cout << input << "���� �뿩 �ƽ��ϴ�." << std::endl;
                break;
            }
            else
            {
                std::cout << "�߸��� �Է��Դϴ�." << std::endl;
            }
        }
    }

    void returnBook(std::string title)
    {
        if (stock.find(title) == stock.end())
        {
            std::cout << "��� ��Ͽ��� å�� ã�� ���߽��ϴ�!" << std::endl;
            return;
        }

        if (3 <= stock[title])
        {
            std::cout << "�뿩�� ������ �����ϴ�." << std::endl;
            return;
        }

        while (true)
        {
            std::cout << "�ִ� " << 3 - stock[title] << "�� �ݳ� �����մϴ�." << std::endl;
            std::cout << "�� ���� �ݳ��Ͻðڽ��ϱ�?" << std::endl;

            int input;
            std::cin >> input;

            if (0 <= input && 3 - stock[title] >= input)
            {
                stock[title] += input;

                std::cout << input << "���� �ݳ� �ƽ��ϴ�." << std::endl;
                break;
            }
            else
            {
                std::cout << "�߸��� �Է��Դϴ�." << std::endl;
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

// ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
// ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
void runLibrary(BookManager& bookManager, BorrowManager& borrowManager)
{
    bool bIsRunning = true;
    while (bIsRunning) {
        std::cout << "\n������ ���� ���α׷�" << std::endl;
        std::cout << static_cast<int>(InputName::AddBook) << ". å �߰�" << std::endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        std::cout << static_cast<int>(InputName::DisplayAllBooks) << ". ��� å ���" << std::endl; // ���� å ��Ͽ� �ִ� ��� å ���
        std::cout << static_cast<int>(InputName::SearchByTitle) << ". å �������� �˻�" << std::endl;
        std::cout << static_cast<int>(InputName::SearchByAuthor) << ". å �۰��� �˻�" << std::endl;
        std::cout << static_cast<int>(InputName::DisplayAllStock) << ". ��� å�� ��� ���" << std::endl;
        std::cout << static_cast<int>(InputName::BorrowByTitle) << ". å �������� �뿩" << std::endl;
        std::cout << static_cast<int>(InputName::BorrowByAuthor) << ". å �۰��� �뿩" << std::endl;
        std::cout << static_cast<int>(InputName::ReturnByTitle) << ". å �������� �ݳ�" << std::endl;
        std::cout << static_cast<int>(InputName::ReturnByAuthor) << ". å �۰��� �ݳ�" << std::endl;
        std::cout << static_cast<int>(InputName::End) << ". ����" << std::endl; // ���α׷� ����
        std::cout << "����: ";

        int choice; // ������� �޴� ������ ����
        std::cin >> choice;

        switch (static_cast<InputName>(choice))
        {
        case InputName::AddBook:
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            {
            std::string title, author;
            std::cout << "å ����: ";
            std::cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(std::cin, title); // ���� �Է� (���� ����)
            std::cout << "å ����: ";
            getline(std::cin, author); // ���ڸ� �Է� (���� ����)
            bookManager.addBook(title, author); // �Է¹��� å ������ �߰�
            borrowManager.initializeStock(bookManager.getBookByTitle(title));
            }
            break;
        case InputName::DisplayAllBooks:
            // ���� BookManager�� ����� å ����� ����մϴ�.
            bookManager.displayAllBooks();
            break;
        case InputName::SearchByTitle:
            // ���� BookManager�� ����� å ��Ͽ��� å �̸����� å�� ã�� ����մϴ�.
            {
            std::string title;
            std::cout << "�˻��Ϸ��� å ����: ";
            std::cin.ignore();
            getline(std::cin, title);
            bookManager.searchByTitle(title);
            }
            break;
        case InputName::SearchByAuthor:
            // ���� BookManager�� ����� å ��Ͽ��� å �۰��� å�� ã�� ����մϴ�.
            {
            std::string author;
            std::cout << "�˻��Ϸ��� å �۰�: ";
            std::cin.ignore();
            getline(std::cin, author);
            bookManager.searchByAuthor(author);
            }
            break;
        case InputName::DisplayAllStock:
            // ���� BorrowManager�� ����� å�� ��� ����մϴ�.
            borrowManager.displayStock();
            break;
        case InputName::BorrowByTitle:
            {
                std::string title;
                std::cout << "�������� å ����: ";
                std::cin.ignore();
                getline(std::cin, title);
                Book* curBook = bookManager.getBookByTitle(title);
                if (nullptr != curBook)
                {
                    borrowManager.brrowBook(curBook->getTitle());
                }
                else
                {
                    std::cout << "å�� ã�� �� �����ϴ�." << std::endl;
                }
            }
            break;
        case InputName::BorrowByAuthor:
            {
                std::string author;
                std::cout << "�������� å�� �۰�: ";
                std::cin.ignore();
                getline(std::cin, author);
                Book* curBook = bookManager.getBookByAuthor(author);
                if (nullptr != curBook)
                {
                    borrowManager.brrowBook(curBook->getTitle());
                }
                else
                {
                    std::cout << "å�� ã�� �� �����ϴ�." << std::endl;
                }
            }
            break;
        case InputName::ReturnByTitle:
            {
                std::string title;
                std::cout << "�ݳ��Ϸ��� å ����: ";
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
                std::cout << "�ݳ��Ϸ��� å �۰�: ";
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
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            bIsRunning = false; // while ���� ����
            break;
        default:
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            std::cin.clear(); // ���� ���� �ʱ�ȭ
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������ �Է� ������ �ִ� ������ ����ŭ ��� ���ڸ� �����ϰ� ���� ���ڸ� ������ �ߴ�
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << std::endl;
            break;
        }
    }
}

int main() {
    BookManager bookManager;
    BorrowManager borrowManager;

    runLibrary(bookManager, borrowManager);
}