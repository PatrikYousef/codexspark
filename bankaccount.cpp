#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>   

using namespace std;

class Bank {
public:
    string foretag;
    string name;
    string lastname;
    string accountNumber;
    string CVV;
    string PinCode;
    long long personnumber;
    long long telefonnumber;
    float money = 0;
};

class User {
public:
    string name;
    string lastname;
    string username;
    string password;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    cout << "Press Enter to continue...\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover input
    cin.get();
}

void createLogin(vector<User>& users) {
    User u;

    cout << "\n═══════════════════════════════════════════════════════════════\n";
    cout << "       📝   CREATE NEW ACCOUNT   📝\n";
    cout << "═══════════════════════════════════════════════════════════════\n";


    cout << "👤  First name   : ";
    cin >> u.name;

    cout << "👤  Last name    : ";
    cin >> u.lastname;

    cout << "🆔  Username     : ";
    cin >> u.username;

    cout << "🔑  Password     : ";
    cin >> u.password;

    users.push_back(u);

    cout << "═══════════════════════════════════════════════════════════════\n";
    cout << "✅ Account for " << u.name << " " << u.lastname << " created successfully!\n";
    cout << "═══════════════════════════════════════════════════════════════\n\n";
    waitForEnter();
}

void login(vector<User>& users) {
    if (users.empty()) {
        cout << "🚫 No users registered yet. Please create an account first to make the system safe.\n";
        return;
    }

    cout << "\n═══════════════════════════════════════════════════════════════\n";
    cout << "          🔐   LOGIN TO Bank System   🔐\n";
    cout << "═══════════════════════════════════════════════════════════════\n";

    string username, password;
    cout << "🆔  Username : ";
    cin >> username;
    cout << "🔑  Password : ";
    cin >> password;

    for (const auto& u : users) {
        if (u.username == username && u.password == password) {
            cout << "═══════════════════════════════════════════════════════════════\n";
            cout << "✅ Welcome, " << u.name << " " << u.lastname << "! You have access to the bank system. 🏦\n";
            cout << "═══════════════════════════════════════════════════════════════\n\n";
            return;
        }
    }

    cout << "❌ Invalid login. Please try again!\n";
}

void menuForLogins() {
    cout << "\n═══════════════════════════════════════════════════\n";
    cout << "             🔐  PASSWORD MANAGEMENT  🔐\n";
    cout << "═══════════════════════════════════════════════════\n\n";

    cout << "1️⃣  Login                  🔑 Access your account\n\n";
    cout << "2️⃣  Show Registered Users  👥 See all accounts\n\n";

    cout << "═══════════════════════════════════════════════════\n";
}

void showLogin(vector<User>& users) {
    if (users.empty()) {
        cout << "🚫 No users have been registered yet.\n";
        return;
    }

    cout << "\n═══════════════════════════════════════════════════════════════\n";
    cout << "                 👥   REGISTERED USERS   👥\n";
    cout << "═══════════════════════════════════════════════════════════════\n";

    // Table header
    cout << left
         << setw(5)  << "ID"
         << setw(15) << "First Name"
         << setw(15) << "Last Name"
         << setw(15) << "Username"
         << setw(10) << "Password"
         << "\n";
    cout << string(60, '-') << "\n";

    // Table rows
    for (int i = 0; i < users.size(); ++i) {
        string masked(users[i].password.size(), '*'); // mask password
        cout << left
             << setw(5)  << (i + 1)
             << setw(15) << users[i].name
             << setw(15) << users[i].lastname
             << setw(15) << users[i].username
             << setw(10) << masked
             << "\n";
    }

    cout << "═══════════════════════════════════════════════════════════════\n\n";
    waitForEnter();  // Flyttat utanför loopen
}

void switchcaseforlogins(vector<User>& users) {
    bool running = true;
    while (running) {
        clearScreen();
        menuForLogins();
        int choice;
        cout << "🔐 Enter your choice (1-2): ";
        cin >> choice;

        switch (choice) {
        case 1:
            login(users);
            running = false;  // Avsluta login-loopen efter lyckad login
            break;
        case 2:
            showLogin(users);
            break;
        default:
            cin.fail();
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "❌ Invalid input. Please enter a number (1-2): ";
            waitForEnter();
            break;
        }
    }
}

int generateThreeDigitNumber() {
    return rand() % 900 + 100;  // 100 to 999
}

int pincode() {
    return rand() % 9000 + 1000;  // 1000 to 9999
}

void showPerson(const vector<Bank>& banken) {
    if (banken.empty()) {
        cout << "\n❌ No accounts found.\n";
        return;
    }

    cout << "\n=================================================================================================================\n";
    cout << "                                     🏦 COMPLETE BANK ACCOUNT LIST                                               \n";
    cout << "=================================================================================================================\n";

    // Table header
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

    cout << string(115, '-') << "\n"; // separator line

    // Table rows
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

    string accountNumber = "";
    for (int i = 0; i < 4; ++i) {
        int part = rand() % 9000 + 1000;  // 1000 to 9999
        accountNumber += to_string(part);
        if (i < 3) accountNumber += ".";
    }

    b.accountNumber = accountNumber;

    int cvv = generateThreeDigitNumber();
    b.CVV = to_string(cvv);

    int pinCode = pincode();
    b.PinCode = to_string(pinCode);

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
            float addmoney;
            cout << "How much money do you want to add: ";
            cin >> addmoney;
            if (addmoney < 0) {
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
}

void withdrawMoneyWithPersonnum(vector<Bank>& banken) {
    long long personnum;
    cout << "Personnumber: ";
    cin >> personnum;

    bool found = false;
    for (auto& i : banken) {
        if (personnum == i.personnumber) {
            float withdraw;
            cout << "How much money do you want to withdraw: ";
            cin >> withdraw;
            if (withdraw < 0) {
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

    // Find sender and receiver
    for (auto& account : banken) {
        if (account.telefonnumber == myTelephoneNumber)
            sender = &account;
        if (account.telefonnumber == myFriendsTelephoneNumber)
            receiver = &account;
    }

    if (!sender) {
        cout << "❌ Sender's phone number not found.\n";
        return;
    }
    if (!receiver) {
        cout << "❌ Receiver's phone number not found.\n";
        return;
    }

    float amount;
    cout << "How much money do you want to send? ";
    cin >> amount;

    if (amount < 0) {
        cout << "❌ Cannot send negative amount.\n";
        return;
    }
    if (amount > sender->money) {
        cout << "❌ Insufficient balance!\n";
        return;
    }

    sender->money -= amount;
    receiver->money += amount;

    cout << "✅ Successfully sent " << fixed << setprecision(2) << amount 
         << " to " << receiver->name << " (" << receiver->telefonnumber << ")\n";
    cout << "💰 Your new balance: " << fixed << setprecision(2) << sender->money << endl;
}

void SearchForUser(const vector<Bank>& banken) {
    long long int personnum;
    cout << "Enter Personnumber: ";
    if (!(cin >> personnum)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
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
            break; // sluta leta efter fler
        }
    }

    if (!found) {
        cout << "User with person number " << personnum << " not found.\n";
    }

    waitForEnter();
}

void SwitchCasesFormeny(vector<Bank>& banken, vector<User>& users) {

    while (true)
    {
    clearScreen();
    cout << "═════════════════════════════════════════════════════════\n";
    cout << "              🏦  WELCOME TO MY BANK  🏦        \n";
    cout << "════════════════════════════════════════════════════════" << endl;

    time_t now = time(0);
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
    cout << "💰 What do you wanna do (1-7): ";
    cin >> choice;

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
            return;
            
        default:
            clearScreen();
            cout << "❌ Invalid choice. Please try again.\n";
            cin.fail();
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            break;
}  
    }
}

void Körprogramen() {
    vector<Bank> banken;
    vector<User> users;
    switchcaseforlogins(users);
    SwitchCasesFormeny(banken, users);
}

int main() {
    Körprogramen();
}