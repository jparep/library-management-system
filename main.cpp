#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    bool is_borrowed;

    // Constructor
    Book(int id, const std::string& title, const std::string& author, bool is_borrowed=false)
        : id(id), title(title), author(author), is_borrowed(is_borrowed) {}

    // Display Method
    void display() const {
        std::cout << "ID: " << id << " | Title: " << title << " | Author: " << author
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