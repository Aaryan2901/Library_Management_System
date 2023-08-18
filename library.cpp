#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
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

class LibraryApp : public QWidget {
public:
    LibraryApp(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        connectSignals();
    }

private:
    void setupUI() {
        QVBoxLayout* layout = new QVBoxLayout;

        titleLabel = new QLabel("Library Management System");
        titleLabel->setAlignment(Qt::AlignCenter);

        borrowButton = new QPushButton("Borrow Book");
        returnButton = new QPushButton("Return Book");
        exitButton = new QPushButton("Exit");

        bookTitleLineEdit = new QLineEdit;
        bookTitleLineEdit->setPlaceholderText("Enter book title");

        QHBoxLayout* buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(borrowButton);
        buttonLayout->addWidget(returnButton);

        layout->addWidget(titleLabel);
        layout->addWidget(bookTitleLineEdit);
        layout->addLayout(buttonLayout);
        layout->addWidget(exitButton);

        setLayout(layout);
        setWindowTitle("Library App");
    }

    void connectSignals() {
        connect(borrowButton, &QPushButton::clicked, this, &LibraryApp::borrowBook);
        connect(returnButton, &QPushButton::clicked, this, &LibraryApp::returnBook);
        connect(exitButton, &QPushButton::clicked, this, &LibraryApp::exitApp);
    }

    void borrowBook() {
        QString bookTitle = bookTitleLineEdit->text();
        if (!bookTitle.isEmpty()) {
            Book* foundBook = library.findBook(bookTitle.toStdString());
            if (foundBook) {
                foundBook->borrowBook();
                QMessageBox::information(this, "Borrow Book", "You have successfully borrowed the book.");
            } else {
                QMessageBox::warning(this, "Borrow Book", "Book not available or not found.");
            }
        } else {
            QMessageBox::warning(this, "Borrow Book", "Please enter a valid book title.");
        }
    }

    void returnBook() {
        QString bookTitle = bookTitleLineEdit->text();
        if (!bookTitle.isEmpty()) {
            Book* foundBook = library.findBook(bookTitle.toStdString());
            if (foundBook) {
                foundBook->returnBook();
                QMessageBox::information(this, "Return Book", "Thank you for returning the book.");
            } else {
                QMessageBox::warning(this, "Return Book", "Book not found.");
            }
        } else {
            QMessageBox::warning(this, "Return Book", "Please enter a valid book title.");
        }
    }

    void exitApp() {
        close();
    }

private:
    QLabel* titleLabel;
    QPushButton* borrowButton;
    QPushButton* returnButton;
    QPushButton* exitButton;
    QLineEdit* bookTitleLineEdit;
    Library library;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LibraryApp libraryApp;
    libraryApp.show();

    return app.exec();
}
