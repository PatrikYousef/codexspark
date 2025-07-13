#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class Loan {
public:
    string name;
    string lastname;
    string personnumber;
    float loanAmount;
    float interestRate;
    float years;

    float calculateTotalToPay() const {
        return loanAmount * (1 + interestRate * years);
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLine(char ch, int length) {
    cout << string(length, ch) << "\n";
}
void felsöka(){
     cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard leftover input
    cin.get(); // wait for actual Enter press
}


void appendPerson(vector<Loan>& people) {
    do {
        Loan l;

        printLine('=', 50);
        cout << "📋 Register a New Loan\n";
        printLine('=', 50);

        cout << "👤 First Name        : ";
        cin >> l.name;

        cout << "👤 Last Name         : ";
        cin >> l.lastname;

        cout << "🆔 Personal Number   : ";
        cin >> l.personnumber;

        cout << "💵 Loan Amount (kr)  : ";
        while (!(cin >> l.loanAmount) || l.loanAmount <= 0) {
            cout << "⚠️ Please enter a valid positive loan amount: ";
            felsöka();
        }

        cout << "📈 Interest Rate (%) : ";
        while (!(cin >> l.interestRate) || l.interestRate < 0) {
            cout << "⚠️ Please enter a valid non-negative interest rate: ";
            felsöka();
        }
        // Convert interest rate percentage to decimal fraction
        l.interestRate /= 100.0f;

        cout << "⏳ Duration (years)  : ";
        while (!(cin >> l.years) || l.years <= 0) {
            cout << "⚠️ Please enter a valid positive duration in years: ";
            felsöka();
        }

        float totalToPay = l.calculateTotalToPay();
        float totalPerMonth = totalToPay / (l.years * 12);

        cout << fixed << setprecision(2);
        cout << "\n✅ Loan Registered Successfully!\n";
        cout << "💰 Total to Pay Back       : " << totalToPay << " kr\n";
        cout << "💰 Total to Pay Back/month : " << totalPerMonth << " kr\n";
        printLine('=', 50);

        people.push_back(l);

        // Ask if user wants to add another loan
        cout << "➕ Add another loan? (y/n): ";
        char cont;
        cin >> cont;
        if (cont != 'y' && cont != 'Y') {
            break;
        }

    } while (true);
}

void showPeople(const vector<Loan>& people) {
    if (people.empty()) {
        cout << "\n⚠️  No loans registered yet.\n";
        return;
    }

    printLine('=', 130);
    cout << "📄 Registered Loans\n";
    printLine('=', 130);

    cout << "╔════╦════════════════╦════════════════╦════════════════════╦════════════╦════════════╦════════╦════════════════╦════════════════╗\n";
    cout << "║ ID ║ First Name     ║ Last Name      ║ Personal Number    ║ Loan (kr)  ║ Rate (%)   ║ Years  ║ 💸 Per Month   ║  Total to Pay  ║\n";
    cout << "╠════╬════════════════╬════════════════╬════════════════════╬════════════╬════════════╬════════╬════════════════╬════════════════╣\n";

    for (size_t i = 0; i < people.size(); ++i) {
        const auto& p = people[i];
        float totalToPay = p.calculateTotalToPay();
        float perMonth = totalToPay / (p.years * 12);

        cout << "║ "
             << setw(2) << right << (i + 1) << " ║ "
             << setw(15) << left << p.name << "║ "
             << setw(15) << left << p.lastname << "║ "
             << setw(19) << left << p.personnumber << "║ "
             << setw(10) << right << fixed << setprecision(2) << p.loanAmount << " ║ "
             << setw(9) << right << p.interestRate * 100 << " ║ "
             << setw(6) << right << p.years << " ║ "
             << setw(14) << right << perMonth << " ║ "
             << setw(14) << right << totalToPay << " ║\n";
    }

    cout << "╚════╩════════════════╩════════════════╩════════════════════╩════════════╩════════════╩════════╩════════════════╩════════════════╝\n";
    waitForEnter();
}

void findPerson(const vector<Loan>& people) {
    if (people.empty()) {
        cout << "\n⚠️  No loans registered yet.\n";
        return;
    }

    cin.ignore();
    string searchPN;
    cout << "\n🔍 Enter personal number to search: ";
    getline(cin, searchPN);

    bool found = false;

    for (size_t i = 0; i < people.size(); ++i) {
        const auto& p = people[i];
        if (p.personnumber == searchPN) {
            found = true;
            float totalToPay = p.calculateTotalToPay();
            float perMonth = totalToPay / (p.years * 12);

            printLine('=', 130);
            cout << "📋 Loan Details for Personal Number: " << p.personnumber << "\n";
            printLine('=', 130);

            cout << "╔════╦════════════════╦════════════════╦════════════════════╦════════════╦════════════╦════════╦════════════════╦════════════════╗\n";
            cout << "║ ID ║ First Name     ║ Last Name      ║ Personal Number    ║ Loan (kr)  ║ Rate (%)   ║ Years  ║ 💸 Per Month   ║  Total to Pay  ║\n";
            cout << "╠════╬════════════════╬════════════════╬════════════════════╬════════════╬════════════╬════════╬════════════════╬════════════════╣\n";

            cout << "║ "
                 << setw(2) << right << (i + 1) << " ║ "
                 << setw(15) << left << p.name << "║ "
                 << setw(15) << left << p.lastname << "║ "
                 << setw(19) << left << p.personnumber << "║ "
                 << setw(10) << right << fixed << setprecision(2) << p.loanAmount << " ║ "
                 << setw(9) << right << p.interestRate * 100 << " ║ "
                 << setw(6) << right << p.years << " ║ "
                 << setw(14) << right << perMonth << " ║ "
                 << setw(14) << right << totalToPay << " ║\n";

            cout << "╚════╩════════════════╩════════════════╩════════════════════╩════════════╩════════════╩════════╩════════════════╩════════════════╝\n";

            waitForEnter();
            break;
        }
    }

    if (!found) {
        cout << "❌ No person found with that personal number.\n";
    }
}




void deletePerson(vector<Loan>& people) {
    if (people.empty()) {
        cout << "\n⚠️ No loans registered yet.\n";
        waitForEnter();
        return;
    }

    cin.ignore();

    string delPN;
    cout << "\n🗑️ Enter personal number to delete: ";
    getline(cin, delPN);

    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].personnumber == delPN) {
            cout << "⚠️ Are you sure you want to delete the loan for " << people[i].name << " " << people[i].lastname << "? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                people.erase(people.begin() + i);
                cout << "✅ Loan deleted successfully.\n";
            } else {
                cout << "❌ Deletion canceled.\n";
            }
            waitForEnter();
            return;
        }
    }
    cout << "❌ No loan found with that personal number.\n";
    waitForEnter();
}

int main() {
    vector<Loan> people;

    while (true) {
        clearScreen();
        cout << "\n📘 Loan Management System\n";
        printLine('=', 30);
        cout << "\n1. ➕  Add New Loan\n";
        cout << "\n2. 📄  Show All Loans\n";
        cout << "\n3. 🔍  Search by Personal Number\n";
        cout << "\n4. 🗑️   Delete Loan\n";
        cout << "\n5. ❌  Exit\n";
        printLine('=', 30);

        cout << "Choose an option (1-4): ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
            clearScreen();
                appendPerson(people);
                break;
            case 2:
                clearScreen();
                showPeople(people);
                break;
            case 3:
                clearScreen();
                findPerson(people);
                break;
            case 4:
                clearScreen();
                deletePerson(people);
                break;

            case 5:
                cout << "👋 Exiting program. Have a blessed day!\n";
                return 0;
            default:
                cout << "⚠️ Invalid choice. Try again.\n";
                felsöka();
        }
    }
} 