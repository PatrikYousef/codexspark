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

void felsöka() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForEnter() {
    cout << "\n\n🔁 Press Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void appendPerson(vector<Loan>& people) {
    do {
        clearScreen();
        Loan l;

        printLine('=', 70);
        cout << setw(50) << "📋 Register a New Loan 📋" << "\n";
        printLine('=', 70);
        cout << "\n";

        cout << "👤 First Name               : ";
        cin >> l.name;

        cout << "👤 Last Name                : ";
        cin >> l.lastname;

        cout << "🆔 Personal Number          : ";
        cin >> l.personnumber;

        cout << "💵 Loan Amount (kr)         : ";
        while (!(cin >> l.loanAmount) || l.loanAmount <= 0) {
            cout << "⚠️  Please enter a valid positive loan amount: ";
            felsöka();
        }

        cout << "📈 Interest Rate (%)        : ";
        while (!(cin >> l.interestRate) || l.interestRate < 0) {
            cout << "⚠️  Please enter a valid non-negative interest rate: ";
            felsöka();
        }
        l.interestRate /= 100.0f;

        cout << "⏳ Duration (years)         : ";
        while (!(cin >> l.years) || l.years <= 0) {
            cout << "⚠️  Please enter a valid positive duration in years: ";
            felsöka();
        }

        float totalToPay = l.calculateTotalToPay();
        float totalPerMonth = totalToPay / (l.years * 12);

        cout << fixed << setprecision(2);
        cout << "\n✅ Loan Registered Successfully!\n";
        cout << "💰 Total to Pay Back        : " << totalToPay << " kr\n";
        cout << "💰 Monthly Payment          : " << totalPerMonth << " kr\n";

        printLine('=', 70);
        people.push_back(l);

        cout << "\n➕ Add another loan? (y/n): ";
        char cont;
        cin >> cont;
        if (cont != 'y' && cont != 'Y') break;

    } while (true);
}

void showPeople(const vector<Loan>& people) {
    clearScreen();
    if (people.empty()) {
        cout << "\n⚠️  No loans registered yet.\n";
        waitForEnter();
        return;
    }

    printLine('=', 150);
    cout << setw(90) << "📄 Registered Loans 📄" << "\n";
    printLine('=', 150);

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
    clearScreen();
    if (people.empty()) {
        cout << "\n⚠️  No loans registered yet.\n";
        waitForEnter();
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

            printLine('=', 150);
            cout << "📋 Loan Details for: " << p.name << " " << p.lastname << " (" << p.personnumber << ")\n";
            printLine('=', 150);

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
        cout << "\n❌ No person found with that personal number.\n";
        waitForEnter();
    }
}

void deletePerson(vector<Loan>& people) {
    clearScreen();
    if (people.empty()) {
        cout << "\n⚠️  No loans registered yet.\n";
        waitForEnter();
        return;
    }

    cin.ignore();

    string delPN;
    cout << "\n🗑️  Enter personal number to delete: ";
    getline(cin, delPN);

    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].personnumber == delPN) {
            cout << "\n⚠️  Are you sure you want to delete the loan for " << people[i].name << " " << people[i].lastname << "? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                people.erase(people.begin() + i);
                cout << "\n✅ Loan deleted successfully.\n";
            } else {
                cout << "\n❌ Deletion canceled.\n";
            }
            waitForEnter();
            return;
        }
    }

    cout << "\n❌ No loan found with that personal number.\n";
    waitForEnter();
}

int main() {
    vector<Loan> people;

    while (true) {
        clearScreen();
        printLine('=', 70);
        cout << setw(48) << "📘 LOAN MANAGEMENT SYSTEM 📘\n";
        printLine('=', 70);

        cout << "\n";
        cout << setw(40) << "🏦 Main Menu 🏦\n";
        printLine('-', 70);

        cout << "\n[1] ➕  Add New Loan\n";
        cout << "\n[2] 📄  Show All Loans\n";
        cout << "\n[3] 🔍  Search by Personal Number\n";
        cout << "\n[4] 🗑️   Delete Loan\n";
        cout << "\n[5] ❌  Exit Program\n";

        cout << "\n";
        printLine('-', 70);
        cout << "👉 Choose an option (1-5): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                appendPerson(people);
                break;
            case 2:
                showPeople(people);
                break;
            case 3:
                findPerson(people);
                break;
            case 4:
                deletePerson(people);
                break;
            case 5:
                clearScreen();
                cout << "\n🙏 Thank you for using the system.\n";
                cout << "✨ May your finances be blessed! ✨\n\n";
                return 0;
            default:
                cout << "\n⚠️ Invalid choice. Please try again.\n";
                felsöka();
                waitForEnter();
        }
    }
}
