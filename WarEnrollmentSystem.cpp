#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class person {
public:
    string name;
    string lastname;
    string gender;
    long long int personnumber;
    int age;
    float height; // Height in cm

    int HeightPerson = 170; // Minimum height to join (cm)
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    cout << "\nPress Enter to continue...\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void appendperson(vector<person>& Person) {
    do {
        person p;

        cout << "\n🎖️ =========================================\n";
        cout << "✍️       ENTER NEW PERSON INFORMATION\n";
        cout << "🎖️ =========================================\n";

        cout << "\n👤 First Name       : ";
        cin >> p.name;

        cout << "\n👥 Last Name        : ";
        cin >> p.lastname;

        while (true) {
            cout << "\n🚻 Gender (M/F/Other): ";
            cin >> p.gender;

            if (p.gender == "M" || p.gender == "F" || p.gender == "Other") break;
            cout << "❌ Invalid gender. Please enter M, F, or Other.\n";
        }

        while (true) {
            cout << "\n🆔 Person Number    : ";
            cin >> p.personnumber;

            if (cin.fail()) {
                cout << "❌ Ogiltigt personnummer, försök igen!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        while (true) {
            cout << "\n🎂 Age              : ";
            cin >> p.age;

            if (cin.fail()) {
                cout << "❌ Ogiltig ålder, försök igen!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        while (true) {
            cout << "\n📏 Height (in cm)   : ";
            cin >> p.height;

            if (cin.fail()) {
                cout << "❌ Ogiltig längd, försök igen!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

        Person.push_back(p);

        cout << "\n✅ Person \"" << p.name << " " << p.lastname << "\" added successfully!\n";
        cout << "🎖️ =========================================\n";

        string choice;
        cout << "\n➕ Do you want to add another person? (Y/N): ";
        cin >> choice;

        if (choice != "Y" && choice != "y") {
            cout << "\n👋 Returning to menu...\n";
            waitForEnter();
            break;
        }

    } while (true);
}

void ShowAppendPersons(const vector<person>& Person) {
    cout << "\n🪖 ===============================================\n";
    cout << "     WAR ENROLLMENT CHECKLIST 📋\n";
    cout << "🪖 ===============================================\n";

    cout << left << setw(12) << "👤Name"
         << setw(12) << "👥Lastname"
         << setw(6)  << "  🎂Age "
         << setw(10) << " 🚻Gender "
         << setw(10) << " 📏Height "
         << "  📜Status" << endl;

    cout << string(65, '-') << endl;

    for (const auto& i : Person) {
        cout << left << setw(12) << i.name
             << setw(12) << i.lastname
             << setw(6)  << i.age
             << setw(10) << i.gender
             << setw(10) << fixed << setprecision(1) << i.height;

        if (i.height < i.HeightPerson) {
            cout << "❌ Too short to join" << endl;
        } else {
            cout << "✅ Eligible for war" << endl;
        }
    }

    cout << "🪖 ===============================================\n";
    waitForEnter();
}

void ChangeSomethingYouAccidentallyAdded(vector<person>& Person) {
    long long int personnumber;
    bool found = false;

    cout << "\n🔍 Enter the 🆔 Personnumber of the person to update: ";
    cin >> personnumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

    for (auto& p : Person) {
        if (p.personnumber == personnumber) {
            found = true;

            cout << "\n✅ Person found: " << p.name << " " << p.lastname << "\n";

            int choice;
            do {
                clearScreen();
                cout << "\n🪖 ===============================================\n";
                cout << "     WAR ENROLLMENT CHECKLIST 📋\n";
                cout << "🪖 ===============================================\n";

                cout << left << setw(12) << "👤Name"
                     << setw(12) << "👥Lastname"
                     << setw(6)  << "  🎂Age "
                     << setw(10) << " 🚻Gender "
                     << setw(10) << " 📏Height " << endl;

                cout << left << setw(12) << p.name
                     << setw(12) << p.lastname
                     << setw(6)  << p.age
                     << setw(10) << p.gender
                     << setw(10) << fixed << setprecision(1) << p.height;

                cout << "\n🪖 ===============================================\n";

                cout << "\n📋✨ What would you like to change? ✨📋\n";
                cout << "🌟===========================================🌟\n";
                cout << "\n0.  🔚 Exit\n";
                cout << "\n1.  📝 Change Name\n";
                cout << "\n2.  🗂️ Change Lastname\n";
                cout << "\n3.  🚻 Change Gender\n";
                cout << "\n4.  🎂 Change Age\n";
                cout << "\n5.  📏 Change Height\n";
                cout << "🌟===========================================🌟\n";
                cout << "➡️  Enter your choice (0-5): ";

                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline

                switch (choice) {
                    case 0:
                        cout << "\n🔙 Exiting update menu.\n";
                        waitForEnter();
                        return;
                    case 1:
                        cout << "📝 New Name: ";
                        getline(cin, p.name);
                        break;
                    case 2:
                        cout << "📝 New Lastname: ";
                        getline(cin, p.lastname);
                        break;
                    case 3:
                        cout << "📝 New Gender (M/F/Other): ";
                        getline(cin, p.gender);
                        break;
                    case 4:
                        cout << "📝 New Age: ";
                        cin >> p.age;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    case 5:
                        cout << "📝 New Height (cm): ";
                        cin >> p.height;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    default:
                        cout << "❌ Invalid choice, please enter a number between 0 and 5.\n";
                        waitForEnter();
                        break;
                }

                if (choice >= 1 && choice <= 5) {
                    cout << "\n✅ Update completed successfully!\n";
                    waitForEnter();
                }
            } while (true);
        }
    }

    if (!found) {
        cout << "❌ No person found with that personnumber.\n";
        waitForEnter();
    }
}

void RemovePerson(vector<person>& PersonList) {
    long long int targetPersonNumber;
    cout << "\n🗑️ ✍️  Enter the 🆔 Personnumber of the person to remove: ";
    cin >> targetPersonNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;

    for (auto it = PersonList.begin(); it != PersonList.end(); ++it) {
        if (it->personnumber == targetPersonNumber) {
            cout << "⚠️  Are you sure you want to remove " << it->name << " " << it->lastname << "? (y/n): ";
            char confirm;
            while (true) {
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (confirm == 'y' || confirm == 'Y' || confirm == 'n' || confirm == 'N') break;
                cout << "❌ Invalid input. Please enter 'y' or 'n': ";
            }

            if (confirm == 'y' || confirm == 'Y') {
                PersonList.erase(it);
                cout << "✅ Person removed successfully!\n";
            } else {
                cout << "❎ Removal cancelled.\n";
            }

            found = true;
            waitForEnter();
            break;
        }
    }

    if (!found) {
        cout << "❌ No person found with that personnumber.\n";
        waitForEnter();
    }
}

void showMainMenu() {
    cout << "\n🌟===========================================🌟\n";
    cout << "        🧍‍♂️ WAR ENROLLMENT SYSTEM MENU 🧍‍♀️       \n";
    cout << "🌟===========================================🌟\n";
    cout << "\n1.  ➕ Add New Person\n";
    cout << "\n2.  📋 Show All Persons & Permission\n";
    cout << "\n3.  ✏️ Change Person Details\n";
    cout << "\n4.  🗑️ Remove a Person\n";
    cout << "\n5.  ❌ Exit\n";
    cout << "\n🌟===========================================🌟\n";
    cout << "👉 Enter your choice (1-5): ";
}

int main() {
    vector<person> Person;
    int choice;

    while (true) {
        clearScreen();
        showMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                clearScreen();
                appendperson(Person);
                break;
            case 2:
                clearScreen();
                ShowAppendPersons(Person);
                break;
            case 3:
                clearScreen();
                ChangeSomethingYouAccidentallyAdded(Person);
                break;
            case 4:
                clearScreen();
                RemovePerson(Person);
                break;
            case 5:
                cout << "\n👋 Thank you for using the War Enrollment System. Stay safe! 🕊️\n";
                waitForEnter();
                return 0;
            default:
                cout << "❗ Invalid choice. Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                waitForEnter();
        }
    }

    return 0;
}
