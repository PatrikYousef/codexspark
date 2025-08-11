#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class Book {
public:
    string name;
    long long int bookCode;
    int total;
    long long int borrowedBy; // 0 if available, personalNumber if borrowed
};

class User {
public:
    string firstName;
    string lastName;
    long long int personalNumber;
    string username;
    string password;
};

void Pause() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ShowDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    cout << "========================================================\n";
    cout << "📅 Date: " << localTime->tm_mday << "/"
         << localTime->tm_mon + 1 << "/"
         << localTime->tm_year + 1900 << "   ⏰ Time: "
         << (localTime->tm_hour < 10 ? "0" : "") << localTime->tm_hour << ":"
         << (localTime->tm_min < 10 ? "0" : "") << localTime->tm_min << "\n";
    cout << "========================================================\n";
}

void ShowRules() {
    clearScreen();
    cout << "\n📜✨ Library Rules (based on our system) ✨📜\n";
    cout << "----------------------------------------------------\n";
    cout << "\n1️⃣ You must enter a valid personal number registered in the system.\n";
    cout << "\n2️⃣ You can only borrow books that are registered in the library.\n";
    cout << "\n3️⃣ If the book is out of stock (0 copies left), it cannot be borrowed.\n";
    cout << "\n4️⃣ The number of copies decreases immediately when you borrow a book.\n";
    cout << "\n5️⃣ Only registered users can borrow books.\n";
    cout << "\n----------------------------------------------------\n";
    Pause();
}

void AppendBooks(vector<Book>& books) {
    clearScreen();
    Book b;
    cout << "\n📚✨ Add a Book ✨📚\n";
    cout << "----------------------------------\n";

    cout << "📖 Book name: ";
    cin >> b.name;

    while (true) {
        cout << "🔢 Book code (number): ";
        cin >> b.bookCode;
        if (cin.fail()) {
            cout << "❌ Invalid number, please try again! 🚫\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    while (true) {
        cout << "🔢 Total copies (number): ";
        cin >> b.total;
        if (cin.fail() || b.total < 0) {
            cout << "❌ Invalid number, please try again! 🚫\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    b.borrowedBy = 0; // ✅ initialize
    books.push_back(b);
    cout << "✅ The book has been added! 🎉📚\n";
    Pause();
}

void AddUserAccess(vector<User>& users) {
    clearScreen();
    User u;
    cout << "\n👤✨ Add a User ✨👤\n";
    cout << "----------------------------------\n";

    while (true) {
        cout << "🧑 First name: ";
        getline(cin, u.firstName);
        if (!u.firstName.empty()) break;
        cout << "❌ First name cannot be empty.\n";
    }

    while (true) {
        cout << "👨 Last name: ";
        getline(cin, u.lastName);
        if (!u.lastName.empty()) break;
        cout << "❌ Last name cannot be empty.\n";
    }

    while (true) {
        cout << "🆔 Personal number (number): ";
        cin >> u.personalNumber;
        if (cin.fail() || u.personalNumber <= 0) {
            cout << "❌ Invalid personal number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    while (true) {
        cout << "🗝️ Username: ";
        getline(cin, u.username);
        if (!u.username.empty()) break;
        cout << "❌ Username cannot be empty.\n";
    }

    while (true) {
        cout << "🔒 Password: ";
        getline(cin, u.password);
        if (!u.password.empty()) break;
        cout << "❌ Password cannot be empty.\n";
    }

    users.push_back(u);
    cout << "✅ The user has been added! 🎉👤\n";
    Pause();
}

void ShowBooks(const vector<Book>& books) {
    clearScreen();
    if (books.empty()) {
        cout << "\n📚⚠️ No books registered yet.\n";
        Pause();
        return;
    }
    cout << "\n📚✨ List of Books ✨📚\n";
    cout << "------------------------------------------------\n";
    cout << left << setw(30) << "📖 Name"
         << setw(20) << "🔢 Book Code"
         << setw(10) << "📚 Total" << "\n";
    cout << "------------------------------------------------\n";
    for (const auto& i : books) {
        cout << left << setw(30) << i.name
             << setw(20) << i.bookCode
             << setw(10) << i.total << "\n";
    }
    cout << "------------------------------------------------\n";
    Pause();
}

void ShowUsers(const vector<User>& users) {
    clearScreen();
    if (users.empty()) {
        cout << "\n👤⚠️ No users registered yet.\n";
        Pause();
        return;
    }
    cout << "\n👤✨ List of Users ✨👤\n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << left << setw(15) << "🧑 First Name"
         << setw(15) << "👨 Last Name"
         << setw(20) << "🆔 Personal Number"
         << setw(20) << "🗝️ Username"
         << setw(15) << "🔒 Password" << "\n";
    cout << "-------------------------------------------------------------------------------\n";
    for (const auto& i : users) {
        cout << left << setw(15) << i.firstName
             << setw(15) << i.lastName
             << setw(20) << i.personalNumber
             << setw(20) << i.username
             << setw(15) << i.password << "\n";
    }
    cout << "-------------------------------------------------------------------------------\n";
    Pause();
}

void BorrowBook(vector<User>& users, vector<Book>& books) {
    clearScreen();
    cout << "\n📚✨ Borrow a Book ✨📚\n";
    cout << "----------------------------------\n";

    long long int personalNumber;
    cout << "🆔 Enter your personal number: ";
    cin >> personalNumber;

    bool foundUser = false;
    for (auto& u : users) {
        if (u.personalNumber == personalNumber) {
            foundUser = true;
            long long int bookCode;
            cout << "🔢 Enter the book code: ";
            cin >> bookCode;

            bool foundBook = false;
            for (auto& b : books) {
                if (b.bookCode == bookCode) {
                    foundBook = true;
                    cout << "\n----------------------------------\n";
                    if (b.total > 0 && b.borrowedBy == 0) {
                        b.total--;
                        b.borrowedBy = personalNumber; // ✅ track borrower
                        cout << "✅ The book \"" << b.name
                             << "\" has been borrowed by 👤 " << u.firstName << " " << u.lastName << ".\n";
                        cout << "📚 Copies left: " << b.total << "\n";
                    } else {
                        cout << "❌ Sorry, this book is not available.\n";
                    }
                    cout << "----------------------------------\n\n";
                    break;
                }
            }
            if (!foundBook) {
                cout << "\n❌ We don't have the book you're looking for.\n\n";
            }
            break;
        }
    }

    if (!foundUser) {
        cout << "\n❌ We don't have a user with that personal number.\n\n";
    }
    Pause();
}

void ShowBorrowBook(vector<User>& users, vector<Book>& books) {
    long long int personalNumber;
    cout << "🆔 Enter your personal number: ";
    cin >> personalNumber;

    bool userFound = false;
    for (const auto& user : users) {
        if (user.personalNumber == personalNumber) {
            userFound = true;
            cout << "📚 Books borrowed by " << user.firstName << ":\n";
            bool hasBorrowedBooks = false;
            for (const auto& book : books) {
                if (book.borrowedBy == personalNumber) {
                    cout << " - " << book.name << "\n";
                    hasBorrowedBooks = true;
                }
            }
            if (!hasBorrowedBooks) {
                cout << "No books borrowed.\n";
            }
            break;
        }
    }
    if (!userFound) {
        cout << "User not found. Please check the personal number.\n";
    }
    Pause();
}

void FindUser(const vector<User>& users) {
    clearScreen();
    cout << "========================================================\n";
    cout << "🔍  SEARCH FOR USER\n";
    cout << "========================================================\n";
    long long int personalNumber;
    cout << "🆔 Enter your personal number: ";
    cin >> personalNumber;

    bool found = false;
    for (const auto& u : users) {
        if (personalNumber == u.personalNumber) {
            clearScreen();
            ShowDateTime();
            cout << "========================================================\n";
            cout << "✅  USER FOUND!\n";
            cout << "========================================================\n";
            cout << "👤 Name:         " << u.firstName << " " << u.lastName << "\n";
            cout << "📛 Username:     " << u.username << "\n";
            cout << "🔑 Password:     " << u.password << "\n";
            cout << "🆔 Personal No.: " << u.personalNumber << "\n";
            cout << "========================================================\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\n❌ No user was found with that personal number.\n";
    }
    Pause();
}


void FindBook(vector<Book>& books) {
    long long int code;
    cout << "🔍 Enter Book Code: ";
    cin >> code;

    clearScreen();
    cout << "📚 ========================================= 📚\n";
    cout << "               📖 Book Search Result\n";
    cout << "📚 ========================================= 📚\n";

    bool found = false;
    for (const auto& i : books) {
        if (code == i.bookCode) {
            cout << left << setw(20) << "📌 Book Name"   << ": " << i.name << "\n";
            cout << left << setw(20) << "🆔 Book Code"   << ": " << i.bookCode << "\n";
            cout << left << setw(20) << "📦 Copies Left" << ": " << i.total << "\n";
            cout << "-------------------------------------------\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "❌ Book with code " << code << " not found.\n";
    }

    cout << "📚 ========================================= 📚\n";
}



void ShowMenu() {
    clearScreen();
    ShowDateTime();
    cout << "📚  WELCOME TO THE LIBRARY SYSTEM  📚\n";
    cout << "========================================================\n\n";
    cout << "1. ➕ Add a book\n";
    cout << "\n2. 📖 Show books\n";
    cout << "\n3. ➕ Add a user\n";
    cout << "\n4. 👥 Show users\n";
    cout << "\n5. 📚 Borrow a book\n";
    cout << "\n6. 📜 Show library rules\n";
    cout << "\n7. 🔍 Search for a book\n";        // New option here
    cout << "\n8. 🔍 Search for a user\n";         // Shifted from 7 to 8
    cout << "\n9. 📚 Show borrowed books\n";       // Shifted from 8 to 9
    cout << "\n10. ❌ Exit\n";                     // Shifted from 9 to 10
    cout << "\n========================================================\n";
    cout << "📚 Enter your choice (1-10): ";
}

int main() {
    vector<Book> books;
    vector<User> users;
    int choice;
    ShowRules();
    do {
        ShowMenu();
        cin >> choice;
        if (cin.fail()) {
            cout << "❌ Invalid choice.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: AppendBooks(books); break;
            case 2: ShowBooks(books); break;
            case 3: AddUserAccess(users); break;
            case 4: ShowUsers(users); break;
            case 5: BorrowBook(users, books); break;
            case 6: ShowRules(); break;
            case 7: FindBook(books); break;          // Search Book
            case 8: FindUser(users); break;          // Search User
            case 9: ShowBorrowBook(users, books); break;
            case 10: cout << "\n👋 Goodbye!\n"; break;
            default: cout << "❌ Invalid choice.\n"; Pause();
        }
    } while (choice != 10);
    return 0;
}
