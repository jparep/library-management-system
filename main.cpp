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
    Book(int id, const std::string& title), std::string& author, bool is_borrowed=false)
        : id(id), tittle(title), author(author), is_borrowed(is_borrow){}
    {