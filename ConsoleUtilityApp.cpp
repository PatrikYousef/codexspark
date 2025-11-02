#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

// ==================== Datatyper ====================
struct Bank {
    string foretag;
    string name;
    string lastname;
    long long personnumber = 0;
    long long telefonnumber = 0;
    string accountNumber;
    string CVV;
    string PinCode;
    double money = 0.0;
};

struct User {
    string username;
    string password;
};

// ==================== Hjälpfunktioner ====================
int generateThreeDigitNumber() {
    return rand() % 900 + 100; // 100-999
}

int pincode() {
    return rand() % 9000 + 1000; // 1000-9999
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    cout << "\n🔁 Tryck Enter för att fortsätta...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ==================== Bibelverser ====================
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

    int index = rand() % static_cast<int>(verses.size());
    cout << verses[index] << "\n";
}

// ==================== Kryptering ====================
const vector<char> encryptionMap = {
    '9', ':', ';', '<', '=', '>', '?', '0', '1', '2', '3', '4', '5',
    '6', '7', '(', ')', '*', '+', ',', '-', '.', '/', ' ', '!', '"'
    // a..z -> 26 symboler
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

// ==================== Bank: funktioner ====================
void showPerson(const vector<Bank>& banken) {
    if (banken.empty()) {
        cout << "\n❌ No accounts found.\n";
        waitForEnter();
        return;
    }

    cout << "\n=================================================================================================================\n";
    cout << "                                     🏦 COMPLETE BANK ACCOUNT LIST                                               \n";
    cout << "=================================================================================================================\n";

    cout << left << setw(12) << "Företag"
         << setw(12) << "Name"
         << setw(12) << "Lastname"
         << setw(18) << "Personnumber"
         << setw(18) << "Telephone"
         << setw(23) << "Account Number"
         << setw(8)  << "CVV"
         << setw(8)  << "PIN"
         << setw(10) << "Balance"
         << "\n";

    cout << string(115, '-') << "\n";

    for (const auto& i : banken) {
        cout << left
             << setw(12) << i.foretag
             << setw(12) << i.name
             << setw(12) << i.lastname
             << setw(18) << i.personnumber
             << setw(18) << i.telefonnumber
             << setw(23) << i.accountNumber
             << setw(8)  << i.CVV
             << setw(8)  << i.PinCode
             << setw(10) << fixed << setprecision(2) << i.money
             << "\n";
    }

    cout << string(115, '-') << "\n";
    waitForEnter();
}

void addPerson(vector<Bank>& banken) {
    Bank b;

    cout << "👤  Företag: ";
    cin >> b.foretag;

    cout << "🪪  Name: ";
    cin >> b.name;

    cout << "👤 Lastname: ";
    cin >> b.lastname;

    string accountNumber;
    for (int i = 0; i < 4; ++i) {
        int part = rand() % 9000 + 1000;
        accountNumber += to_string(part);
        if (i < 3) accountNumber += ".";
    }
    b.accountNumber = accountNumber;

    b.CVV = to_string(generateThreeDigitNumber());
    b.PinCode = to_string(pincode());

    cout << "📄 Personnumber: ";
    while (!(cin >> b.personnumber)) {
        cout << "❌ Invalid input. Please enter numbers only: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "📞 Telephonenumber: ";
    while (!(cin >> b.telefonnumber)) {
        cout << "❌ Invalid input. Please enter numbers only: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    banken.push_back(b);

    cout << "\n✅ Account created successfully!\n";
    cout << "---------------------------\n";
    cout << "Name: " << b.name << " " << b.lastname << "\n";
    cout << "Personnumber: " << b.personnumber << "\n";
    cout << "Telephonenumber: " << b.telefonnumber << "\n";
    cout << "Account Number: " << b.accountNumber << "\n";
    cout << "CVV: " << b.CVV << "\n";
    cout << "Pin Code: " << b.PinCode << "\n";
    cout << "Balance: " << fixed << setprecision(2) << b.money << "\n";
    cout << "---------------------------\n";
    waitForEnter();
}

void addMoneyWithTelefonnummer(vector<Bank>& banken) {
    long long telefonnumer;
    cout << "Telephonenumber: ";
    cin >> telefonnumer;

    bool found = false;
    for (auto& i : banken) {
        if (telefonnumer == i.telefonnumber) {
            double addmoney;
            cout << "How much money do you want to add: ";
            cin >> addmoney;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "❌ Invalid amount.\n";
            } else if (addmoney < 0) {
                cout << "❌ Cannot add negative amount.\n";
            } else {
                i.money += addmoney;
                cout << "💰 New balance: " << fixed << setprecision(2) << i.money << endl;
            }
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Couldn't find the user's phone number.\n";

    waitForEnter();
}

void withdrawMoneyWithPersonnum(vector<Bank>& banken) {
    long long personnum;
    cout << "Personnumber: ";
    cin >> personnum;

    bool found = false;
    for (auto& i : banken) {
        if (personnum == i.personnumber) {
            double withdraw;
            cout << "How much money do you want to withdraw: ";
            cin >> withdraw;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "❌ Invalid amount.\n";
            } else if (withdraw < 0) {
                cout << "❌ Cannot withdraw negative amount.\n";
            } else if (withdraw > i.money) {
                cout << "❌ Insufficient balance!\n";
            } else {
                i.money -= withdraw;
                cout << "💰 New balance: " << fixed << setprecision(2) << i.money << endl;
            }
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Couldn't find the user's person number.\n";

    waitForEnter();
}

void SwishToAFriend(vector<Bank>& banken) {
    long long myTelephoneNumber;
    long long myFriendsTelephoneNumber;

    cout << "My Telephone Number: ";
    cin >> myTelephoneNumber;

    cout << "My friend's Telephone Number: ";
    cin >> myFriendsTelephoneNumber;

    Bank* sender = nullptr;
    Bank* receiver = nullptr;

    for (auto& account : banken) {
        if (account.telefonnumber == myTelephoneNumber)
            sender = &account;
        if (account.telefonnumber == myFriendsTelephoneNumber)
            receiver = &account;
    }

    if (!sender) {
        cout << "❌ Sender's phone number not found.\n";
        waitForEnter();
        return;
    }
    if (!receiver) {
        cout << "❌ Receiver's phone number not found.\n";
        waitForEnter();
        return;
    }

    double amount;
    cout << "How much money do you want to send? ";
    cin >> amount;

    if (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "❌ Invalid amount.\n";
        waitForEnter();
        return;
    }
    if (amount < 0) {
        cout << "❌ Cannot send negative amount.\n";
        waitForEnter();
        return;
    }
    if (amount > sender->money) {
        cout << "❌ Insufficient balance!\n";
        waitForEnter();
        return;
    }

    sender->money -= amount;
    receiver->money += amount;

    cout << "✅ Successfully sent " << fixed << setprecision(2) << amount
         << " to " << receiver->name << " (" << receiver->telefonnumber << ")\n";
    cout << "💰 Your new balance: " << fixed << setprecision(2) << sender->money << endl;
    waitForEnter();
}

void SearchForUser(const vector<Bank>& banken) {
    long long int personnum;
    cout << "Enter Personnumber: ";
    if (!(cin >> personnum)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
        waitForEnter();
        return;
    }
    bool found = false;

    for (const auto& user : banken) {
        if (personnum == user.personnumber) {
            found = true;
            clearScreen();
            cout << left << setw(10) << "Business"
                 << setw(12) << "Name"
                 << setw(12) << "Lastname"
                 << setw(18) << "Personnumber"
                 << setw(18) << "Telephone"
                 << setw(23) << "Account Number"
                 << setw(8)  << "CVV"
                 << setw(8)  << "PIN"
                 << setw(10) << "Balance"
                 << "\n";

            cout << string(115, '-') << "\n";

            cout << left << setw(10) << user.foretag
                 << setw(12) << user.name
                 << setw(12) << user.lastname
                 << setw(18) << user.personnumber
                 << setw(18) << user.telefonnumber
                 << setw(23) << user.accountNumber
                 << setw(8)  << user.CVV
                 << setw(8)  << user.PinCode
                 << setw(10) << fixed << setprecision(2) << user.money
                 << "\n";

            cout << string(115, '-') << "\n";
            break;
        }
    }

    if (!found) {
        cout << "User with person number " << personnum << " not found.\n";
    }

    waitForEnter();
}

// ==================== Användarhantering ====================
void createLogin(vector<User>& users) {
    User u;
    cout << "📝 Create Login Account\n";
    cout << "Username: ";
    cin >> u.username;
    cout << "Password: ";
    cin >> u.password;

    // enkel koll: inga dubletter
    auto it = find_if(users.begin(), users.end(),
                      [&](const User& x){ return x.username == u.username; });
    if (it != users.end()) {
        cout << "❌ Username already exists.\n";
    } else {
        users.push_back(u);
        cout << "✅ User created.\n";
    }
    waitForEnter();
}


void SwitchCasesFormeny(vector<Bank>& banken, vector<User>& users);

void bankMenu(vector<Bank>& banken, vector<User>& users) {
    SwitchCasesFormeny(banken, users);
}

void SwitchCasesFormeny(vector<Bank>& banken, vector<User>& users) {
    while (true) {
        clearScreen();
        cout << "═════════════════════════════════════════════════════════\n";
        cout << "              🏦  WELCOME TO MY BANK  🏦                 \n";
        cout << "════════════════════════════════════════════════════════" << endl;

        time_t now = time(nullptr);
        tm* localTime = localtime(&now);
        cout << "========================================================" << endl;
        cout << "📅 Date: " << localTime->tm_mday << "/"
            << localTime->tm_mon + 1 << "/"
            << localTime->tm_year + 1900 << "   ⏰ Time: "
            << (localTime->tm_hour < 10 ? "0" : "") << localTime->tm_hour << ":"
            << (localTime->tm_min < 10 ? "0" : "") << localTime->tm_min << "\n";
        cout << "========================================================\n\n";

        cout << "1️⃣  Add Person                   👤 Create a new account\n\n";
        cout << "2️⃣  Add Money                    💰 Deposit money\n\n";
        cout << "3️⃣  Withdraw                     💸 Withdraw money\n\n";
        cout << "4️⃣  Swish Money to a Friend      📱 Transfer money\n\n";
        cout << "5️⃣  Show All Accounts            👥 View all accounts\n\n";
        cout << "6️⃣  Create Login Account         📝 For system login only\n\n";
        cout << "7️⃣  Search for a person's bank   🔍 Search an account\n\n";
        cout << "8️⃣  Exit                         🚪 Leave the bank\n\n";

        cout << "═══════════════════════════════════════════════════════════\n";

        int choice;
        cout << "💰 What do you wanna do (1-8): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input.\n";
            waitForEnter();
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                addPerson(banken);
                break;
            case 2:
                clearScreen();
                addMoneyWithTelefonnummer(banken);
                break;
            case 3:
                clearScreen();
                withdrawMoneyWithPersonnum(banken);
                break;
            case 4:
                clearScreen();
                SwishToAFriend(banken);
                break;
            case 5:
                clearScreen();
                showPerson(banken);
                break;
            case 6:
                clearScreen();
                createLogin(users);
                break;
            case 7:
                clearScreen();
                SearchForUser(banken);
                break;
            case 8:
                clearScreen();
                cout << "Goodbye! Have a nice day. Great job!\n";
                waitForEnter();
                return;
            default:
                clearScreen();
                cout << "❌ Invalid choice. Please try again.\n";
                waitForEnter();
                break;
        }
    }
}

// ==================== Matteverktyg ====================
void pauseScreen() {
    cout << "\n🔁 Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void addNumber(vector<int>& math) {
    int num;
    cout << "🔢 Enter number: ";
    cin >> num;
    if (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "❌ Invalid number.\n";
        return;
    }
    math.push_back(num);
    cout << "✅ Number added successfully!\n";
}

void deleteNumber(vector<int>& math) {
    int num;
    cout << "🗑️ Enter number to delete: ";
    cin >> num;
    if (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "❌ Invalid number.\n";
        return;
    }
    auto it = find(math.begin(), math.end(), num);
    if (it != math.end()) {
        math.erase(it);
        cout << "✅ Number deleted.\n";
    } else {
        cout << "❌ Number not found.\n";
    }
}

void calculateAverage(const vector<int>& math) {
    if (math.empty()) {
        cout << "⚠️ No numbers available to calculate.\n";
    } else {
        double avg = accumulate(math.begin(), math.end(), 0.0) / math.size();
        cout << "📊 Average: " << fixed << setprecision(2) << avg << "\n";
    }
}

void showNumbers(const vector<int>& math) {
    if (math.empty()) {
        cout << "⚠️ No numbers to show.\n";
    } else {
        cout << "📋 Stored Numbers: ";
        for (int n : math) cout << n << " ";
        cout << "\n";
    }
}

void showSum(const vector<int>& math) {
    if (math.empty()) {
        cout << "⚠️ No numbers to sum.\n";
    } else {
        int sum = accumulate(math.begin(), math.end(), 0);
        cout << "➕ Sum: " << sum << "\n";
    }
}

void mathMenu(vector<int>& math) {
    while (true) {
        clearScreen();
        cout << "========================================================" << endl;
        cout << "               📊 MATH UTILITIES MENU            \n";
        cout << "========================================================" << endl;
        cout << "\n1. ➕ Add number\n";
        cout << "\n2. 🗑️ Delete number\n";
        cout << "\n3. 📊 Calculate average\n";
        cout << "\n4. 📋 Show all numbers\n";
        cout << "\n5. ➕ Show sum\n";
        cout << "\n6. 🔙 Return to main menu\n";
        cout << "========================================================" << endl;
        cout << "👉 Choose an option (1-6): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                clearScreen();
                addNumber(math);
                pauseScreen();
                break;
            case 2:
                clearScreen();
                deleteNumber(math);
                pauseScreen();
                break;
            case 3:
                clearScreen();
                calculateAverage(math);
                pauseScreen();
                break;
            case 4:
                clearScreen();
                showNumbers(math);
                pauseScreen();
                break;
            case 5:
                clearScreen();
                showSum(math);
                pauseScreen();
                break;
            case 6:
                return;
            default:
                cout << "❌ Invalid option.\n";
                pauseScreen();
        }
    }
}

// ==================== Tid ====================
void displayTime() {
   time_t now = time(0);
    tm* localTime = localtime(&now);
    cout << "========================================================" << endl;
    cout << "📅 Date: " << localTime->tm_mday << "/"
         << localTime->tm_mon + 1 << "/"
         << localTime->tm_year + 1900 << "   ⏰ Time: "
         << (localTime->tm_hour < 10 ? "0" : "") << localTime->tm_hour << ":"
         << (localTime->tm_min < 10 ? "0" : "") << localTime->tm_min << "\n";
        cout << "========================================================" << endl;
}

void listNumbers() {
    int start;
    cout << "🔢 Ange antal tal att lista: ";
    cin >> start;

    if (start <= 0) {
        cout << "⚠️  Antalet måste vara större än 0.\n";
        return;
    }

    vector<int> numbers;
    for (int i = 1; i <= start; ++i) {
        numbers.push_back(i);
    }

    cout << "\n📋 Dina tal: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << "\n✅ Klart!\n";
}

// ==================== Main ====================
int main() {
    // seed för slump
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> math;
    vector<Bank> banken;
    vector<User> users;

    while (true) {
        clearScreen();
        cout << "========================================================";
        displayRandomVerse();
        displayTime();

        cout << "========================================================" << endl;
        cout << "                 🖥️ MAIN MENU                   \n";
        cout << "========================================================" << endl;
        cout << "\n1. 📊 Math Utilities\n";
        cout << "\n2. 🏦 Bank Management\n";
        cout << "\n3. 🔐 Name Encryptor\n";
        cout << "\n4. 📖 Show Random Bible Verse\n";
        cout << "\n5. 📋 listnumbers  \n";
        cout << "\n6. 🚪 Exit\n";
        cout << "========================================================" << endl;
        cout << "👉 Enter your choice (1-5): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input. Please enter a number (1-5).\n";
            waitForEnter();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                clearScreen();
                mathMenu(math);
                break;
            case 2:
                clearScreen();
                bankMenu(banken, users);  
                break;
            case 3:
                clearScreen();
                encryptor();
                break;
            case 4:
                clearScreen();
                displayRandomVerse();
                waitForEnter();
                break;
            case 5:
                clearScreen();
                listNumbers();
                waitForEnter();
                break;
            case 6:
                cout << "👋 Have a nice day!\n";
                return 0;
            default:
                cout << "❌ Invalid option. Please choose 1-5.\n";
                waitForEnter();
        }
    }

    return 0;
}
