#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <exception>
#include <cstdlib>
#include <limits>
#include <fstream>

using namespace std;

// ===== UTILITY =====
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void safeInputInt(int& value, const string& prompt, int min = numeric_limits<int>::min(), int max = numeric_limits<int>::max()) {
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else {
                cout << "Value must be between " << min << " and " << max << ". Please try again.\n";
            }
        } else {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ===== STRUCTS =====
struct BankAccount {
    string bankName;
    string firstName;
    string lastName;
    string accountNumber;
    string CVV;
    string expiryDate;
    int balance = 0;
};

struct User {
    string firstName;
    string lastName;
    string username;
    string password;
};

// ===== FILE STORAGE =====
void saveUsersToFile(const vector<User>& users, const string& filename = "sparaddata") {
    ofstream MyFile(filename, ios::trunc);
    if (!MyFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    for (const auto& user : users) {
        MyFile << "First Name: " << user.firstName << endl;
        MyFile << "Last Name: " << user.lastName << endl; 
        MyFile << "Username: " << user.username << endl;
        MyFile << "Password: " << user.password << endl;
        MyFile << "------------------------" << endl;
    }
    MyFile.close();
}

// ===== USER MANAGEMENT =====
void manageUsers(vector<User>& users) {
    User u;
    while (true) {
        clearScreen();
        int choice;
        safeInputInt(choice, "\n1. Create Account\n2. Login\n3. Delete Account\n4. Back\nWhat would you like to do? (1-4): ", 1, 4);

        try {
            switch (choice) {
                case 1: {
                    clearScreen();
                    cout << "Enter first name: ";
                    getline(cin, u.firstName);
                    cout << "Enter last name: ";
                    getline(cin, u.lastName);
                    cout << "Enter username: ";
                    getline(cin, u.username);
                    cout << "Enter password: ";
                    getline(cin, u.password);

                    bool alreadyTaken = false;
                    for (const auto& user : users) {
                        if (user.username == u.username) {
                            cout << "Username is already taken!" << endl;
                            alreadyTaken = true;
                            break;
                        }
                    }
                    if (!alreadyTaken) {
                        users.push_back(u);
                        saveUsersToFile(users);
                        cout << "Account created successfully!" << endl;
                    }
                    break;
                }
                case 2:
                    return;
                case 3: {
                    clearScreen();
                    string usernameInput;
                    cout << "Enter username to delete: ";
                    getline(cin, usernameInput);

                    auto it = remove_if(users.begin(), users.end(),
                                        [&usernameInput](const User& user) { return user.username == usernameInput; });

                    if (it != users.end()) {
                        users.erase(it, users.end());
                        saveUsersToFile(users);
                        cout << "Account deleted." << endl;
                    } else {
                        cout << "Account not found." << endl;
                    }
                    break;
                }
                case 4:
                    return;
            }
        } catch (const exception& e) {
            clearScreen();
            cout << "An error occurred: " << e.what() << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

bool login(const vector<User>& users, string& loggedInUser) {
    clearScreen();
    string usernameInput, passwordInput;
    cout << "Enter username: ";
    getline(cin, usernameInput);
    cout << "Enter password: ";
    getline(cin, passwordInput);

    for (const auto& user : users) {
        if (user.username == usernameInput && user.password == passwordInput) {
            loggedInUser = user.username;
            clearScreen();
            cout << "Welcome, " << user.firstName << "!" << endl;
            return true;
        }
    }

    clearScreen();
    cout << "Incorrect username or password. Please try again." << endl;
    return false;
}

// ===== BANK FUNCTIONS =====
void ageCheck() {
    while (true) {
        int age;
        safeInputInt(age, "How old are you? ");

        if (age < 18) {
            clearScreen();
            cout << "You must be 18 years or older to create an account." << endl;
        } else {
            clearScreen();
            cout << "You are eligible to create a bank account." << endl;
            break;
        }
    }
}

// Function to add a new bank account with emojis and nice layout
void addAccount(vector<BankAccount>& accounts) {
    try {
        ageCheck();

        BankAccount account;
        cout << "\n🏦────────── Add New Bank Account ──────────🏦\n";

        cout << "🏛️  Bank name: ";
        getline(cin, account.bankName);

        cout << "👤 First name: ";
        getline(cin, account.firstName);

        cout << "👥 Last name: ";
        getline(cin, account.lastName);

        cout << "🔢 Account number: ";
        getline(cin, account.accountNumber);

        cout << "🔒 CVV: ";
        getline(cin, account.CVV);

        cout << "📅 Expiry date (MMYY): ";
        getline(cin, account.expiryDate);

        accounts.push_back(account);

        cout << "\n✅ Account successfully added for " 
             << account.firstName << " " << account.lastName << "!\n";
        cout << "🏦────────────────────────────────────────────🏦\n\n";
    } catch (const exception& e) {
        clearScreen();
        cout << "❌ An error occurred: " << e.what() << endl;
    }
}

void showAccounts(const vector<BankAccount>& accounts) {
    if (accounts.empty()) {
        cout << "No accounts to display." << endl;
        return;
    }

    cout << "\n==========================================================================================" << endl;
    cout << "| No | Bank Name          | Full Name                | Account Number   | Balance  | CVV  | Expiry |" << endl;
    cout << "==========================================================================================" << endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        cout << "| " << setw(2) << right << i + 1 << " "
             << "| " << setw(18) << left << accounts[i].bankName
             << "| " << setw(24) << left << (accounts[i].firstName + " " + accounts[i].lastName)
             << "| " << setw(17) << left << accounts[i].accountNumber
             << "| $" << setw(8) << right << accounts[i].balance
             << " | " << setw(4) << left << accounts[i].CVV
             << "| " << setw(6) << left << accounts[i].expiryDate
             << "|" << endl;
    }
    cout << "==========================================================================================" << endl;
}

void deleteAccount(vector<BankAccount>& accounts) {
    clearScreen();
    string toDelete;
    cout << "Enter the first name of the account to delete: ";
    getline(cin, toDelete);

    auto it = remove_if(accounts.begin(), accounts.end(),
                        [&toDelete](const BankAccount& account) { return account.firstName == toDelete; });

    if (it != accounts.end()) {
        accounts.erase(it, accounts.end());
        clearScreen();
        cout << "Account for '" << toDelete << "' deleted.\n";
    } else {
        clearScreen();
        cout << "No account found with the first name '" << toDelete << "'.\n";
    }
}

// Function to manage funds with beautiful layout and emojis
void manageFunds(vector<BankAccount>& accounts) {
    clearScreen();
    
    cout << "\n💰===========================================💰\n";
    cout << "         🏦 WELCOME TO BANKING FUNDS 🏦        \n";
    cout << "💰===========================================💰\n";
    cout << "1️⃣  ➤ Deposit money 💵\n";
    cout << "2️⃣  ➤ Withdraw money 💸\n";
    cout << "💰-------------------------------------------💰\n";

    int choice;
    safeInputInt(choice, "👉 Enter your choice (1 or 2): ", 1, 2);

    string name;
    cout << "👤 Enter the *first name* for the account: ";
    getline(cin, name);

    for (auto& account : accounts) {
        if (account.firstName == name) {
            int amount;
            safeInputInt(amount, (choice == 1 ? "💵 Enter deposit amount: " : "💸 Enter withdrawal amount: "));

            if (choice == 1 && amount > 0) {
                account.balance += amount;
                cout << "✅ $" << amount << " deposited successfully!\n";
                cout << "📊 " << name << "'s new balance: 💰 $" << account.balance << "\n";
            } else if (choice == 2 && amount > 0 && amount <= account.balance) {
                account.balance -= amount;
                cout << "✅ $" << amount << " withdrawn successfully!\n";
                cout << "📊 " << name << "'s new balance: 💰 $" << account.balance << "\n";
            } else {
                cout << "⚠️ Invalid amount or insufficient funds.\n";
            }
            return;
        }
    }

    cout << "❌ No account found with the name '" << name << "'.\n";
}


// ===== MENUS =====
void showStartupMenu(vector<User>& users, string& loggedInUser) {
    while (true) {
        clearScreen();
        int choice;
        safeInputInt(choice, "=== User Menu ===\n1. Manage accounts (Create/Delete User)\n2. Login\n3. Exit\nYour choice: ", 1, 3);

        if (choice == 1) {
            manageUsers(users);
        } else if (choice == 2) {
            if (login(users, loggedInUser)) return;
        } else if (choice == 3) {
            cout << "Exiting program..." << endl;
            exit(0);
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

void showBankingMenu(vector<BankAccount>& accounts, vector<User>& users) {
    while (true) {
        clearScreen();
    // Function to display the bank account management menu with emojis

    cout << "\n";
    cout << "💼━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━💼\n";
    cout << "           🏦 BANK ACCOUNT MENU 🏦\n";
    cout << "💼━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━💼\n";
    cout << "\n1️⃣  ➤ 🏦 Add bank account\n";
    cout << "\n2️⃣  ➤ 📄 Show all accounts\n";
    cout << "\n3️⃣  ➤ 🗑️ Delete a bank account\n";
    cout << "\n4️⃣  ➤ 💰 Manage funds\n";
    cout << "\n5️⃣  ➤ 🚪 Exit\n";
    cout << "\n6️⃣  ➤ 🔐 Logout\n";
    cout << "💼━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━💼\n";
    cout << "👉 Please select an option (1-6): ";


        int choice;
        safeInputInt(choice, "Your choice: ", 1, 6);

        switch (choice) {
            case 1:
                addAccount(accounts);
                break;
            case 2:
                showAccounts(accounts);
                break;
            case 3:
                deleteAccount(accounts);
                break;
            case 4:
                manageFunds(accounts);
                break;
            case 5:
                cout << "Exiting program." << endl;
                exit(0);
            case 6:
                return;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

// ===== MAIN =====
int main() {
    vector<BankAccount> accounts;
    vector<User> users;
    string loggedInUser;

    while (true) {
        showStartupMenu(users, loggedInUser);
        showBankingMenu(accounts, users);
    }

    return 0;
}
