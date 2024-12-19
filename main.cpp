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
