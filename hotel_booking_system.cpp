#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class hotel {
public:
    string name;
    string lastname;
    long long int personnumber;
    int days;
    int room;
    int prize = 500;
    int totalprize;

    void calculateTotal() {
        totalprize = days * prize;
    }
};

void ClearScreen() {
    // cross-platform clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
// 📍 Show available rooms as ✅ and ❌ with room numbers
void ShowRoomMap(const vector<hotel>& hotell) {
    const int columns = 10;
    cout << "\n🏨════════════════════════ ROOM STATUS MAP ═════════════════════════\n\n";

    for (int i = 0; i < 100; ++i) {
        bool taken = false;
        for (const auto& guest : hotell) {
            if (guest.room == i) {
                taken = true;
                break;
            }
        }

        cout << (taken ? "❌" : "✅") << setw(2) << i << "  ";

        if ((i + 1) % columns == 0)
            cout << endl;
    }

    cout << "\n═════════════════════════════════════════════════════════════════════\n";
}

// ✍️ Add a new guest
void AppendPerson(vector<hotel>& hotell) {
    hotel h;

    cout << "\n📥═════════════════════════════════════════════════════════════════════📥\n";
    cout << "                     ADD NEW PERSON DETAILS FORM                      \n";
    cout << "📥═════════════════════════════════════════════════════════════════════📥\n\n";

    cout << "👤 First Name        : ";
    cin >> h.name;

    cout << "👥 Last Name         : ";
    cin >> h.lastname;

    while (true) {
        cout << "🆔 Personal Number   : ";
        cin >> h.personnumber;

        if (cin.fail()) {
            cout << "❌ Invalid number. Please enter digits only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    while (true) {
        cout << "📅 Days Staying      : ";
        cin >> h.days;

        if (cin.fail()) {
            cout << "❌ Invalid number. Please enter digits only.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    // 🔍 Show available rooms
    ShowRoomMap(hotell);

    // 🚪 Room selection — check if taken
    while (true) {
        cout << "🚪 Select Room Number (0-99): ";
        cin >> h.room;

        if (cin.fail() || h.room < 0 || h.room >= 100) {
            cout << "❌ Invalid room number. Please select between 0 and 99.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        bool taken = false;
        for (const auto& guest : hotell) {
            if (guest.room == h.room) {
                taken = true;
                break;
            }
        }

        if (taken) {
            cout << "❌ That room is already booked. Choose another.\n";
        } else {
            break;
        }
    }

  
    h.calculateTotal();
    hotell.push_back(h);

    cout << "\n✅ Person successfully added to room " << h.room << "!\n";
    cout << "🙏 Thank you, " << h.name << " " << h.lastname << "!\n";
}


void ShowPerson(const vector<hotel>& hotell) {
    ClearScreen();
    cout << "\n📄══════════════════════════ GUEST LIST DETAILS ═══════════════════════════📄\n";

    if (hotell.empty()) {
        cout << "\n⚠️ No guests have been added yet.\n";
        return;
    }

    cout << left << setw(14) << "👤 First"
         << setw(14) << "👥 Last"
         << setw(18) << "🆔 Person #"
         << setw(8)  << "🏨 Room"
         << setw(8)  << "📅 Days"
         << setw(10) << "💰 Total" << "\n";
    cout << "═════════════════════════════════════════════════════════════════════════════\n";

    for (const auto& i : hotell) {
        cout << left << setw(14) << i.name
             << setw(14) << i.lastname
             << setw(18) << i.personnumber
             << setw(8)  << i.room
             << setw(8)  << i.days
             << setw(10) << i.totalprize << "\n";
    }

    cout << "═════════════════════════════════════════════════════════════════════════════\n";
}

void SearchPerson(vector<hotel>& hotell){
    long long int personnumber;
    cout << "Personnumber: ";
    cin >> personnumber;
    for (const auto& i : hotell)
    {
        if (personnumber == i.personnumber)
        {
            cout << i.name << i.lastname << i.personnumber << i.room << i.prize << i.days << i.totalprize;
        }
        
    }
    

}
void ChangeSomethingYouAccidentallyAdded(vector<hotel>& hotell) {
    ClearScreen();
    long long int personnumber;
    bool found = false;

    cout << "\n🛠️🔧🔨 ==================================================\n";
    cout << "🔍 ENTER THE 🆔 PERSONAL NUMBER TO MODIFY A RECORD 📄\n";
    cout << "=====================================================\n";
    cout << "🆔 Personal Number: ";
    cin >> personnumber;

    for (auto& h : hotell) {
        if (h.personnumber == personnumber) {
            found = true;
            cout << endl;
            cout << string(70, '-') << "\n";

            cout << left
                 << setw(14) << "👤 First Name"
                 << setw(14) << "👥 Last Name"
                 << setw(18) << "🆔 Personal #"
                 << setw(8)  << "🏨 Room"
                 << setw(8)  << "📅 Days"
                 << setw(10) << "💰 Total"
                 << "\n";

            cout << string(70, '-') << "\n";

            cout << left
                 << setw(14) << h.name
                 << setw(14) << h.lastname
                 << setw(18) << h.personnumber
                 << setw(8)  << h.room
                 << setw(8)  << h.days
                 << setw(10) << h.totalprize
                 << "\n";

            cout << string(70, '-') << "\n";

            cout << "\n📌 --------------------------------------------------\n";
            cout << "✏️ What would you like to update?\n";
            cout << "📌 --------------------------------------------------\n";
            cout << "1️⃣  👤 First Name\n";
            cout << "2️⃣  👥 Last Name\n";
            cout << "3️⃣  📅 Days Staying\n";
            cout << "4️⃣  🚪 Room Number\n";
            cout << "5️⃣  🆔 Personal Number\n";
            cout << "📌 --------------------------------------------------\n";
            cout << "👉 Your choice (1-5): ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "✍️ Enter New First Name: ";
                    cin >> h.name;
                    break;
                case 2:
                    cout << "✍️ Enter New Last Name: ";
                    cin >> h.lastname;
                    break;
                case 3:
                    cout << "📅 Enter New Days Staying: ";
                    cin >> h.days;
                    break;
                case 4: {
                    int newRoom;
                    while (true) {
                        cout << "🚪 Enter New Room Number (0-99): ";
                        cin >> newRoom;
                        if (cin.fail() || newRoom < 0 || newRoom >= 100) {
                            cout << "❌ Invalid room number. Please select between 0 and 99.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        // Check if room already taken by someone else
                        bool taken = false;
                        for (const auto& guest : hotell) {
                            if (guest.room == newRoom && guest.personnumber != h.personnumber) {
                                taken = true;
                                break;
                            }
                        }
                        if (taken) {
                            cout << "❌ That room is already booked. Choose another.\n";
                        } else {
                            break;
                        }
                    }
                    h.room = newRoom;
                    break;
                }
                case 5:
                    cout << "🆔 Enter New Personal Number: ";
                    cin >> h.personnumber;
                    break;
                default:
                    cout << "❌ Invalid selection. Returning to menu.\n";
                    return;
            }

            h.calculateTotal();  // recalc total prize in case days changed

            cout << "\n✅ Information updated successfully!\n";
            cout << "📎 Updated Record for: " << h.name << " " << h.lastname << "\n";
            cout << "=====================================================\n";
            return;
        }
    }

    if (!found) {
        cout << "\n❌ No person found with the entered personal number.\n";
    }
}
void ShowRoom(const vector<hotel>& hotell) {
    const int columns = 10;
    cout << "\n🏨════════════════════════ ROOM STATUS MAP ═════════════════════════\n\n";

    for (int i = 0; i < 100; ++i) {
        bool taken = false;
        for (const auto& guest : hotell) {
            if (guest.room == i) {
                taken = true;
                break;
            }
        }

        cout << (taken ? "❌" : "✅") << setw(2) << i << "  ";

        if ((i + 1) % columns == 0)
            cout << endl;
    }

    cout << "\n═════════════════════════════════════════════════════════════════════\n";
}
void ShowMenu() {
    ClearScreen();
    cout << "\n\n";
    cout << "🏨💫═════════════════════════════════════════════════════════════════════════💫🏨\n";
    cout << "🌟                     WELCOME TO THE ROYAL HOTEL BOOKING SYSTEM            🌟\n";
    cout << "🏨💫═════════════════════════════════════════════════════════════════════════💫🏨\n\n";

    cout << "🛎️  Please select an option below to continue:\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

    cout << "\n1️⃣  ➤ 🧾 Add New Guest to the Hotel\n";
    cout << "\n2️⃣  ➤ 📋 View All Guests (Guest List)\n";
    cout << "\n3️⃣  ➤ 🔍 Search Guest by Personal Number\n";
    cout << "\n4️⃣  ➤ 🛠️ Update Guest Details\n";
    cout << "\n5️⃣  ➤ 🏨 Show Room Status Map\n";
    cout << "\n6️⃣  ➤ ❌ Exit the Booking System\n";

    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "👉 Enter your choice (1–6): ";
}

int main() {
    vector<hotel> hotell;
    int choice;

    while (true) {
        ShowMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "❌ Invalid input. Please enter a number between 1 and 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                AppendPerson(hotell);
                break;
            case 2:
                ShowPerson(hotell);
                break;
            case 3:
                SearchPerson(hotell);
                break;
            case 4:
                ChangeSomethingYouAccidentallyAdded(hotell);
                break;
            case 5:
                ShowRoom(hotell);
                break;
            case 6:
                cout << "\n👋 Exiting... Thank you for using the Hotel Booking System!\n\n";
                return 0;
            default:
                cout << "❌ Invalid choice. Please select a number between 1 and 6.\n";
        }
    }
}