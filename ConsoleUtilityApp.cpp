#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

// -------------------- Bank Account Class --------------------
class BankAccount {
public:
    static int nextId;
    int id;
    string name;
    string lastname;
    float money = 0;

    BankAccount() {
        id = nextId++;
    }
};

int BankAccount::nextId = 1;

// -------------------- ANSI Color Constants --------------------
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string CYAN    = "\033[36m";
const string RESET   = "\033[0m";

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// -------------------- Bible Verses --------------------
void displayRandomVerse() {
    vector<string> verses = {
        "\n📖 Lamentations 3:22-23\n\"The steadfast love of the Lord never ceases; his mercies never come to an end; they are new every morning; great is your faithfulness.\"",
        "\n📖 Joshua 1:9\n\"Be strong and courageous. Do not be afraid; do not be discouraged, for the Lord your God will be with you wherever you go.\"",
        "\n📖 Psalm 121:1-2\n\"I lift up my eyes to the hills—where does my help come from? My help comes from the Lord, the Maker of heaven and earth.\"",
        "\n📖 Hebrews 13:5\n\"Never will I leave you; never will I forsake you.\"",
        "\n📖 Romans 15:13\n\"May the God of hope fill you with all joy and peace as you trust in him...\"",
        "\n📖 1 Peter 5:7\n\"Cast all your anxiety on him because he cares for you.\"",
        "\n📖 John 16:33\n\"In this world you will have trouble. But take heart! I have overcome the world.\"",
        "\n📖 Isaiah 40:31\n\"But those who hope in the Lord will renew their strength...\"",
        "\n📖 Psalm 34:18\n\"The Lord is close to the brokenhearted and saves those who are crushed in spirit.\"",
        "\n📖 Deuteronomy 31:6\n\"Be strong and courageous. Do not be afraid... for the Lord your God goes with you.\""
    };

    srand(static_cast<unsigned int>(time(nullptr)));
    int index = rand() % verses.size();
    cout << CYAN << verses[index] << RESET << "\n";
}

// -------------------- Encryption --------------------
const vector<char> encryptionMap = {
    '9', ':', ';', '<', '=', '>', '?', '0', '1', '2', '3', '4', '5',
    '6', '7', '(', ')', '*', '+', ',', '-', '.', '/', ' ', '!', '"'
};

void encryptor() {
    string input;
    cout << "\n✍️  Enter the name to encrypt (letters only): ";
    cin >> input;

    cout << "\n🔐 Encrypted Output: ";
    for (char character : input) {
        if (isalpha(character)) {
            character = tolower(character);
            int index = character - 'a';
            cout << encryptionMap[index];
        } else {
            cout << character;
        }
    }
    cout << "\n✅ Your name has been encrypted!\n";
    cout << "\n🔁 Press Enter to continue...";
                cin.get();
}

// Helper to print the bank menu header
void printBankMenubar(){
    cout << "\n═══════════════════════════════════════════\n";
    cout << "              🏦 BANK MANAGEMENT             \n";
    cout << "════════════════════════════════════════════\n";
    cout << "\n1. ➕ Add a new account                      \n";
    cout << "\n2. 📋 Show all accounts                      \n";
    cout << "\n3. 💰 Deposit money to an account           \n";
    cout << "\n4. 🔙 Return to main menu                    \n";
    cout << "═══════════════════════════════════════════\n";
}

void addAccount(vector<BankAccount>& bankAccounts) {
    BankAccount b;
    cout << "Enter the first name: ";
    getline(cin, b.name);
    cout << "Enter the last name: ";
    getline(cin, b.lastname);
    bankAccounts.push_back(b);
    cout << GREEN << "✅ Account created with ID #" << b.id << "\n" << RESET;
}

void showAccounts(const vector<BankAccount>& bankAccounts) {
    if (bankAccounts.empty()) {
        cout << YELLOW << "⚠️ No accounts found.\n" << RESET;
    } else {
        cout << "\n📋 List of Accounts:\n";
        cout << left << setw(6) << "ID" << setw(15) << "First Name" << setw(15) << "Last Name" << "Balance\n";
        cout << "--------------------------------------------------\n";
        for (const auto& acc : bankAccounts) {
            cout << left << setw(6) << acc.id << setw(15) << acc.name << setw(15) << acc.lastname
                 << "$" << fixed << setprecision(2) << acc.money << "\n";
        }
    }
}

void depositToAccount(vector<BankAccount>& bankAccounts) {
    if (bankAccounts.empty()) {
        cout << YELLOW << "⚠️ No accounts available.\n" << RESET;
        return;
    }

    int id;
    cout << "Enter account ID: ";
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "❌ Invalid account ID.\n" << RESET;
        return;
    }

    bool found = false;
    for (auto& acc : bankAccounts) {
        if (acc.id == id) {
            found = true;
            double amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;

            if (cin.fail() || amount <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "❌ Invalid amount.\n" << RESET;
            } else {
                acc.money += amount;
                cout << GREEN << "✅ Deposited " << fixed << setprecision(2) << amount
                     << " to account ID #" << acc.id << ". New balance: " << acc.money << "\n" << RESET;
            }
            break;
        }
    }

    if (!found) {
        cout << RED << "❌ Account not found.\n" << RESET;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear buffer
}

void bankMenu(vector<BankAccount>& bankAccounts) {
    while (true) {
        clearScreen();
        printBankMenubar();
        cout << "👉 Choose an option (1-4): ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "❌ Invalid input. Please enter a number (1–4).\n" << RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
            cout << "\n🔁 Press Enter to continue...";
            cin.get();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline

        switch (choice) {
            case 1:
                clearScreen();
                addAccount(bankAccounts);
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
                break;
            case 2:
                clearScreen();
                showAccounts(bankAccounts);
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
                break;
            case 3:
                clearScreen();
                depositToAccount(bankAccounts);
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
                break;
            case 4:
                return;
            default:
                cout << RED << "❌ Invalid option. Please enter 1-4.\n" << RESET;
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
        }
    }
}

// Utility functions
void pause() {
    cout << "\n🔁 Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void addNumber(vector<int>& math) {
    int num;
    cout << "🔢 Enter number: ";
    cin >> num;
    math.push_back(num);
    cout << GREEN << "✅ Number added successfully!\n" << RESET;
}

void deleteNumber(vector<int>& math) {
    int num;
    cout << "🗑️ Enter number to delete: ";
    cin >> num;
    auto it = find(math.begin(), math.end(), num);
    if (it != math.end()) {
        math.erase(it);
        cout << GREEN << "✅ Number deleted.\n" << RESET;
    } else {
        cout << RED << "❌ Number not found.\n" << RESET;
    }
}

void calculateAverage(const vector<int>& math) {
    if (math.empty()) {
        cout << YELLOW << "⚠️ No numbers available to calculate.\n" << RESET;
    } else {
        double avg = accumulate(math.begin(), math.end(), 0.0) / math.size();
        cout << "📊 Average: " << fixed << setprecision(2) << avg << "\n";
    }
}

void showNumbers(const vector<int>& math) {
    if (math.empty()) {
        cout << YELLOW << "⚠️ No numbers to show.\n" << RESET;
    } else {
        cout << "📋 Stored Numbers: ";
        for (int n : math) cout << n << " ";
        cout << "\n";
    }
}

void showSum(const vector<int>& math) {
    if (math.empty()) {
        cout << YELLOW << "⚠️ No numbers to sum.\n" << RESET;
    } else {
        int sum = accumulate(math.begin(), math.end(), 0);
        cout << "➕ Sum: " << sum << "\n";
    }
}

void mathMenu(vector<int>& math) {
    while (true) {
        clearScreen();
        cout << "\n═══════════════════════════════════════════════\n";
        cout << "               📊 MATH UTILITIES MENU            \n";
        cout << "════════════════════════════════════════════════\n";
        cout << "\n1. ➕ Add number\n";
        cout << "\n2. 🗑️ Delete number\n";
        cout << "\n3. 📊 Calculate average\n";
        cout << "\n4. 📋 Show all numbers\n";
        cout << "\n5. ➕ Show sum\n";
        cout << "\n6. 🔙 Return to main menu\n";
        cout << "════════════════════════════════════════════════\n";
        cout << "👉 Choose an option (1-6): ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "❌ Invalid input.\n" << RESET;
            pause();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear newline

        switch (choice) {
            case 1:
                clearScreen();
                addNumber(math);
                pause();
                break;
            case 2:
                clearScreen();
                deleteNumber(math);
                pause();
                break;
            case 3:
                clearScreen();
                calculateAverage(math);
                pause();
                break;
            case 4:
                clearScreen();
                showNumbers(math);
                pause();
                break;
            case 5:
                clearScreen();
                showSum(math);
                pause();
                break;
            case 6:
                return;
            default:
                cout << RED << "❌ Invalid option.\n" << RESET;
                pause();
        }
    }
}

// Show current time
void displayTime() {
    time_t now = time(nullptr);
    cout << "\n🕰️  Current time: " << ctime(&now);
}

// -------------------- Main --------------------
int main() {
    vector<int> math;
    vector<BankAccount> bankAccounts;

    while (true) {
        clearScreen();
        displayTime();
        displayRandomVerse();

        cout << "\n═══════════════════════════════════════════════\n";
        cout << "                 🖥️ MAIN MENU                   \n";
        cout << "═══════════════════════════════════════════════\n";
        cout << "\n1. 📊 Math Utilities\n";
        cout << "\n2. 🏦 Bank Management\n";
        cout << "\n3. 🔐 Name Encryptor\n";
        cout << "\n4. 📖 Show Random Bible Verse\n";
        cout << "\n5. 🚪 Exit\n";
        cout << "═══════════════════════════════════════════════\n";
        cout << "👉 Enter your choice (1-5): ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "❌ Invalid input. Please enter a number (1-5).\n" << RESET;
            cout << "\n🔁 Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

        switch (choice) {
            case 1:
                clearScreen();
                mathMenu(math);
                break;
            case 2:
                clearScreen();
                bankMenu(bankAccounts);
                break;
            case 3:
                clearScreen();
                encryptor();
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
                break;
            case 4:
                clearScreen();
                displayRandomVerse();
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
                break;
            case 5:
                cout << GREEN << "👋 Have a nice day!\n" << RESET;
                return 0;
            default:
                cout << RED << "❌ Invalid option. Please choose 1-5.\n" << RESET;
                cout << "\n🔁 Press Enter to continue...";
                cin.get();
        }
    }

    return 0;
}