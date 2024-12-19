# Library Management System

A simple command-line Library Management System implemented in C++ to manage books in a library. The system provides functionalities to add books, display all books, borrow books, and return books. It persists data to a text file, ensuring that the library's records are saved between program executions.

## Features

1. **Add Book**: Add a book to the library by providing its ID, title, and author.
2. **Display Books**: View all books in the library along with their status (available or borrowed).
3. **Borrow Book**: Borrow a book using its ID, marking it as borrowed.
4. **Return Book**: Return a borrowed book using its ID, marking it as available.
5. **Persistent Data**: All changes are saved to a file (`books.txt`) for persistence across program runs.

## File Structure

- `books.txt`: Stores the library's book records in the format:
  ```
  <BookID>
  <Title>|<Author>|<IsBorrowed>
  ```
- `library_management_system.cpp`: The main source code for the program.

## How to Use

### Prerequisites
- C++ compiler (e.g., GCC)

### Steps to Run
1. Clone or download this repository.
2. Open a terminal and navigate to the directory containing `library_management_system.cpp`.
3. Compile the program:
   ```bash
   g++ -o library_management_system library_management_system.cpp
   ```
4. Run the compiled executable:
   ```bash
   ./library_management_system
   ```
5. Use the interactive menu to manage the library:
   - Option `1`: Add a new book
   - Option `2`: Display all books
   - Option `3`: Borrow a book
   - Option `4`: Return a book
   - Option `5`: Exit the system

## Example Usage

### Adding a Book
Input:
```
Enter Book ID: 1
Enter Book Title: The Great Gatsby
Enter Book Author: F. Scott Fitzgerald
```
Output:
```
Book added successfully.
```

### Displaying Books
Output:
```
ID: 1 | Title: The Great Gatsby | Author: F. Scott Fitzgerald | Status: Available
```

### Borrowing a Book
Input:
```
Enter Book ID to Borrow: 1
```
Output:
```
You have borrowed the book: The Great Gatsby
```

### Returning a Book
Input:
```
Enter Book ID to Return: 1
```
Output:
```
You have returned the book: The Great Gatsby
```

## Persistent Storage
All book data is stored in `books.txt`. The program automatically loads data from this file on startup and saves changes to it on exit.

## License
This project is open-source and available under the MIT License.

## Contributions
Contributions are welcome! Please feel free to fork the repository, make improvements, and submit a pull request.
