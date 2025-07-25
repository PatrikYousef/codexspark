#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

class GitHub {
public:
    int clones = 0;
    int uniqueClones = 0;
    int views = 0;
    int projects = 0;
};

vector<string> projectLog;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\n🔸 Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday << " "
       << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min;
    return ss.str();
}

void appendClones(int& totalClones, int& totalUniqueClones, int& totalViews, int& totalProjects) {
    GitHub g;
    cout << "\n🚀 == Add Project Stats ==\n";
    cout << "=============================\n";

    while (true) {
        cout << "🔹 Clones: ";
        cin >> g.clones;
        if (cin.fail()) {
            cout << "❌ Error: Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            totalClones += g.clones;
            break;
        }
    }

    while (true) {
        cout << "🔹 Unique Clones: ";
        cin >> g.uniqueClones;
        if (cin.fail()) {
            cout << "❌ Error: Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            totalUniqueClones += g.uniqueClones;
            break;
        }
    }

    while (true) {
        cout << "🔹 Views: ";
        cin >> g.views;
        if (cin.fail()) {
            cout << "❌ Error: Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            totalViews += g.views;
            break;
        }
    }

    while (true) {
        cout << "🔹 How many projects are included: ";
        cin >> g.projects;
        if (cin.fail()) {
            cout << "❌ Error: Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            totalProjects += g.projects;
            break;
        }
    }

    string timestamp = getCurrentTime();
    stringstream entry;
    entry << "📅 " << timestamp 
          << " | 📦 Projects: " << g.projects 
          << " | 🧬 Clones: " << g.clones 
          << " | 👤 Unique: " << g.uniqueClones 
          << " | 👁️ Views: " << g.views;
    projectLog.push_back(entry.str());

    cout << "\n✅ Data successfully added!\n";
    cout << "=============================\n";
}

void showStats(int totalClones, int totalUniqueClones, int totalViews, int totalProjects) {
    cout << "\n📊 == Current GitHub Stats ==\n";
    cout << "==============================\n";
    cout << left << setw(25) << "🔹 Total Projects:" << totalProjects << endl;
    cout << left << setw(25) << "🔹 Total Clones:" << totalClones << endl;
    cout << left << setw(25) << "🔹 Unique Clones:" << totalUniqueClones << endl;
    cout << left << setw(25) << "🔹 Total Views:" << totalViews << endl;

    float percentUnique = 0.0f;
    if (totalClones > 0) {
        percentUnique = static_cast<float>(totalUniqueClones) / totalClones * 100;
    }

    if (totalProjects > 0) {
        float clonesPerProject = static_cast<float>(totalClones) / totalProjects;
        float uniquePerProject = static_cast<float>(totalUniqueClones) / totalProjects;
        float viewsPerProject = static_cast<float>(totalViews) / totalProjects;

        cout << left << setw(25) << "📈 Clones per Project:" << fixed << setprecision(2) << clonesPerProject << endl;
        cout << left << setw(25) << "👤 Unique per Project:" << fixed << setprecision(2) << uniquePerProject << endl;
        cout << left << setw(25) << "👁️ Views per Project:" << fixed << setprecision(2) << viewsPerProject << endl;
    } else {
        cout << "⚠️ Not enough data to calculate averages (0 projects).\n";
    }

    cout << left << setw(25) << "🔹 Unique Clone (%) :" << fixed << setprecision(2) << percentUnique << " %\n";

    cout << "------------------------------\n";
    if (percentUnique >= 70)
        cout << "🔥 Excellent reach! Lots of unique users!\n";
    else if (percentUnique >= 50)
        cout << "✅ Good spread. Keep going!\n";
    else if (percentUnique >= 30)
        cout << "🟡 Decent, but could be improved.\n";
    else
        cout << "🔻 Low uniqueness. Try promoting more.\n";
    cout << "==============================\n";
}

void showLog() {
    clearScreen();
    cout << "\n🕓 == Project Log ==\n";
    cout << "===========================\n";
    if (projectLog.empty()) {
        cout << "❌ No entries yet.\n";
    } else {
        for (const auto& entry : projectLog) {
            cout << entry << endl;
        }
    }
    cout << "===========================\n";
    pause();
}

void AboutTheCode() {
    cout << "\n=============================================\n";
    cout << "      📢 Welcome to GitHub Stats Tracker 📢\n";
    cout << "=============================================\n\n";

    cout << "📋 How it works:\n";
    cout << "---------------------------------------------\n";
    cout << "\n• 📦 Track your GitHub project stats over time.\n";
    cout << "\n• ⏳ GitHub only shows traffic data for 14 days.\n";
    cout << "\n• 🔄 Use this tool to manually track your stats.\n";
    cout << "\n• 📊 You can track: clones, views, unique clones, and number of projects.\n";
    cout << "\n• 📈 Monitor average performance per project (e.g., Clones/Project).\n";
    cout << "\n• 🚀 Stay motivated as your numbers grow!\n\n";

    cout << "⚠️ Data Persistence Warning:\n";
    cout << "---------------------------------------------\n";
    cout << "\n• ❌ All data will be lost when you close the program.\n";
    cout << "\n• 💾 You can implement file saving using fstream.\n";
    cout << "\n• 🛠️ Try building your own save/load feature.\n\n";

    cout << "📌 Pro Tips:\n";
    cout << "---------------------------------------------\n";
    cout << "\n• 🗂️ Track each GitHub repo separately if needed.\n";
    cout << "\n• 📅 Update weekly or after promoting your project.\n";
    cout << "\n• 🎯 Use your stats to guide growth strategy.\n";

    cout << "\n=============================================\n\n";
}

void printMenu() {
    cout << "\n══════════════════════════════════\n";
    cout << "     📈 GITHUB STATS TRACKER      \n";
    cout << "══════════════════════════════════\n";
    cout << "\n1. ➕ Add Project Stats\n";
    cout << "\n2. 📊 Show Total Stats\n";
    cout << "\n3. ♻️ Reset All Stats\n";
    cout << "\n4. ❌ Exit\n";
    cout << "\n5. 🕓 View Project Log\n";
    cout << "══════════════════════════════════\n";
    cout << "👉 Enter your choice (1-5): ";
}

int main() {
    int totalClones = 0;
    int totalUniqueClones = 0;
    int totalViews = 0;
    int totalProjects = 0;
    int choice;

    clearScreen();
    AboutTheCode();
    pause();

    while (true) {
        clearScreen();
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "\n❌ Invalid input. Please enter a number from 1 to 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                appendClones(totalClones, totalUniqueClones, totalViews, totalProjects);
                pause();
                break;
            case 2:
                clearScreen();
                showStats(totalClones, totalUniqueClones, totalViews, totalProjects);
                pause();
                break;
            case 3:
                clearScreen();
                totalClones = 0;
                totalUniqueClones = 0;
                totalViews = 0;
                totalProjects = 0;
                projectLog.clear();
                cout << "\n♻️ All stats have been reset to zero.\n";
                pause();
                break;
            case 4:
                clearScreen();
                cout << "\n👋 Exiting... Goodbye and God bless!\n";
                return 0;
            case 5:
                clearScreen();
                showLog();
                break;
            default:
                clearScreen();
                cout << "\n⚠️ Please select a valid option (1-5).\n";
                pause();
        }
    }

    return 0;
}