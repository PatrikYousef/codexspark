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

// ANSI color codes for terminals that support color (optional)
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string CYAN    = "\033[36m";
const string RESET   = "\033[0m";

// Show month days in a nice calendar style
void showMonth(const string& name, int days) {
    cout << "\n╔════════════════════════════════════╗\n";
    cout << "        📅  " << CYAN << name << RESET << "  📅\n";
    cout << "╚════════════════════════════════════╝\n";

    cout << " ";
    for (int i = 1; i <= days; i++) {
        cout << setw(3) << i;
        if (i % 7 == 0) cout << "\n ";
    }
    cout << "\n\n";
}

// Add a task to the specified month
void addTask(vector<vector<string>>& month, const string& name) {
    int day;
    cout << YELLOW << "\n📌 Pick a day in " << name << " (1–" << month.size() << "): " << RESET;
    cin >> day;

    if (cin.fail() || day < 1 || day > (int)month.size()) {
        cout << RED << "❌ Invalid day.\n" << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore();
    string task;
    cout << YELLOW << "📝 Enter your task:\n> " << RESET;
    getline(cin, task);

    if (task.empty()) {
        cout << RED << "⚠️ Task cannot be empty.\n" << RESET;
    } else {
        month[day - 1].push_back(task);
        cout << GREEN << "✅ Task added for " << name << " " << day << "!\n" << RESET;
    }
}

// Show tasks for the specified month
void showTasks(const vector<vector<string>>& month, const string& name) {
    cout << "\n" << CYAN << "📋 Tasks in " << name << ":" << RESET << "\n";
    bool found = false;

    for (int i = 0; i < (int)month.size(); ++i) {
        if (!month[i].empty()) {
            cout << "\n🗓️  Day " << (i + 1) << ":\n";
            for (const string& task : month[i]) {
                cout << "   ➤ " << task << "\n";
            }
            found = true;
        }
    }

    if (!found) {
        cout << YELLOW << "📭 No tasks saved in " << name << ".\n" << RESET;
    }

    cout << "\n⏎ Press Enter to return to menu...";
    cin.ignore();
    cin.get();
}

void printMenu() {
    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    cout << "                      🌟 TODOLIST CALENDAR 🌟              \n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";

    cout << "\n" << CYAN << "📌 =========== ADD TASK ===========\n" << RESET;
    cout << left;
    cout << setw(4) << " " << setw(22) << "1. January"     << setw(22) << "2. February"  << setw(22) << "3. March"     << "4. April\n";
    cout << setw(4) << " " << setw(22) << "5. May"         << setw(22) << "6. June"      << setw(22) << "7. July"      << "8. August\n";
    cout << setw(4) << " " << setw(22) << "9. September"   << setw(22) << "10. October"  << setw(22) << "11. November" << "12. December\n";

    cout << "\n" << CYAN << "👁️  ========== VIEW TASKS ===========\n" << RESET;
    cout << setw(4) << " " << setw(22) << "13. January"    << setw(22) << "14. February" << setw(22) << "15. March"    << "16. April\n";
    cout << setw(4) << " " << setw(22) << "17. May"        << setw(22) << "18. June"     << setw(22) << "19. July"     << "20. August\n";
    cout << setw(4) << " " << setw(22) << "21. September"  << setw(22) << "22. October"  << setw(22) << "23. November" << "24. December\n";

    cout << "\n" << RED << "🚪 ============= EXIT ===============\n" << RESET;
    cout << setw(4) << " " << "0. Exit\n";

    cout << "\n🔢 Enter your choice (0–24): ";
}

int main() {
    vector<vector<string>> jan(31), feb(28), mar(31), apr(30), may(31), jun(30),
                            jul(31), aug(31), sep(30), oct(31), nov(30), dec(31);

    while (true) {
        clearScreen();
        printMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 0: cout << GREEN << "\n👋 Goodbye! Stay productive!\n" << RESET; return 0;

            case 1:  clearScreen(),showMonth("January", 31);    addTask(jan, "January"); break;
            case 2:   clearScreen(),showMonth("February", 28);   addTask(feb, "February"); break;
            case 3:   clearScreen(),showMonth("March", 31);      addTask(mar, "March"); break;
            case 4:   clearScreen(),showMonth("April", 30);      addTask(apr, "April"); break;
            case 5:   clearScreen(),showMonth("May", 31);        addTask(may, "May"); break;
            case 6:   clearScreen(),showMonth("June", 30);       addTask(jun, "June"); break;
            case 7:   clearScreen(),showMonth("July", 31);       addTask(jul, "July"); break;
            case 8:   clearScreen(),showMonth("August", 31);     addTask(aug, "August"); break;
            case 9:   clearScreen(),showMonth("September", 30);  addTask(sep, "September"); break;
            case 10:  clearScreen(),showMonth("October", 31);    addTask(oct, "October"); break;
            case 11:  clearScreen(),showMonth("November", 30);   addTask(nov, "November"); break;
            case 12:  clearScreen(),showMonth("December", 31);   addTask(dec, "December"); break;

            case 13:  clearScreen(),showTasks(jan, "January"); break;
            case 14:  clearScreen(),showTasks(feb, "February"); break;
            case 15:  clearScreen(),showTasks(mar, "March"); break;
            case 16:  clearScreen(),showTasks(apr, "April"); break;
            case 17:  clearScreen(),showTasks(may, "May"); break;
            case 18:  clearScreen(),showTasks(jun, "June"); break;
            case 19:  clearScreen(),showTasks(jul, "July"); break;
            case 20:  clearScreen(),showTasks(aug, "August"); break;
            case 21:  clearScreen(),showTasks(sep, "September"); break;
            case 22:  clearScreen(),showTasks(oct, "October"); break;
            case 23:  clearScreen(),showTasks(nov, "November"); break;
            case 24:  clearScreen(),showTasks(dec, "December"); break;

            default: cout << RED << "❌ Invalid choice. Try again.\n" << RESET; break;
        }
    }

    return 0;
}
