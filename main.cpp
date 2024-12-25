#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool is_borrowed;

    Book(int id, const string& title, const string& author, bool is_borrowed = false)
        : id(id), title(title), author(author), is_borrowed(is_borrowed) {}

    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Status: " << (is_borrowed ? "Borrowed" : "Available") << '\n';
    }
};

class Library {
private:
    vector<Book> books;

    void loadBooks() {
        ifstream file("books.txt");
        if (file) {
            int id;
            string title, author;
            bool is_borrowed;
            while (file >> id >> ws && getline(file, title, '|') && getline(file, author, '|') && file >> is_borrowed) {
                books.emplace_back(id, title, author, is_borrowed);
            }
        }
    }

    void saveBooks() const {
        ofstream file("books.txt");
        if (file) {
            for (const auto& book : books) {
                file << book.id << '|' << book.title << '|' << book.author << '|' << book.is_borrowed << '\n';
            }
        }
    }

public:
    Library() {
        loadBooks();
    }

    ~Library() {
        saveBooks();
    }

    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book added successfully." << '\n';
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books found in the library." << '\n';
            return;
        }
        for (const auto& book : books) {
            book.display();
        }
    }

    void borrowBook(int book_id) {
        auto it = find_if(books.begin(), books.end(), [book_id](const Book& book) { return book.id == book_id; });
        if (it != books.end()) {
            if (!it->is_borrowed) {
                it->is_borrowed = true;
                cout << "You have borrowed the book: " << it->title << '\n';
            } else {
                cout << "Sorry, the book is already borrowed." << '\n';
            }
        } else {
            cout << "Book with ID " << book_id << " not found." << '\n';
        }
    }

    void returnBook(int book_id) {
        auto it = find_if(books.begin(), books.end(), [book_id](const Book& book) { return book.id == book_id; });
        if (it != books.end()) {
            if (it->is_borrowed) {
                it->is_borrowed = false;
                cout << "You have returned the book: " << it->title << '\n';
            } else {
                cout << "The book was not borrowed." << '\n';
            }
        } else {
            cout << "Book with ID " << book_id << " not found." << '\n';
        }
    }
};


int main() {
    Library library;
    int choice;


    do {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Display Books\n";
        std::cout << "3. Borrow Book\n";
        std::cout << "4. Return Book\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            std::string title, author;
            std::cout << "Enter Book ID: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter Book Title: ";
            std::getline(std::cin, title);
            std::cout << "Enter Book Author: ";
            std::getline(std::cin, author);
            library.addBook(Book(id, title, author));
            break;
        }
        case 2:
            library.displayBooks();
            break;
        case 3: {
            int id;
            std::cout << "Enter Book ID to Borrow: ";
            std::cin >> id;
            library.borrowBook(id);
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter Book ID to Return: ";
            std::cin >> id;
            library.returnBook(id);
            break;
        }
        case 5:
            std::cout << "Exiting the system.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

