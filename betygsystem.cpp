#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib> // For system()

using namespace std;

// Adjust the command to clear the screen depending on OS
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

void clearScreen() {
    system(CLEAR_COMMAND);
}

void pause() {
    cout << "\n⏸️  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Data type to store grade information
struct Grade {
    string firstName;
    string lastName;
    char grade;

    // Comparison operator to be able to use std::remove
    bool operator==(const Grade& other) const {
        return firstName == other.firstName && lastName == other.lastName && grade == other.grade;
    }
};

// Add a grade
void addGrade(vector<Grade>& system) {
    Grade g;
    cout << "\n📝 --- Add Grade --- 📝\n";
    cout << "👤 First name: ";
    cin >> g.firstName;
    cout << "👤 Last name: ";
    cin >> g.lastName;
    cout << "🏅 Grade (A-F): ";
    cin >> g.grade;
    g.grade = toupper(g.grade);

    if (string("ABCDEF").find(g.grade) != string::npos) {
        system.push_back(g);
        cout << "\n✅ Added: " << g.firstName << " " << g.lastName << " (" << g.grade << ")\n";
    } else {
        cout << "\n❌ Invalid grade. Only A-F allowed.\n";
    }
}

// Remove a specific grade
void removeGrade(vector<Grade>& system) {
    Grade g;
    cout << "\n🗑️  --- Remove Grade --- 🗑️\n";
    cout << "👤 First name: ";
    cin >> g.firstName;
    cout << "👤 Last name: ";
    cin >> g.lastName;
    cout << "🏅 Grade: ";
    cin >> g.grade;
    g.grade = toupper(g.grade);

    auto it = remove(system.begin(), system.end(), g);
    if (it != system.end()) {
        system.erase(it, system.end());
        cout << "\n🗑️  Entry deleted successfully.\n";
    } else {
        cout << "\n⚠️  No matching entry found.\n";
    }
}

// Show all grades
void showGrades(const vector<Grade>& system) {
    cout << "\n📋 --- Grade List --- 📋\n";
    if (system.empty()) {
        cout << "📭 No grades added yet.\n";
        return;
    }

    cout << left << setw(20) << "👤 First Name" 
         << setw(20) << "👤 Last Name" 
         << "🏅 Grade\n";
    cout << string(50, '-') << '\n';

    for (const auto& g : system) {
        cout << left << setw(20) << g.firstName
             << setw(20) << g.lastName
             << g.grade << '\n';
    }
}

// Show main menu and return user choice
int menu() {
    cout << "\n🎓 ======= GRADE SYSTEM ======= 🎓\n";
cout << "\n1️⃣  ✏️ Add Grade\n";
cout << "\n2️⃣  🗑️ Remove Grade\n";
cout << "\n3️⃣  📋 Show Grades\n";
cout << "\n4️⃣  🚪 Exit\n";
cout << "===============================\n"
         << "👉 Choice: ";

    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; // Invalid input
    }

    cin.ignore(); // Clear newline after number
    return choice;
}

int main() {
    vector<Grade> system;
    while (true) {
        clearScreen();
        int choice = menu();

        switch (choice) {
            case 1: addGrade(system); break;
            case 2: removeGrade(system); break;
            case 3: showGrades(system); break;
            case 4:
                cout << "\n👋 Thank you for using the system. Goodbye!\n";
                return 0;
            default:
                cout << "\n⚠️  Invalid choice. Please enter a number between 1 and 4.\n";
        }

        pause();
    }
}
