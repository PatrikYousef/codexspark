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
            cout << "Type 1 to confirm: ";
            int confirm;
            cin >> confirm;
            

            if (confirm == 1) {
                Person.erase(it);
                cout << "\n✅ Record deleted successfully.\n";
            } else {
                cout << "\n❌ Deletion cancelled.\n";
            }

            waitForEnter();
            return;
        }
    }

    if (!found) {
        cout << "\n❌ No person found with the entered personal number.\n";
        waitForEnter();
    }
}


void appendperson(vector<person>& Person) {
    clearScreen();
    person p;

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
    waitForEnter();
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
            cout << endl;
             cout << string(87, '-') << "\n";
            // Show only the found record before editing
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

            cout << "📌 --------------------------------------------------";
            cout << "\n✏️ What would you like to update?\n";
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
            clearScreen();

            switch (choice) {
                case 1:
                    cout << "✍️ Enter New First Name: ";
                    cin >> p.name;
                    break;
                case 2:
                    cout << "✍️ Enter New Last Name: ";
                    cin >> p.lastname;
                    break;
                case 3:
                    cout << "🎂 Enter New Age: ";
                    cin >> p.age;
                    break;
                case 4:
                    cout << "💵 Enter New Invoice Amount: ";
                    cin >> p.invoice;
                    break;
                case 5:
                    cout << "💰 Enter New VAT %: ";
                    cin >> p.VAT;
                    break;
                case 6:
                    cout << "🆔 Enter New Personal Number: ";
                    cin >> p.personnumber;
                    break;
                default:
                    cout << "❌ Invalid selection. Returning to menu.\n";
                    waitForEnter();
                    return;
            }

            cout << "\n✅ Information updated successfully!\n";
            cout << "📎 Updated Record for: " << p.name << " " << p.lastname << "\n";
            cout << "=====================================================\n";
            waitForEnter();
            return;
        }
    }

    if (!found) {
        cout << "\n❌ No person found with the entered personal number.\n";
        waitForEnter();
    }
}

void FindPerson(vector<person>& Person){
    clearScreen();
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
            cout << endl;
             cout << string(87, '-') << "\n";
            // Show only the found record before editing
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
            waitForEnter();

}
}
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