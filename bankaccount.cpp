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

// ===== STRUCTS =====
struct BankAccount {
    string bankName;
    string firstName;
    string lastName;
    string accountNumber;
    string CVV;
    string expiryDate;
    string PinCode;
    int balance = 0;
};

struct User {
    string firstName;
    string lastName;
    string username;
    string password;
};



// ===== USER MANAGEMENT =====
void manageUsers(vector<User>& users) {
    User u;
    while (true) {
        clearScreen();
        int choice;
        cout << "\n1. Create Account\n2. Delete Account\n3. Back\nWhat would you like to do? (1-3): ";
        cin >> choice;
        cin.ignore();

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
                        cout << "Account created successfully!" << endl;
                    }
                    break;
                }
                case 2: {
                    clearScreen();
                    string usernameInput;
                    cout << "Enter username to delete: ";
                    getline(cin, usernameInput);

                    auto it = remove_if(users.begin(), users.end(),
                                        [&usernameInput](const User& user) { return user.username == usernameInput; });

                    if (it != users.end()) {
                        users.erase(it, users.end());
                    
                        cout << "Account deleted." << endl;
                    } else {
                        cout << "Account not found." << endl;
                    }
                    break;
                }
                case 3:
                    return;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            clearScreen();
            cout << "An error occurred: " << e.what() << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

// ===== BANK FUNCTIONS =====
void ageCheck() {
    while (true) {
        int age;
        cout << "How old are you? ";
        cin >> age;
        cin.ignore();

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
// ===== FUNCTION DEFINITIONS =====
int generateThreeDigitNumber() {
    return rand() % 900 + 100;  // 100 to 999
}

int pincode() {
    return rand() % 9000 + 1000;  // 1000 to 9999
}
void addAccount(vector<BankAccount>& accounts) {
    try {
        ageCheck();

        BankAccount account;

        clearScreen();
        cout << "🏦═══════════════════════════════════════════════════🏦\n";
        cout << "           🏦 Add New Bank Account 🏦\n";
        cout << "🏦═══════════════════════════════════════════════════🏦\n\n";

        cout << "🏛️  Bank name       : ";
        getline(cin, account.bankName);

        cout << "👤 First name      : ";
        getline(cin, account.firstName);

        cout << "👥 Last name       : ";
        getline(cin, account.lastName);

        // Generate account number as 4 groups of 4-digit numbers separated by dots
        string accountNumber = "";
        for (int i = 0; i < 4; ++i) {
            int part = rand() % 9000 + 1000;  // 1000 to 9999
            accountNumber += to_string(part);
            if (i < 3) accountNumber += ".";
        }
        account.accountNumber = accountNumber;

        // Generate single 3-digit CVV number
        int cvv = generateThreeDigitNumber();
        account.CVV = to_string(cvv);

        // Generate 4-digit PinCode
        int pinCode = pincode();
        account.PinCode = to_string(pinCode);

        cout << "\n🔢 Generated Account Number: " << account.accountNumber << endl;
        cout << "🔐 Generated CVV          : " << account.CVV << endl;
        cout << "🔑 Generated PinCode      : " << account.PinCode << endl;

        cout << "\n📅 Expiry date (MMYY) : ";
        getline(cin, account.expiryDate);

        accounts.push_back(account);

        cout << "\n✅ Account successfully created for "
             << account.firstName << " " << account.lastName << "!\n";
        cout << "🏦═══════════════════════════════════════════════════🏦\n\n";
    }
    catch (const exception& e) {
        clearScreen();
        cout << "❌ An error occurred: " << e.what() << endl;
    }
}

void showAccounts(const vector<BankAccount>& accounts) {
    if (accounts.empty()) {
        cout << "🚫 No accounts to display.\n";
        return;
    }

    cout << "\n🏦═══════════════════════════════════════════════════════════════════════════════════════════════════════════════🏦\n";
    cout << "| No | Bank Name          | Full Name                | Account Number   | Balance    | CVV  | PinCode | Expiry |\n";
    cout << "🏦═════════════════════════════════════════════════════════════════════════════════════════════════════════════════🏦\n";

    for (int i = 0; i < accounts.size(); ++i) {
        cout << "| " << setw(2) << right << i + 1 << " "
             << "| " << setw(18) << left << accounts[i].bankName
             << "| " << setw(24) << left << (accounts[i].firstName + " " + accounts[i].lastName)
             << "| " << setw(17) << left << accounts[i].accountNumber
             << "| 💰 $" << setw(8) << right << accounts[i].balance
             << " | " << setw(4) << left << accounts[i].CVV
             << " | " << setw(7) << left << accounts[i].PinCode
             << " | " << setw(6) << left << accounts[i].expiryDate
             << " |\n";
    }

    cout << "🏦═════════════════════════════════════════════════════════════════════════════════════════════════════════════════🏦\n";
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

void manageFunds(vector<BankAccount>& accounts) {
    clearScreen();

    cout << "\n💰===========================================💰\n";
    cout << "         🏦 WELCOME TO BANKING FUNDS 🏦        \n";
    cout << "💰===========================================💰\n";
    cout << "1️⃣  ➤ Deposit money 💵\n";
    cout << "2️⃣  ➤ Withdraw money 💸\n";
    cout << "💰-------------------------------------------💰\n";

    int choice;
    cout << "👉 Enter your choice (1 or 2): ";
    cin >> choice;
    cin.ignore();

    string enteredPin;
    cout << "🔐 Enter your PinCode: ";
    getline(cin, enteredPin);

    // Find the account by PinCode
    for (auto& account : accounts) {
        if (account.PinCode == enteredPin) {
            int amount;
            cout << (choice == 1 ? "💵 Enter deposit amount: " : "💸 Enter withdrawal amount: ");
            cin >> amount;
            cin.ignore();

            if (amount <= 0) {
                cout << "⚠️ Amount must be greater than zero.\n";
                return;
            }

            if (choice == 1) {
                account.balance += amount;
                cout << "✅ $" << amount << " deposited successfully!\n";
                cout << "📊 New balance: 💰 $" << account.balance << "\n";
            } else if (choice == 2) {
                if (amount <= account.balance) {
                    account.balance -= amount;
                    cout << "✅ $" << amount << " withdrawn successfully!\n";
                    cout << "📊 New balance: 💰 $" << account.balance << "\n";
                } else {
                    cout << "⚠️ Insufficient funds.\n";
                }
            } else {
                cout << "⚠️ Invalid choice.\n";
            }
            return;
        }
    }

    cout << "❌ No account found with that PinCode.\n";
}


// ===== MENUS =====
void showStartupMenu(vector<User>& users) {
    while (true) {
        clearScreen();
        int choice;
        cout << "=== User Menu ===\n1. Manage accounts (Create/Delete User)\n2. Continue to Bank Menu\n3. Exit\nYour choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            manageUsers(users);
        } else if (choice == 2) {
            return;
        } else if (choice == 3) {
            cout << "Exiting program..." << endl;
            exit(0);
        } else {
            cout << "Invalid choice. Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

void showBankingMenu(vector<BankAccount>& accounts, vector<User>& users) {
    while (true) {
        clearScreen();

        cout << "\n💼━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━💼\n";
        cout << "           🏦 BANK ACCOUNT MENU 🏦\n";
        cout << "💼━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━💼\n";
        cout << "\n1️⃣  ➤ 🏦 Add bank account\n";
        cout << "\n2️⃣  ➤ 📄 Show all accounts\n";
        cout << "\n3️⃣  ➤ 🗑️ Delete a bank account\n";
        cout << "\n4️⃣  ➤ 💰 Manage funds\n";
        cout << "\n5️⃣  ➤ 🚪 Exit\n";
        cout << "\n6️⃣  ➤ 🔐 Back to User Menu\n";
        cout << "💼━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━💼\n";

        int choice;
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

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
            default:
                cout << "Invalid option.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

// ===== MAIN =====
int main() {
    vector<BankAccount> accounts;
    vector<User> users;

    while (true) {
        showStartupMenu(users);
        showBankingMenu(accounts, users);
    }

    return 0;
}
