#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <limits>
#include <iomanip>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    cout << "\n🔁 Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


class person {
public:
    string name;
    string lastname;
    int age;
    long long int personnumber;
    float invoice;
    int VAT;
};


void deletePerson(vector<person>& Person) {
    clearScreen();
    do {
        long long int personnumber;
        bool found = false;

        cout << "\n🗑️ ==============================================\n";
        cout << "🔍 ENTER THE 🆔 PERSONAL NUMBER TO DELETE RECORD\n";
        cout << "==============================================\n";
        cout << "🆔 Personal Number: ";
        cin >> personnumber;

        for (auto it = Person.begin(); it != Person.end(); ++it) {
            if (it->personnumber == personnumber) {
                found = true;

                cout << "\n⚠️ Are you sure you want to delete this record?\n";
                cout << "👤 " << it->name << " " << it->lastname << ", Age: " << it->age << "\n";
                cout << "Type 1 to confirm deletion: ";
                
                int confirm;
                cin >> confirm;

                if (confirm == 1) {
                    Person.erase(it);
                    cout << "\n✅ Record deleted successfully.\n";
                } else {
                    cout << "\n❌ Deletion cancelled.\n";
                }

                waitForEnter();
                break; // stop searching after found
            }
        }

        if (!found) {
            cout << "\n❌ No person found with the entered personal number.\n";
            waitForEnter();
        }

        cout << "➕ Delete another person? (y/n): ";
        char cont;
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cont != 'y' && cont != 'Y') {
            break;
        }

        clearScreen();
    } while (true);
}


void appendperson(vector<person>& Person) {
    clearScreen();
    person p;
   do {
  cout << "\n📥═════════════════════════════════════════════════════════════════════📥\n";
cout << "                     ADD NEW PERSON DETAILS FORM                      \n";
cout << "📥═════════════════════════════════════════════════════════════════════📥\n";
cout << endl;


    cout << "👤 First Name        : ";
    cin >> p.name;

    cout << "👥 Last Name         : ";
    cin >> p.lastname;

    while (true) {
        cout << "🆔 Personal Number   : ";
        cin >> p.personnumber;

        if (cin.fail()) {
            cout << "❌ Invalid number. Please enter digits only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    while (true) {
        cout << "🎂 Age               : ";
        cin >> p.age;

        if (cin.fail()) {
            cout << "❌ Invalid age. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    while (true) {
        cout << "📄 Invoice Amount    : ";
        cin >> p.invoice;

        if (cin.fail()) {
            cout << "❌ Invalid invoice amount.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    while (true) {
        cout << "💰 VAT %             : ";
        cin >> p.VAT;

        if (cin.fail()) {
            cout << "❌ Invalid VAT value.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

   
    float vatAmount = p.invoice * (p.VAT / 100);    
    float total = p.invoice + vatAmount;             

    Person.push_back(p);

    cout << "\n✅ Person \"" << p.name << " " << p.lastname << "\" was added successfully!\n";
    cout << "🙏 Thank you! Their information is now stored.\n";
    cout << "===============================================\n";
       // Ask if user wants to add another loan
        cout << "➕ Add another person? (y/n): ";
        char cont;
        cin >> cont;
        if (cont != 'y' && cont != 'Y') {
            break;
        }
           waitForEnter();

    } while (true);
   
}

void showPerson(const vector<person>& Person) {
    clearScreen();
   cout << "\n🌟======================================================================🌟\n";
cout << "🌟                      👥 REGISTERED PEOPLE OVERVIEW                    🌟\n";
cout <<   "🌟======================================================================🌟\n";


    if (Person.empty()) {
        cout << "🚫 No records found. Please add persons first.\n";
    } else {
        cout << endl;
             cout << string(87, '-') << "\n";
        cout << left
             << setw(12) << "👤 Name"
             << setw(12) << "👥 Lastname"
             << setw(15) << " 🆔 Personal"
             << setw(6)  << " 🎂 Age"
             << setw(12) << " 💵 Invoice"
             << setw(6)  << " 💰 VAT%"
             << setw(12) << " 💸 VAT Amt"
             << setw(12) << " 🧾 Total"
             << "\n";

        cout << string(87, '-') << "\n";

        // Rows
        for (const auto& p : Person) {
            float vatAmount = p.invoice * (p.VAT / 100.0f);
            float total = p.invoice + vatAmount;

            cout << left
                 << setw(12) << p.name
                 << setw(12) << p.lastname
                 << setw(15) << p.personnumber
                 << setw(6)  << p.age
                 << setw(12) << fixed << setprecision(2) << p.invoice
                 << setw(6)  << p.VAT
                 << setw(12) << fixed << setprecision(2) << vatAmount
                 << setw(12) << fixed << setprecision(2) << total
                 << "\n";
        }

        cout << string(87, '-') << "\n";
    }
    waitForEnter();
}

void ChangeSomethingYouAccidentallyAdded(vector<person>& Person) {
    clearScreen();
    do {
        long long int personnumber;
        bool found = false;

        cout << "\n🛠️🔧🔨 ==================================================\n";
        cout << "🔍 ENTER THE 🆔 PERSONAL NUMBER TO MODIFY A RECORD 📄\n";
        cout << "=====================================================\n";
        cout << "🆔 Personal Number: ";
        cin >> personnumber;

        for (auto& p : Person) {
            if (p.personnumber == personnumber) {
                found = true;

                // Show found record before editing
                cout << endl << string(87, '-') << "\n";
                cout << left
                     << setw(12) << "👤 Name"
                     << setw(12) << "👥 Lastname"
                     << setw(15) << " 🆔 Personal"
                     << setw(6)  << " 🎂 Age"
                     << setw(12) << " 💵 Invoice"
                     << setw(6)  << " 💰 VAT%"
                     << setw(12) << " 💸 VAT Amt"
                     << setw(12) << " 🧾 Total"
                     << "\n";
                cout << string(87, '-') << "\n";

                float vatAmount = p.invoice * (p.VAT / 100.0f);
                float total = p.invoice + vatAmount;

                cout << left
                     << setw(12) << p.name
                     << setw(12) << p.lastname
                     << setw(15) << p.personnumber
                     << setw(6)  << p.age
                     << setw(12) << fixed << setprecision(2) << p.invoice
                     << setw(6)  << p.VAT
                     << setw(12) << fixed << setprecision(2) << vatAmount
                     << setw(12) << fixed << setprecision(2) << total
                     << "\n";
                cout << string(87, '-') << "\n\n";

                cout << "📌 --------------------------------------------------\n";
                cout << "✏️ What would you like to update?\n";
                cout << "📌 --------------------------------------------------\n";
                cout << "\n1️⃣  👤 First Name\n";
                cout << "\n2️⃣  👥 Last Name\n";
                cout << "\n3️⃣  🎂 Age\n";
                cout << "\n4️⃣  💵 Invoice Amount\n";
                cout << "\n5️⃣  💰 VAT %\n";
                cout << "\n6️⃣  🆔 Personal Number\n";
                cout << "📌 --------------------------------------------------\n";
                cout << "👉 Your choice (1-6): ";

                int choice;
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

                switch (choice) {
                    case 1: {
                        cout << "✍️ Enter New First Name: ";
                        getline(cin, p.name);
                        break;
                    }
                    case 2: {
                        cout << "✍️ Enter New Last Name: ";
                        getline(cin, p.lastname);
                        break;
                    }
                    case 3: {
                        cout << "🎂 Enter New Age: ";
                        while (!(cin >> p.age)) {
                            cout << "❌ Invalid age. Please enter a valid number: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    case 4: {
                        cout << "💵 Enter New Invoice Amount: ";
                        while (!(cin >> p.invoice)) {
                            cout << "❌ Invalid invoice amount. Try again: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    case 5: {
                        cout << "💰 Enter New VAT %: ";
                        while (!(cin >> p.VAT)) {
                            cout << "❌ Invalid VAT value. Try again: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    case 6: {
                        cout << "🆔 Enter New Personal Number: ";
                        while (!(cin >> p.personnumber)) {
                            cout << "❌ Invalid number. Try again: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }
                    default:
                        cout << "❌ Invalid selection. Returning to menu.\n";
                        waitForEnter();
                        return;
                }

                // Show updated record
                cout << "\n✅ Information updated successfully!\n";
                cout << "📎 Updated Record for: " << p.name << " " << p.lastname << "\n";
                cout << string(87, '-') << "\n";
                vatAmount = p.invoice * (p.VAT / 100.0f);
                total = p.invoice + vatAmount;
                cout << left
                     << setw(12) << p.name
                     << setw(12) << p.lastname
                     << setw(15) << p.personnumber
                     << setw(6)  << p.age
                     << setw(12) << fixed << setprecision(2) << p.invoice
                     << setw(6)  << p.VAT
                     << setw(12) << fixed << setprecision(2) << vatAmount
                     << setw(12) << fixed << setprecision(2) << total
                     << "\n";
                cout << string(87, '-') << "\n";

                // Ask if user wants to edit another record
                cout << "➕ Modify another record? (y/n): ";
                char cont;
                cin >> cont;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (cont != 'y' && cont != 'Y') {
                    waitForEnter();
                    return;
                } else {
                    clearScreen();
                    break;  // Break the for loop and restart the do-while to ask for personal number again
                }
            }
        }

        if (!found) {
            cout << "\n❌ No person found with the entered personal number.\n";
            cout << "➕ Try again? (y/n): ";
            char tryAgain;
            cin >> tryAgain;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (tryAgain != 'y' && tryAgain != 'Y') {
                waitForEnter();
                return;
            }
            clearScreen();
        }
    } while (true);
}

void FindPerson(vector<person>& Person){
    clearScreen();
    do {
        long long int personnumber;
        bool found = false;

        cout << "\n🛠️🔧🔨 ==================================================\n";
        cout << "🔍 ENTER THE 🆔 PERSONAL NUMBER TO SEARCH A RECORD 📄\n";
        cout << "=====================================================\n";
        cout << "🆔 Personal Number: ";
        cin >> personnumber;

        for (auto& p : Person) {
            if (p.personnumber == personnumber) {
                found = true;
                cout << endl << string(87, '-') << "\n";
                cout << left
                     << setw(12) << "👤 Name"
                     << setw(12) << "👥 Lastname"
                     << setw(15) << " 🆔 Personal"
                     << setw(6)  << " 🎂 Age"
                     << setw(12) << " 💵 Invoice"
                     << setw(6)  << " 💰 VAT%"
                     << setw(12) << " 💸 VAT Amt"
                     << setw(12) << " 🧾 Total"
                     << "\n";
                cout << string(87, '-') << "\n";

                float vatAmount = p.invoice * (p.VAT / 100.0f);
                float total = p.invoice + vatAmount;

                cout << left
                     << setw(12) << p.name
                     << setw(12) << p.lastname
                     << setw(15) << p.personnumber
                     << setw(6)  << p.age
                     << setw(12) << fixed << setprecision(2) << p.invoice
                     << setw(6)  << p.VAT
                     << setw(12) << fixed << setprecision(2) << vatAmount
                     << setw(12) << fixed << setprecision(2) << total
                     << "\n";
                cout << string(87, '-') << "\n";
                cout << endl;

                break;  // Found the person, break out of the for loop
            }
        }

        if (!found) {
            cout << "\n❌ No person found with the entered personal number.\n";
        }

        // Ask if user wants to search again
        cout << "🔍 Search another person? (y/n): ";
        char tryAgain;
        cin >> tryAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (tryAgain != 'y' && tryAgain != 'Y') {
            waitForEnter();
            return;
        }

        clearScreen();

    } while (true);
}

void showMenu(){
    clearScreen();
    cout << "\n🌟===============================================🌟\n";
    cout << "            🧑‍💼 WELCOME TO PERSON MANAGER\n";
    cout << "🌟===============================================🌟\n";
    cout << "\n1️⃣  ➕ Add New Person\n";
    cout << "\n2️⃣  📋 View All Persons\n";
    cout << "\n3️⃣  ✏️  Modify Existing Person\n";
    cout << "\n4️⃣  🗑️  Delete Person\n";
    cout << "\n5️⃣  🔍 Find a Person\n";
    cout << "\n0️⃣  ❌ Exit Program\n";
    cout << "\n🌟===============================================🌟\n";

}

int main() {
    vector<person> Person;

    while (true) {
        clearScreen();
        showMenu();

        int choice;
        cout << "\n📎 Choose Between (0-5): ";
        cin >> choice;

        if (cin.fail()) {
            cout << "❌ Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            waitForEnter();
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                appendperson(Person);
                break;
            case 2:
                clearScreen();
                showPerson(Person);
                break;
            case 3:
                clearScreen();
                ChangeSomethingYouAccidentallyAdded(Person);
                break;
            case 4:
                deletePerson(Person);
                break;
            case 5:
                FindPerson(Person);
                break;

            case 0:
                clearScreen();
                cout << "\n👋 Exiting... Thank you & God bless you!\n";
                return 0;
            default:
                cout << "❌ Invalid menu option. Please try again.\n";
                waitForEnter();
        }
    }
}
