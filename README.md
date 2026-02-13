# 📚 Library Management System (C++)

A console-based Library Management System developed using **C++** to manage book records efficiently.
This project demonstrates the use of **Object-Oriented Programming (OOP)**, **STL**, and **File Handling** for persistent data storage.

---

## 🚀 Features

* ➕ Add new books
* 📖 Display all books
* 🔍 Search book by ID
* 📕 Issue book to member
* 📗 Return issued book
* ❌ Delete book record
* 💾 Automatic data save & load using file handling

---

## 🛠️ Tech Stack

* **Language:** C++
* **Concepts Used:**

  * Object-Oriented Programming (Classes & Objects)
  * STL (Vector, Algorithms)
  * File Handling
  * Menu-driven Console UI

---

## 🧱 Project Structure

```
Library-Management-System/
│
├── main.cpp
├── library_data.txt   (Auto-generated)
└── README.md
```

---

## ⚙️ How It Works

1. Books are stored in a **vector container**.
2. Each book has:

   * ID
   * Title
   * Author
   * Issue Status
   * Issued To
3. Data is saved in a text file using **pipe-delimited format**:

```
id|title|author|isIssued|issuedTo
```

4. File loads automatically when program starts.

---

## ▶️ How to Run

### Compile

```bash
g++ main.cpp -o library
```

### Run

```bash
./library
```

*(Windows)*

```bash
library.exe
```

---

## 🖥️ Sample Menu

```
LIBRARY MANAGEMENT SYSTEM
1. Add Book
2. Display All Books
3. Search Book
4. Issue Book
5. Return Book
6. Delete Book
7. Exit
```

---

## 📸 Sample Output

```
ID   Title               Author            Status
--------------------------------------------------
1    C++ Primer          Lippman           Available
2    Clean Code          Robert Martin     Issued
```

---

## 🎯 Learning Outcomes

* Implemented real-world CRUD operations
* Practiced OOP design in C++
* Learned STL container management
* Applied file handling for persistence
* Built menu-driven console applications

---

## 🔮 Future Improvements

* Member management system
* Fine calculation for late returns
* Binary file storage
* GUI version (Qt / C++ GUI)
* Database integration (MySQL)

---

## 👨‍💻 Author

**Soham**
C++ Developer Aspirant 🚀

---

## ⭐ If you like this project

Give it a star on GitHub ⭐ and feel free to fork & improve!

---


