#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structs
struct UserPassword {
    string firstName;
    string lastName;
    string username;
    string password;
    float salary;
    float taxRate;
};

struct Item {
    string name;
    int price;
    int quantity;
};

// Utils
string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// 📦 Add Item
void addItem(vector<Item>& inventory) {
    system("clear");
    Item item;

    cout << "\n📦 ========= Add New Item ========= 📦\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "📄 Item name: ";
    getline(cin, item.name);

    cout << "💰 Price (in currency): ";
    while (!(cin >> item.price) || item.price < 0) {
        cout << "❌ Invalid price. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "📦 Quantity in stock: ";
    while (!(cin >> item.quantity) || item.quantity < 0) {
        cout << "❌ Invalid quantity. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    inventory.push_back(item);

    system("clear");
    cout << "\n✅ ========= Item Added ========= ✅\n\n";

    cout << "------------------------------------------------------\n";
    cout << left << setw(25) << "📄 Name" << setw(15) << "💰 Price" << setw(15) << "📦 Quantity" << "\n";
    cout << "------------------------------------------------------\n";
    cout << left << setw(25) << item.name << setw(15) << item.price << setw(15) << item.quantity << "\n";
    cout << "------------------------------------------------------\n";
}

// 📋 List Items
void listItems(const vector<Item>& inventory) {
    system("clear");
    cout << "\n📋 ========= All Items ========= 📋\n\n";

    if (inventory.empty()) {
        cout << "❌ No items available.\n";
        return;
    }

    cout << "=====================================================\n";
    cout << left << setw(30) << "📄 Item" << setw(15) << "💰 Price" << setw(15) << "📦 Quantity" << "\n";
    cout << "=====================================================\n";

    for (const auto& item : inventory) {
        cout << left << setw(30) << item.name << setw(15) << item.price << setw(15) << item.quantity << "\n";
    }

    cout << "=====================================================\n";
}

// 🧑 Add User
void addUser(vector<UserPassword>& users) {
    system("clear");
    UserPassword user;

    cout << "\n🧑 ========= Add New User ========= 🧑\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "📝 First name: ";
    getline(cin, user.firstName);

    cout << "📝 Last name: ";
    getline(cin, user.lastName);

    cout << "👤 Username: ";
    getline(cin, user.username);

    cout << "🔒 Password: ";
    getline(cin, user.password);

    cout << "💰 Salary: ";
    while (!(cin >> user.salary) || user.salary < 0) {
        cout << "❌ Invalid salary. Enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "📊 Tax rate (0.1 to 1.0): ";
    cin >> user.taxRate;

    users.push_back(user);
    system("clear");
    cout << "\n✅ ========= User Saved ========= ✅\n\n";

    cout << "----------------------------------------------------------\n";
    cout << left << setw(15) << "📝 First Name" << setw(15) << "📝 Last Name" << setw(20) << "👤 Username" << "\n";
    cout << "----------------------------------------------------------\n";
    cout << left << setw(15) << user.firstName << setw(15) << user.lastName << setw(20) << user.username << "\n";
    cout << "----------------------------------------------------------\n";
}

// 🔍 Find User
void findUser(const vector<UserPassword>& users) {
    system("clear");
    cout << "\n🔍 ========= Find User ========= 🔍\n\n";

    if (users.empty()) {
        cout << "❌ No users to search.\n";
        return;
    }

    cout << "🔎 Enter first or last name to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string searchName;
    getline(cin, searchName);
    string searchLower = toLower(searchName);

    bool found = false;

    system("clear");
    cout << "==========================================================================\n";
    cout << left << setw(15) << "📝 First Name" << setw(15) << "📝 Last Name" << setw(20) << "👤 Username"
         << setw(15) << "💰 Salary" << setw(15) << "🧾 Tax Paid" << setw(15) << "💵 Net Salary" << "\n";
    cout << "==========================================================================\n";

    for (const auto& u : users) {
        if (toLower(u.firstName) == searchLower || toLower(u.lastName) == searchLower) {
            float taxPaid = u.salary * u.taxRate;
            float netSalary = u.salary - taxPaid;
            cout << left << setw(15) << u.firstName << setw(15) << u.lastName << setw(20) << u.username
                 << setw(15) << fixed << setprecision(2) << u.salary
                 << setw(15) << taxPaid << setw(15) << netSalary << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "❌ No user found with that name.\n";

    cout << "==========================================================================\n";
}

// 🔑 Login
bool login(const vector<UserPassword>& users, string& loggedInUser) {
    system("clear");

    if (users.empty()) {
        cout << "❌ No registered users. Please create a user first.\n";
        return false;
    }

    cout << "\n🔐 ========= Login ========= 🔐\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string username, password;

    cout << "👤 Username: ";
    getline(cin, username);
    cout << "🔒 Password: ";
    getline(cin, password);

    for (const auto& u : users) {
        if (u.username == username && u.password == password) {
            system("clear");
            cout << "✅ Login successful! Welcome, " << u.username << "!\n";
            loggedInUser = u.username;
            return true;
        }
    }

    cout << "❌ Incorrect username or password.\n";
    return false;
}

// 🛒 Buy Items
void buyItems(vector<Item>& inventory) {
    system("clear");
    if (inventory.empty()) {
        cout << "\n❌ No items available for purchase.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "\n🛒 Enter item name to buy (or type 'exit' to stop): ";
        string itemName;
        getline(cin, itemName);

        if (toLower(itemName) == "exit") break;

        cout << "🔢 Quantity: ";
        int quantityToBuy;
        if (!(cin >> quantityToBuy) || quantityToBuy <= 0) {
            cout << "❌ Invalid quantity. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        bool found = false;

        for (auto& item : inventory) {
            if (toLower(item.name) == toLower(itemName)) {
                found = true;
                if (item.quantity >= quantityToBuy) {
                    item.quantity -= quantityToBuy;
                    int totalPrice = item.price * quantityToBuy;
                    time_t now = time(0);
                    system("clear");
                    cout << "\n✅ ========= Purchase Completed ========= ✅\n\n";
                    cout << "🛍️ You bought " << quantityToBuy << " x " << item.name << " for " << totalPrice << " currency units.\n";
                    cout << "🕒 Time: " << ctime(&now);
                    cout << "📦 Remaining stock: " << item.quantity << "\n";
                    cout << "========================================\n";
                } else {
                    cout << "⚠️ Only " << item.quantity << " left in stock.\n";
                }
                break;
            }
        }

        if (!found) {
            cout << "❌ Item not found.\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// 📊 Show All Users
void showAllUsers(const vector<UserPassword>& users) {
    system("clear");
    if (users.empty()) {
        cout << "❌ No users available.\n";
        return;
    }

    cout << "\n📊 ========= All Users & Salaries ========= 📊\n\n";

    cout << left << setw(15) << "📝 First Name" << setw(15) << "📝 Last Name" << setw(20) << "👤 Username"
         << setw(15) << "💰 Salary" << setw(15) << "🧾 Tax Paid" << setw(15) << "💵 Net Salary" << "\n";
    cout << "====================================================================================\n";

    for (const auto& u : users) {
        float taxPaid = u.salary * u.taxRate;
        float netSalary = u.salary - taxPaid;
        cout << left << setw(15) << u.firstName << setw(15) << u.lastName << setw(20) << u.username
             << setw(15) << fixed << setprecision(2) << u.salary << setw(15) << taxPaid << setw(15) << netSalary << "\n";
    }

    cout << "====================================================================================\n";
}

// 🧠 Main
int main() {
    vector<UserPassword> users;
    vector<Item> inventory;
    string loggedInUser;

    // Start Menu
    while (true) {
        system("clear");
        time_t timestamp = time(nullptr);
        cout << "✨===========================================✨\n";
        cout << "        📦 Inventory Management System\n";
        cout << "🕒 Date: " << ctime(&timestamp);
        cout << "✨===========================================✨\n";

        cout << "\n🔑 1. Login\n";
        cout << "\n🧑 2. Create User\n";
        cout << "\n🚪 3. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "👉 Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            if (login(users, loggedInUser)) break;
        } else if (choice == 2) {
            addUser(users);
        } else if (choice == 3) {
            cout << "\n👋 Exiting program. Goodbye!\n";
            return 0;
        } else {
            cout << "❌ Invalid choice. Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }

    // Main Menu
    while (true) {
        system("clear");
        cout << "===========================================\n";
        cout << "📦 Inventory Management - Main Menu\n";
        cout << "👤 Logged in as: " << loggedInUser << "\n";
        cout << "===========================================\n\n";
        cout << "\n➕ 1. Add Item\n";
        cout << "\n📋 2. List All Items\n";
        cout << "\n🛒 3. Buy Items\n";
        cout << "\n🔍 4. Find User\n";
        cout << "\n📊 5. Show All Users\n";
        cout << "\n🚪 6. Logout\n";
        cout << "-------------------------------------------\n";
        cout << "👉 Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addItem(inventory);
                break;
            case 2:
                listItems(inventory);
                cout << "🔁 Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 3:
                buyItems(inventory);
                cout << "🔁 Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 4:
                findUser(users);
                cout << "🔁 Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 5:
                showAllUsers(users);
                cout << "🔁 Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
            case 6:
                cout << "\n👋 Logging out...\n";
                loggedInUser.clear();
                return 0;
            default:
                cout << "❌ Invalid choice. Press Enter to continue...";
                cin.ignore();
                cin.get();
                break;
        }
    }

    return 0;
}
