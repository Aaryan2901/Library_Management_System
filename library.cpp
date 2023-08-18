#include <iostream>
#include <vector>
#include <string>

class Book {
public:
    Book(const std::string& title, const std::string& author, const std::string& isbn)
        : title(title), author(author), isbn(isbn), available(true) {}

    std::string getTitle() const { return title; }
    bool isAvailable() const { return available; }
    void borrowBook() { available = false; }
    void returnBook() { available = true; }

private:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;
};

class Library {
public:
    void addBook(const Book& book) { books.push_back(book); }
    Book* findBook(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title && book.isAvailable()) {
                return &book;
            }
        }
        return nullptr;
    }

private:
    std::vector<Book> books;
};

int main() {
    Library library;

    // Adding books to the library
    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "978-0-316-76949-4"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "978-0-06-112008-4"));
    library.addBook(Book("1984", "George Orwell", "978-0-452-28423-4"));

    std::cout << "Welcome to the Library Management System!\n";

    while (true) {
        std::cout << "\n1. Borrow a book\n2. Return a book\n3. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string title;
            std::cout << "Enter the title of the book you want to borrow: ";
            std::cin.ignore();
            std::getline(std::cin, title);

            Book* foundBook = library.findBook(title);
            if (foundBook) {
                foundBook->borrowBook();
                std::cout << "You have successfully borrowed '" << foundBook->getTitle() << "'. Enjoy your reading!\n";
            } else {
                std::cout << "Sorry, the book is either unavailable or not in the library.\n";
            }
        } else if (choice == 2) {
            std::string title;
            std::cout << "Enter the title of the book you want to return: ";
            std::cin.ignore();
            std::getline(std::cin, title);

            Book* foundBook = library.findBook(title);
            if (foundBook) {
                foundBook->returnBook();
                std::cout << "Thank you for returning '" << foundBook->getTitle() << "'.\n";
            } else {
                std::cout << "This book doesn't belong to our library.\n";
            }
        } else if (choice == 3) {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
