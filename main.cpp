#include <iostream> // Provides input and output functionality
#include <fstream>  // Handles file operations for reading and writing
#include <unordered_map> // Optimized storage using unordered_map
#include <string>   // Provides support for string data types
#include <optional> // Includes optional for better search handling
#include <limits>   // Provides numeric_limits for input validation
#include <nlohmann/json.hpp> // JSON library for modern file storage

using namespace std;
using json = nlohmann::json;

// Book class represents individual books in the library
class Book {
public:
    int id;             // Unique identifier for each book
    string title;       // Title of the book
    string author;      // Author of the book
    bool is_borrowed;   // Indicates if the book is currently borrowed

    // Constructor to initialize a book with its details
    Book(int id, const string& title, const string& author, bool is_borrowed = false)
        : id(id), title(title), author(author), is_borrowed(is_borrowed) {}

    // Displays the book's details
    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Status: " << (is_borrowed ? "Borrowed" : "Available") << '\n';
    }

    // Converts a book to a JSON object
    json to_json() const {
        return json{{"id", id}, {"title", title}, {"author", author}, {"is_borrowed", is_borrowed}};
    }

    // Creates a book object from a JSON object
    static Book from_json(const json& j) {
        return Book(j["id"], j["title"], j["author"], j["is_borrowed"]);
    }
};

// Library class manages the collection of books
class Library {
private:
    unordered_map<int, Book> books; // Optimized collection of books using unordered_map
    const string file_name = "books.json"; // File name for storing books

    // Validates numeric input
    int getValidatedInput(const string& prompt) {
        int value;
        cout << prompt;
        while (!(cin >> value)) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

public:
    // Loads books from the JSON file
    void loadBooks() {
        try {
            ifstream file(file_name);
            if (!file.is_open()) throw runtime_error("Failed to open books.json");

            json j_books;
            file >> j_books;
            for (const auto& j_book : j_books) {
                books[j_book["id"]] = Book::from_json(j_book);
            }
        } catch (const exception& e) {
            cerr << "Error loading books: " << e.what() << '\n';
        }
    }

    // Saves books to the JSON file
    void saveBooks() const {
        ofstream file(file_name);
        if (file.is_open()) {
            json j_books = json::array();
            for (const auto& [id, book] : books) {
                j_books.push_back(book.to_json());
            }
            file << j_books.dump(4);
        }
    }

    // Adds a new book to the library
    void addBook() {
        int id = getValidatedInput("Enter Book ID: ");
        cin.ignore();
        string title, author;
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);

        if (books.find(id) != books.end()) {
            cout << "A book with ID " << id << " already exists.\n";
            return;
        }

        books[id] = Book(id, title, author);
        saveBooks();
        cout << "Book '" << title << "' has been added to the library.\n";
    }

    // Displays all books in the library
    void displayBooks() const {
        if (books.empty()) {
            cout << "No books found in the library.\n";
            return;
        }
        for (const auto& [id, book] : books) {
            book.display();
        }
    }

    // Finds a book by ID
    optional<Book*> findBook(int book_id) {
        auto it = books.find(book_id);
        if (it != books.end()) return &it->second;
        return nullopt;
    }

    // Marks a book as borrowed
    void borrowBook() {
        int book_id = getValidatedInput("Enter Book ID to Borrow: ");
        auto book_opt = findBook(book_id);

        if (book_opt) {
            Book* book = *book_opt;
            if (!book->is_borrowed) {
                book->is_borrowed = true;
                saveBooks();
                cout << "You have successfully borrowed '" << book->title << "'.\n";
            } else {
                cout << "The book '" << book->title << "' is already borrowed.\n";
            }
        } else {
            cout << "Book with ID " << book_id << " not found.\n";
        }
    }

    // Marks a book as returned
    void returnBook() {
        int book_id = getValidatedInput("Enter Book ID to Return: ");
        auto book_opt = findBook(book_id);

        if (book_opt) {
            Book* book = *book_opt;
            if (book->is_borrowed) {
                book->is_borrowed = false;
                saveBooks();
                cout << "You have successfully returned '" << book->title << "'.\n";
            } else {
                cout << "The book '" << book->title << "' was not borrowed.\n";
            }
        } else {
            cout << "Book with ID " << book_id << " not found.\n";
        }
    }

    ~Library() {
        saveBooks();
    }
};

// Main function
int main() {
    Library library;
    library.loadBooks();

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Borrow a Book\n";
        cout << "4. Return a Book\n";
        cout << "5. Exit\n";
        choice = library.getValidatedInput("Enter your choice: ");

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.displayBooks();
                break;
            case 3:
                library.borrowBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                cout << "Exiting the Library Management System.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
