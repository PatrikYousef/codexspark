#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// Define the clear screen command depending on the operating system
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

class Payment {
public:
    string firstName;
    string lastName;
    long long int income;
    long long int bills;
    long long int food;
    long long int clothes;
};

void clearScreen() {
    system(CLEAR_COMMAND);
}
void findUsers(const vector<Payment>& users) {
    if (users.empty()) {
        clearScreen();
        cout << "\n📭 No users available to search.\n";
        cout << "\n🔁 Press Enter to return...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    do {
        clearScreen();
        cout << "\n🔍 ➤ Find Users\n";
        cout << "━━━━━━━━━━━━━━━━━\n";
        cout << "Enter name to search (or type 'exit' to return): ";
        string searchName;
        getline(cin, searchName);

        if (searchName == "exit" || searchName == "Exit") break;

        bool found = false;
        int index = 1;

        for (const auto& user : users) {
            if (user.firstName.find(searchName) != string::npos ||
                user.lastName.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\n📋 Matching Users:\n";
                    cout << left << setw(3) << "#"
                         << setw(15) << "First Name"
                         << setw(15) << "Last Name"
                         << setw(12) << "Income"
                         << setw(12) << "Bills"
                         << setw(12) << "Food"
                         << setw(12) << "Clothes" << "\n";
                    cout << string(84, '-') << "\n";
                }

                cout << left << setw(3) << index++
                     << setw(15) << user.firstName
                     << setw(15) << user.lastName
                     << setw(12) << user.income
                     << setw(12) << user.bills
                     << setw(12) << user.food
                     << setw(12) << user.clothes << "\n";

                found = true;
            }
        }

        if (!found) {
            cout << "\n❌ No users match \"" << searchName << "\".\n";
        }

        cout << "\n🔁 Search again? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}

void modifyUser(vector<Payment>& users) {
    if (users.empty()) {
        clearScreen();
        cout << "\n📭 No users available to modify.\n";
        cout << "\n🔁 Press Enter to return...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    do {
        clearScreen();
        cout << "\n✏️ ➤ Modify User Data\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "🔍 Enter First Name of user to modify (or type 'exit' to return): ";
        string nameToModify;
        getline(cin, nameToModify);

        if (nameToModify == "exit" || nameToModify == "Exit") break;

        bool found = false;

        for (auto &user : users) {
            if (user.firstName == nameToModify) {
                found = true;
                cout << "\n👤 Modifying: " << user.firstName << " " << user.lastName << "\n";

                string input;

                // First name
                cout << "New First Name (leave empty to keep \"" << user.firstName << "\"): ";
                getline(cin, input);
                if (!input.empty()) user.firstName = input;

                // Last name
                cout << "New Last Name (leave empty to keep \"" << user.lastName << "\"): ";
                getline(cin, input);
                if (!input.empty()) user.lastName = input;

                // Income
                cout << "New Income (leave empty to keep " << user.income << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        long long val = stoll(input);
                        if (val >= 0) user.income = val;
                    } catch (...) {
                        cout << "❌ Invalid input. Keeping old income.\n";
                    }
                }

                // Bills
                cout << "New Bills (leave empty to keep " << user.bills << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        long long val = stoll(input);
                        if (val >= 0) user.bills = val;
                    } catch (...) {
                        cout << "❌ Invalid input. Keeping old bills.\n";
                    }
                }

                // Food
                cout << "New Food Expenses (leave empty to keep " << user.food << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        long long val = stoll(input);
                        if (val >= 0) user.food = val;
                    } catch (...) {
                        cout << "❌ Invalid input. Keeping old food expenses.\n";
                    }
                }

                // Clothes
                cout << "New Clothes Expenses (leave empty to keep " << user.clothes << "): ";
                getline(cin, input);
                if (!input.empty()) {
                    try {
                        long long val = stoll(input);
                        if (val >= 0) user.clothes = val;
                    } catch (...) {
                        cout << "❌ Invalid input. Keeping old clothes expenses.\n";
                    }
                }

                cout << "\n✅ User updated successfully!\n";
                break;
            }
        }

        if (!found) {
            cout << "❌ No user found with that first name.\n";
        }

        cout << "\n➕ Modify another user? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}


void showMenu() {
    cout << "\n🌟═══════════════════════════════════════🌟\n";
    cout << "       💸 Saving Money for Stuff 💼\n";
    cout << "🌟═══════════════════════════════════════🌟\n";
    cout << "\n1️⃣  ➤ Add a New User 👤\n";
    cout << "\n2️⃣  ➤ Show All Users 📋\n";
    cout << "\n3️⃣  ➤ Calculate Savings 💰\n";
    cout << "\n4️⃣  ➤ Remove a User 🗑️\n";
    cout << "\n5️⃣  ➤ Modify a User ✏️\n";
    cout << "\n6️⃣  ➤ Find Users 🔍\n";
    cout << "\n7️⃣  ➤ Exit Program 🚪\n";
    cout << "-----------------------------------------\n";
    cout << "👉 Enter your choice (1–7): ";
}


void addUser(vector<Payment>& users) {
    do {
        clearScreen();
        Payment user;
        string input;

        cout << "\n🆕 ➤ Add a New User\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━━\n";

        // Validate First Name
        do {
            cout << "👤 First Name: ";
            getline(cin, user.firstName);
            if (user.firstName.empty()) {
                cout << "❌ Error: First name cannot be empty!\n";
            }
        } while (user.firstName.empty());

        // Validate Last Name
        do {
            cout << "👤 Last Name: ";
            getline(cin, user.lastName);
            if (user.lastName.empty()) {
                cout << "❌ Error: Last name cannot be empty!\n";
            }
        } while (user.lastName.empty());

        // Income (must be numeric & >= 0)
        while (true) {
            cout << "💵 Income (numbers only): ";
            getline(cin, input);
            try {
                user.income = stoll(input);
                if (user.income < 0) {
                    cout << "❌ Error: Income cannot be negative!\n";
                    continue;
                }
                break;
            } catch (...) {
                cout << "❌ Error: Please enter a valid number!\n";
            }
        }

        // Bills
        while (true) {
            cout << "🏠 Monthly Bills: ";
            getline(cin, input);
            try {
                user.bills = stoll(input);
                if (user.bills < 0) {
                    cout << "❌ Error: Bills cannot be negative!\n";
                    continue;
                }
                break;
            } catch (...) {
                cout << "❌ Error: Please enter a valid number!\n";
            }
        }

        // Food
        while (true) {
            cout << "🍽️ Monthly Food Expenses: ";
            getline(cin, input);
            try {
                user.food = stoll(input);
                if (user.food < 0) {
                    cout << "❌ Error: Food expenses cannot be negative!\n";
                    continue;
                }
                break;
            } catch (...) {
                cout << "❌ Error: Please enter a valid number!\n";
            }
        }

        // Clothes
        while (true) {
            cout << "👗 Monthly Clothing Expenses: ";
            getline(cin, input);
            try {
                user.clothes = stoll(input);
                if (user.clothes < 0) {
                    cout << "❌ Error: Clothing expenses cannot be negative!\n";
                    continue;
                }
                break;
            } catch (...) {
                cout << "❌ Error: Please enter a valid number!\n";
            }
        }

        // Add user
        users.push_back(user);
        cout << "\n✅ User \"" << user.firstName << " " << user.lastName << "\" added successfully!\n";

        cout << "\n➕ Add another user? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}


void showUsers(const vector<Payment>& users) {
    do {
        clearScreen();

        if (users.empty()) {
            cout << "\n📭 No users to display.\n";
        } else {
            cout << "\n📋 ➤ Registered Users\n";
            cout << "═══════════════════════════════════════════════════════════════════════════════\n";

            cout << left << setw(3) << "#"
                 << setw(15) << "First Name"
                 << setw(15) << "Last Name"
                 << setw(12) << "Income"
                 << setw(12) << "Bills"
                 << setw(12) << "Food"
                 << setw(12) << "Clothes" << "\n";

            cout << string(84, '-') << "\n";

            int index = 1;
            for (const auto& user : users) {
                cout << left << setw(3) << index++
                     << setw(15) << user.firstName
                     << setw(15) << user.lastName
                     << setw(12) << user.income
                     << setw(12) << user.bills
                     << setw(12) << user.food
                     << setw(12) << user.clothes << "\n";
            }

            cout << string(84, '=') << "\n";
            cout << "👥 Total Users: " << users.size() << "\n";
        }

        cout << "\n🔄 Refresh list? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}

void calculateSavings(const vector<Payment>& users) {
    do {
        clearScreen();

        cout << "\n💰 ➤ Calculate Savings\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "🔍 Enter First Name (or type 'exit' to return): ";
        string nameToFind;
        getline(cin, nameToFind);

        if (nameToFind == "exit" || nameToFind == "Exit") {
            break;
        }

        bool found = false;
        for (const auto& user : users) {
            if (user.firstName == nameToFind) {
                long long int savings = user.income - user.bills - user.food - user.clothes;
                cout << "\n💸 " << user.firstName << " " << user.lastName
                     << "'s Estimated Monthly Savings: " << savings << " 💵\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "❌ User not found. Please check the spelling.\n";
        }

        cout << "\n🔁 Calculate for another user? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}

void removeUser(vector<Payment>& users) {
    if (users.empty()) {
        clearScreen();
        cout << "\n📭 No users available to remove.\n";
        cout << "\n🔁 Press Enter to return...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    do {
        clearScreen();

        cout << "\n🗑️ ➤ Remove a User\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━\n";

        cout << "🔍 Enter **First Name** to remove (or type 'exit' to return): ";
        string nameToRemove;
        getline(cin, nameToRemove);

        if (nameToRemove.empty()) {
            cout << "❌ Error: Name cannot be empty!\n";
            cout << "🔁 Press Enter to try again...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (nameToRemove == "exit" || nameToRemove == "Exit") {
            break;
        }

        // Check if user exists
        auto it = remove_if(users.begin(), users.end(), [&](const Payment& user) {
            return user.firstName == nameToRemove;
        });

        if (it != users.end()) {
            users.erase(it, users.end());
            cout << "\n✅ User \"" << nameToRemove << "\" has been removed.\n";
        } else {
            cout << "❌ No user found with that first name.\n";
        }

        cout << "\n➕ Remove another user? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}

int main() {
    vector<Payment> users;
    string input;
    int choice;

    do {
        clearScreen();
        showMenu();
        getline(cin, input);

        try {
            choice = stoi(input);
        } catch (...) {
            choice = -1;
        }

        clearScreen();

        switch (choice) {
            case 1:
                addUser(users);
                break;
            case 2:
                showUsers(users);
                break;
            case 3:
                calculateSavings(users);
                break;
            case 4:
                removeUser(users);
                break;
            case 5:
                modifyUser(users);
                break;
            case 6:
                findUsers(users);
                break;
            case 7:
                cout << "\n👋 Thank you for using Personal Finance Manager!\n";
                cout << "🙏 Stay financially blessed! 💖\n";
                break;
            default:
                cout << "\n❗ Invalid input. Please enter a number between 1 and 7.\n";
                cout << "\n🔁 Press Enter to return to the main menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }

        if (choice != 7) {
            cout << "\n🔁 Press Enter to return to the main menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (choice != 7);

    return 0;
}
