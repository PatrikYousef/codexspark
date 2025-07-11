#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


class Person {
public:
    int id;
    string name;
    string lastname;
    string personnumber;
    float prize = 0;
};

class Medicaid {
public:
    string name;
    float prize;
    int id;
};

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void waitForEnter() {
    cout << "Press Enter to continue...\n";
    cin.get();
}

void appendPerson(vector<Person>& people, int& personCounter) {
    Person p;
    p.id = ++personCounter;

    cout << "👤 Enter first name: ";
    getline(cin, p.name);

    cout << "👤 Enter last name: ";
    getline(cin, p.lastname);

    cout << "🆔 Enter personal number (e.g., SSN): ";
    getline(cin, p.personnumber);

    people.push_back(p);
    cout << "\n✅ Person successfully added!\n";
}

void displayPeople(const vector<Person>& people) {
    if (people.empty()) {
        cout << "⚠️ No people have been registered yet.\n";
        return;
    }

    cout << "\n👥 Registered People:\n";
    cout << left;
    cout << "╔════╦═════════════════╦═════════════════════╦════════════════════════╦═══════════════╗\n";
    cout << "║ ID ║ First Name      ║ Last Name           ║ Personal Number        ║ Prize         ║\n";
    cout << "╠════╬═════════════════╬═════════════════════╬════════════════════════╬═══════════════╣\n";

    for (const auto& p : people) {
        cout << "║ " << setw(2) << p.id << " "
             << "║ " << setw(16) << p.name
             << "║ " << setw(20) << p.lastname
             << "║ " << setw(23) << p.personnumber
             << "║ $" << setw(11) << fixed << setprecision(2) << p.prize << "║\n";
    }

    cout << "╚════╩═════════════════╩═════════════════════╩════════════════════════╩═══════════════╝\n";
    waitForEnter();
}

void findperson(const vector<Person>& people) {
    if (people.empty()) {
        cout << "⚠️ No people have been registered yet.\n";
        return;
    }

    string findtheperson;
    cout << "🔍 Enter the personal number to search for: ";
    getline(cin, findtheperson);

    bool found = false;

    for (const auto& p : people) {
        if (p.personnumber == findtheperson) {
            found = true;
            cout << "\n👤 Person Found:\n";
            cout << "╔════╦═════════════════╦═════════════════════╦════════════════════════╦═══════════════╗\n";
            cout << "║ ID ║ First Name      ║ Last Name           ║ Personal Number        ║ Prize         ║\n";
            cout << "╠════╬═════════════════╬═════════════════════╬════════════════════════╬═══════════════╣\n";
            cout << "║ " << setw(2) << p.id << " "
                 << "║ " << setw(16) << p.name
                 << "║ " << setw(20) << p.lastname
                 << "║ " << setw(23) << p.personnumber
                 << "║ $" << setw(11) << fixed << setprecision(2) << p.prize << "║\n";
            cout << "╚════╩═════════════════╩═════════════════════╩════════════════════════╩═══════════════╝\n";
            waitForEnter();
            break;
        }
    }

    if (!found) {
        cout << "❌ No person found with that personal number.\n";
    }
}

void appendMedicaidPrize(vector<Medicaid>& medical, int& medicalCounter) {
    Medicaid m;
    m.id = ++medicalCounter;

    cout << "💉 Enter the name of the medical condition: ";
    getline(cin, m.name);

    cout << "💵 Enter the treatment cost (per year): ";
    while (!(cin >> m.prize)) {
        cout << "❌ Invalid input for cost. Please enter a number: ";
        cin.clear();
        clearInput();
    }
    clearInput();

    medical.push_back(m);
    cout << "\n✅ Medical condition added successfully!\n";
}

void showMedicaid(const vector<Medicaid>& medical) {
    if (medical.empty()) {
        cout << "⚠️ No medical conditions have been recorded yet.\n";
        return;
    }

    cout << "\n📋 List of Medical Conditions and Annual Costs:\n";
    cout << left;
    cout << "╔════╦════════════════════════════╦════════════════════╗\n";
    cout << "║ ID ║ Condition Name             ║ Cost (per year)    ║\n";
    cout << "╠════╬════════════════════════════╬════════════════════╣\n";

    for (const auto& m : medical) {
        cout << "║ " << setw(2) << m.id << " "
             << "║ " << setw(28) << m.name
             << "║ $" << setw(18) << fixed << setprecision(2) << m.prize << "║\n";
    }

    cout << "╚════╩════════════════════════════╩════════════════════╝\n";
    waitForEnter();
}

void getmedicalprize(vector<Person>& people, vector<Medicaid>& medical) {
    if (people.empty() || medical.empty()) {
        cout << "⚠️ Please ensure both people and medical data are available.\n";
        return;
    }

    displayPeople(people);

    int choice;
    cout << "👉 Enter the ID of the person to calculate medical cost: ";
    while (!(cin >> choice)) {
        cout << "❌ Invalid input. Please enter a valid person ID: ";
        cin.clear();
        clearInput();
    }
    clearInput();

    bool personFound = false;
    for (auto& p : people) {
        if (choice == p.id) {
            personFound = true;

            showMedicaid(medical);

            float totalCost = 0.0f;

            while (true) {
                int hurt;
                cout << "\n🤕 Enter the ID of the medical condition (or 0 to finish): ";
                if (!(cin >> hurt)) {
                    cout << "❌ Invalid input. Please enter a number.\n";
                    cin.clear();
                    clearInput();
                    continue;
                }
                clearInput();

                if (hurt == 0) break;

                bool conditionFound = false;
                for (const auto& m : medical) {
                    if (hurt == m.id) {
                        conditionFound = true;
                        int years;
                        cout << "📅 Enter the number of years the condition persisted: ";
                        while (!(cin >> years) || years < 0) {
                            cout << "❌ Invalid input. Enter a positive number of years: ";
                            cin.clear();
                            clearInput();
                        }
                        clearInput();

                        float cost = m.prize * years;
                        totalCost += cost;

                        cout << "✅ Added cost for " << m.name << ": $" << fixed << setprecision(2) << cost << "\n";
                        break;
                    }
                }

                if (!conditionFound) {
                    cout << "❌ No medical condition matched the entered ID.\n";
                }
            }

            p.prize = totalCost;

            cout << "\n💰 Total Estimated Medical Cost for " << p.name << " " << p.lastname << ": $"
                 << fixed << setprecision(2) << totalCost << "\n";
            break;
        }
    }

    if (!personFound) {
        cout << "❌ No person found with that ID.\n";
    }
}



int main() {
    vector<Person> personList;
    vector<Medicaid> medical;
    int personCounter = 0;
    int medicalCounter = 0;
    int choice;




    while (true) {
            clearScreen();
            cout << "══════════════════════════════════════\n";
    cout << "     🏥 Welcome to the Medicaid System 🏥\n";
    cout << "══════════════════════════════════════\n";
        cout << "\n═══════════════════════════════════════════════\n";
        cout << "\n1. ➕ Add a Person\n";
        cout << "\n2. 👥 View Registered People\n";
        cout << "\n3. 🏥 Add Medical Condition and Cost\n";
        cout << "\n4. 📋 View Medical Conditions\n";
        cout << "\n5. 💰 Calculate Medical Cost for a Person\n";
        cout << "\n6. 🔍 Find Person by Personal Number\n";
        cout << "\n7. ❌ Exit the Program\n";
        cout << "\n═══════════════════════════════════════════════\n";
        cout << "Enter your choice (1-7): ";

        if (!(cin >> choice)) {
            cout << "❌ Invalid input! Please enter a number between 1 and 7.\n";
            cin.clear();
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
            case 1:
            clearScreen();
                appendPerson(personList, personCounter);
                break;
            case 2:
            clearScreen();
                displayPeople(personList);
                break;
            case 3:
            clearScreen();
                appendMedicaidPrize(medical, medicalCounter);
                break;
            case 4:
            clearScreen();
                showMedicaid(medical);
                break;
            case 5:
            clearScreen();
                getmedicalprize(personList, medical);
                break;
            case 6:
            clearScreen();
                findperson(personList);
                break;
            case 7:
                cout << "👋 Thank you for using the Medicaid System. Goodbye!\n";
                return 0;
            default:
                cout << "❌ Invalid choice! Please select a number between 1 and 7.\n";
                break;
        }

        cout << "──────────────────────────────────────────────\n";
    }
}
