#include <iostream> // Provides input and output functionality
#include <fstream>  // Handles file operations for reading and writing
#include <vector>   // Enables dynamic array (vector) usage
#include <string>   // Provides support for string data types
#include <algorithm> // Includes functions like find_if for searching collections

using namespace std; // Simplifies code by avoiding std:: prefix for standard library usage

// Book class represents individual books in the library
class Book {
public:
    int id; // Unique identifier for each book
    string title; // Title of the book
    string author; // Author of the book
    bool is_borrowed; // Indicates if the book is currently borrowed

    // Constructor to initialize a book with its details
    Book(int id, const string& title, const string& author, bool is_borrowed = false)
        : id(id), title(title), author(author), is_borrowed(is_borrowed) {}

    // Displays the book's details
    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author
             << " | Status: " << (is_borrowed ? "Borrowed" : "Available") << '\n';
    }
};

// Library class manages the collection of books
class Library {
private:
    vector<Book> books; // Stores the collection of books

    // Loads books from the file into the library
    void loadBooks() {
        ifstream file("books.txt"); // Open file for reading
        if (file) {
            int id;
            string title, author;
            bool is_borrowed;
            // Read each book's details and add to the collection
            while (file >> id >> ws && getline(file, title, '|') && getline(file, author, '|') && file >> is_borrowed) {
                books.emplace_back(id, title, author, is_borrowed);
            }
        }
    }

    // Saves books from the library collection to the file
    void saveBooks() const {
        ofstream file("books.txt"); // Open file for writing
        if (file) {
            // Write each book's details to the file
            for (const auto& book : books) {
                file << book.id << '|' << book.title << '|' << book.author << '|' << book.is_borrowed << '\n';
            }
        }
    }

public:
    // Constructor to initialize the library and load books
    Library() {
        loadBooks();
    }

    // Destructor to save books when the library object is destroyed
    ~Library() {
        saveBooks();
    }

    // Adds a new book to the library
    void addBook(const Book& book) {
        books.push_back(book); // Add the book to the collection
        cout << "Book added successfully." << '\n';
    }

    // Displays all books in the library
    void displayBooks() const {
        if (books.empty()) {
            cout << "No books found in the library." << '\n'; // Notify if no books are available
            return;
        }
        for (const auto& book : books) { // Loop through and display each book
            book.display();
        }
    }

    // Allows a user to borrow a book by ID
    void borrowBook(int book_id) {
        // Search for the book by ID
        auto it = find_if(books.begin(), books.end(), [book_id](const Book& book) { return book.id == book_id; });
        if (it != books.end()) {
            if (!it->is_borrowed) {
                it->is_borrowed = true; // Mark as borrowed
                cout << "You have borrowed the book: " << it->title << '\n';
            } else {
                cout << "Sorry, the book is already borrowed." << '\n';
            }
        } else {
            cout << "Book with ID " << book_id << " not found." << '\n';
        }
    }

    // Allows a user to return a book by ID
    void returnBook(int book_id) {
        // Search for the book by ID
        auto it = find_if(books.begin(), books.end(), [book_id](const Book& book) { return book.id == book_id; });
        if (it != books.end()) {
            if (it->is_borrowed) {
                it->is_borrowed = false; // Mark as returned
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
    Library library; // Create a library object
    int choice; // User's menu choice

    do {
        // Display the menu
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Get user's choice

        switch (choice) {
        case 1: { // Add a new book
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id; // Get book ID
            cin.ignore(); // Ignore newline character
            cout << "Enter Book Title: ";
            getline(cin, title); // Get book title
            cout << "Enter Book Author: ";
            getline(cin, author); // Get book author
            library.addBook(Book(id, title, author));
            break;
        }
        case 2:
            library.displayBooks(); // Display all books
            break;
        case 3: { // Borrow a book
            int id;
            cout << "Enter Book ID to Borrow: ";
            cin >> id; // Get book ID
            library.borrowBook(id);
            break;
        }
        case 4: { // Return a book
            int id;
            cout << "Enter Book ID to Return: ";
            cin >> id; // Get book ID
            library.returnBook(id);
            break;
        }
        case 5:
            cout << "Exiting the system." << '\n'; // Exit message
            break;
        default:
            cout << "Invalid choice. Please try again." << '\n'; // Handle invalid input
        }
    } while (choice != 5); // Repeat until user chooses to exit

    return 0; // End the program
}

/*
Example Input and Output:
1. Add Book:
   Input:
   Enter Book ID: 1
   Enter Book Title: The Great Gatsby
   Enter Book Author: F. Scott Fitzgerald
   Output:
   Book added successfully.

2. Display Books:
   Output:
   ID: 1 | Title: The Great Gatsby | Author: F. Scott Fitzgerald | Status: Available

3. Borrow Book:
   Input:
   Enter Book ID to Borrow: 1
   Output:
   You have borrowed the book: The Great Gatsby

4. Return Book:
   Input:
   Enter Book ID to Return: 1
   Output:
   You have returned the book: The Great Gatsby
*/
