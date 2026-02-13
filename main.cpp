#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// BOOK CLASS ====================
class Book {
public:
    int bookID;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    // Constructor
    Book(int id, string t, string a) 
        : bookID(id), title(t), author(a), isIssued(false), issuedTo("") {}

    // Display book info
    void display() const {
        cout << setw(5) << bookID 
             << setw(20) << title.substr(0, 18)
             << setw(18) << author.substr(0, 16)
             << setw(12) << (isIssued ? "Issued" : "Available") << endl;
    }
};

// LIBRARY CLASS ====================
class Library {
private:
    vector<Book> books;
    int nextID;
    const string filename = "library_data.txt";

public:
    Library() : nextID(1) {
        loadData();
    }

    ~Library() {
        saveData();
    }

    // 1. ADD BOOK
    void addBook(string title, string author) {
        books.push_back(Book(nextID, title, author));
        cout << "\n✓ Book added with ID: " << nextID << endl;
        nextID++;
        saveData();
    }

    // 2. DISPLAY ALL BOOKS
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "\nNo books in library!" << endl;
            return;
        }

        cout << "\n" << string(60, '=') << endl;
        cout << setw(5) << "ID" << setw(20) << "Title" 
             << setw(18) << "Author" << setw(12) << "Status" << endl;
        cout << string(60, '=') << endl;

        for (const auto& book : books) {
            book.display();
        }
        cout << string(60, '=') << endl;
    }

    // 3. SEARCH BOOK
    bool searchBook(int id) const {
        for (const auto& book : books) {
            if (book.bookID == id) {
                cout << "\n✓ Book Found:" << endl;
                cout << "ID: " << book.bookID << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Status: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << endl;
                return true;
            }
        }
        cout << "\n✗ Book not found!" << endl;
        return false;
    }

    // 4. ISSUE BOOK
    void issueBook(int id, string memberName) {
        for (auto& book : books) {
            if (book.bookID == id) {
                if (book.isIssued) {
                    cout << "\n✗ Book already issued to " << book.issuedTo << endl;
                    return;
                }
                book.isIssued = true;
                book.issuedTo = memberName;
                cout << "\n✓ Book '" << book.title << "' issued to " << memberName << endl;
                saveData();
                return;
            }
        }
        cout << "\n✗ Book not found!" << endl;
    }

    // 5. RETURN BOOK
    void returnBook(int id) {
        for (auto& book : books) {
            if (book.bookID == id) {
                if (!book.isIssued) {
                    cout << "\n✗ Book is not issued!" << endl;
                    return;
                }
                cout << "\n✓ Book '" << book.title << "' returned successfully!" << endl;
                book.isIssued = false;
                book.issuedTo = "";
                saveData();
                return;
            }
        }
        cout << "\n✗ Book not found!" << endl;
    }

    // 6. DELETE BOOK
    void deleteBook(int id) {
        auto it = find_if(books.begin(), books.end(),
                         [id](const Book& b) { return b.bookID == id; });

        if (it != books.end()) {
            cout << "\n✓ Book '" << it->title << "' deleted successfully!" << endl;
            books.erase(it);
            saveData();
            return;
        }
        cout << "\n✗ Book not found!" << endl;
    }

    // 7. SAVE DATA TO FILE
    void saveData() const {
        ofstream file(filename);
        for (const auto& book : books) {
            file << book.bookID << "|"
                 << book.title << "|"
                 << book.author << "|"
                 << book.isIssued << "|"
                 << book.issuedTo << endl;
        }
        file.close();
    }

    // LOAD DATA FROM FILE
    void loadData() {
        ifstream file(filename);
        if (!file.is_open()) {
            return; // File doesn't exist yet, start fresh
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // Parse: id|title|author|isIssued|issuedTo
            size_t pos = 0;
            int id = stoi(line.substr(pos, line.find('|', pos) - pos));
            pos = line.find('|') + 1;

            size_t titleEnd = line.find('|', pos);
            string title = line.substr(pos, titleEnd - pos);
            pos = titleEnd + 1;

            size_t authorEnd = line.find('|', pos);
            string author = line.substr(pos, authorEnd - pos);
            pos = authorEnd + 1;

            bool isIssued = stoi(line.substr(pos, line.find('|', pos) - pos));
            pos = line.find('|') + 1;

            string issuedTo = line.substr(pos);

            Book book(id, title, author);
            if (isIssued) {
                book.isIssued = true;
                book.issuedTo = issuedTo;
            }
            books.push_back(book);

            if (id >= nextID) {
                nextID = id + 1;
            }
        }
        file.close();
    }
};

// MAIN MENU ====================
void displayMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "  LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Add Book\n";
    cout << "2. Display All Books\n";
    cout << "3. Search Book\n";
    cout << "4. Issue Book\n";
    cout << "5. Return Book\n";
    cout << "6. Delete Book\n";
    cout << "7. Exit\n";
    cout << string(50, '=') << endl;
    cout << "Enter choice: ";
}

int main() {
    Library library;
    int choice;
    string title, author, memberName;
    int bookID;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "\n--- Add Book ---" << endl;
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                library.addBook(title, author);
                break;
            }
            case 2:
                library.displayAllBooks();
                break;

            case 3: {
                cout << "\n--- Search Book ---" << endl;
                cout << "Enter book ID: ";
                cin >> bookID;
                library.searchBook(bookID);
                break;
            }
            case 4: {
                cout << "\n--- Issue Book ---" << endl;
                cout << "Enter book ID: ";
                cin >> bookID;
                cin.ignore();
                cout << "Enter member name: ";
                getline(cin, memberName);
                library.issueBook(bookID, memberName);
                break;
            }
            case 5: {
                cout << "\n--- Return Book ---" << endl;
                cout << "Enter book ID: ";
                cin >> bookID;
                library.returnBook(bookID);
                break;
            }
            case 6: {
                cout << "\n--- Delete Book ---" << endl;
                cout << "Enter book ID: ";
                cin >> bookID;
                library.deleteBook(bookID);
                break;
            }
            case 7:
                cout << "\n✓ Thank you! Data saved." << endl;
                return 0;

            default:
                cout << "\n✗ Invalid choice!" << endl;
        }
    }

    return 0;
}
