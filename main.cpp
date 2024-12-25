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
    std::vector<Book> books;

    void loadbooks() {
        std::ifstream file("books.txt");
        if (file.is_open()) {
            int id;
            std::string title, author;
            bool is_borrowed;
            while (file >> id >> std::ws && std::getline(file, title, '|') && std::getline(file, author, '|') && file >> is_borrowed) {
                books.emplace_back(id, title, author, is_borrowed);
            }
            file.close();
        }
    }

    void savebooks() const {
        std::ofstream file("books.txt");
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.id << '|' << book.title << '|' << book.author << '|' << book.is_borrowed << '\n';
            }
            file.close();
        }
    }

public:
    // Constructor
    Library() {
        loadbooks();
    }
    
    // Destructor
    ~Library() {
        savebooks();
    }

    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added successfully."\n
    }

    void displayBooks() const {
        if (books.empty()) {
            std::cout << "No books found in the libaary." << '\n';
            return;
        }
        for (const auto& book: books) {
            book.display();
        }
    }

    void borrowBook(int book_id) {
        for (auto& book : books) {
            if (book.id == book_id) {
                if (!book.is_borrowed) {
                    book.is_borrowed = true;
                    std::cout << "You have borrowed the book: " << book.title << "\n";
                } else {
                    std::cout << "Sorry, the book is already borrowed.\n";
                }
                return;
            }
        }
        std::cout << "Book with ID " << book_id << " not found.\n";
    }

    void returnBook(int book_id) {
        for (auto& book : books) {
            if (book.id == book_id) {
                if (book.is_borrowed) {
                    book.is_borrowed = false;
                    std::cout << "You have returned the book: " << book.title << "\n";
                } else {
                    std::cout << "The book was not borrowed.\n";
                }
                return;
            }
        }
        std::cout << "Book with ID " << book_id << " not found.\n";
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

