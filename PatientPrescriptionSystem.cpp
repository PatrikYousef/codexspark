#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ====================
// Person class representing a patient with multiple prescriptions
// ====================
class Person {
public:
    string firstName;
    string lastName;
    string personalID;
    vector<string> prescriptions;  // List of prescription names
    vector<int> quantities;        // Corresponding quantities for each prescription
};

// ====================
// Clears the console screen
// ====================
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ====================
// Prints a horizontal line for section separation
// ====================
void printLine(char ch = '=', int length = 60) {
    cout << string(length, ch) << "\n";
}

// ====================
// Displays the main menu to the user
// ====================
void showMainMenu() {
    printLine('=', 60);
    cout << setw(38) << "🏥 LOAN & PRESCRIPTION REGISTRY 🏥\n";
    printLine('=', 60);
    cout << 
          "\n🟢 1. Register New Patient\n"
         << "\n📋 2. Display All Patients\n"
         << "\n🗑️  3. Remove a Patient Record\n"
         << "\n💊 4. Add Prescription to Patient\n"
         << "\n🔍 5. Show Patient Prescriptions\n"
         << "\n🚪 0. Exit Program\n\n";
    printLine('=', 60);
    cout << "👉 Please enter your choice: ";
}


// ====================
// Adds a new patient record
// ====================
void registerPatient(vector<Person>& patients) {
    do {
        Person p;

        clearScreen();
        printLine('-', 60);
        cout << setw(42) << "📝 Register New Patient 📝\n";
        printLine('-', 60);

        // First Name
        while (true) {
            cout << "👤 Enter First Name: ";
            getline(cin, p.firstName);
            if (!p.firstName.empty())
                break;
            cout << "❌ Invalid input. Please enter a valid name.\n";
        }

        // Last Name
        while (true) {
            cout << "👤 Enter Last Name: ";
            getline(cin, p.lastName);
            if (!p.lastName.empty())
                break;
            cout << "❌ Invalid input. Please enter a valid last name.\n";
        }

        // Personal ID
        while (true) {
            cout << "🆔 Enter Personal ID: ";
            getline(cin, p.personalID);
            if (!p.personalID.empty())
                break;
            cout << "❌ Invalid input. Please enter a valid personal ID.\n";
        }

        // Add patient
        patients.push_back(p);

        cout << "\n✅ Patient successfully registered!\n";

        // Ask if user wants to continue
        cout << "➕ Would you like to add another patient? (y/n): ";
        char response;
        cin >> response;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(response) != 'y') {
            cout << "\nReturning to main menu...\n";
            break;
        }

    } while (true);
}


// ====================
// Displays all registered patients in a table format
// ====================
void displayPatients(const vector<Person>& patients) {
    clearScreen();
    printLine('=', 60);
    cout << setw(42) << "📋 Registered Patients 📋\n";
    printLine('=', 60);

    if (patients.empty()) {
        cout << "\n⚠️  No patients found in the registry.\n";
        return;
    }

    cout << left << setw(5) << "No."
         << setw(22) << "👤 First Name"
         << setw(22) << "👤 Last Name"
         << setw(22) << "🆔 Personal ID" << "\n";
    printLine('-', 60);

    for (size_t i = 0; i < patients.size(); ++i) {
        cout << left << setw(5) << (i + 1)
             << setw(22) << patients[i].firstName
             << setw(22) << patients[i].lastName
             << setw(22) << patients[i].personalID << "\n";
    }

    printLine('=', 60);
}

// ====================
// Removes a patient record by personal ID
// ====================
void removePatient(vector<Person>& patients) {
    clearScreen();
    printLine('=', 60);
    cout << setw(42) << "🗑️ Remove Patient Record 🗑️\n";
    printLine('=', 60);

    if (patients.empty()) {
        cout << "\n⚠️  No patient records available to remove.\n";
        return;
    }

    string id;
    cout << "🆔 Enter the Personal ID of the patient to remove: ";
    getline(cin, id);

    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].personalID == id) {
            cout << "\n🔍 Patient found:\n"
                 << "👤 Name: " << patients[i].firstName << " " << patients[i].lastName << "\n"
                 << "🆔 Personal ID: " << patients[i].personalID << "\n\n";


                     if (!patients[i].prescriptions.empty()) {
                cout << "💊 Prescriptions:\n";
                for (size_t j = 0; j < patients[i].prescriptions.size(); ++j) {
                    cout << "  " << (j + 1) << ". " << patients[i].prescriptions[j]
                         << " (Quantity: " << patients[i].quantities[j] << ")\n";
                }
            } else {
                cout << "⚠️  No prescriptions recorded for this patient.\n";
            }

            cout << "\n❗ Are you sure you want to delete this record? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tolower(confirm) == 'y') {
                patients.erase(patients.begin() + i);
                cout << "\n✅ Patient record successfully deleted.\n";
            } else {
                cout << "\n❌ Deletion cancelled.\n";
            }
            return;
        }
    }

    cout << "\n❌ No patient found with the given Personal ID.\n";
}


// ====================
// Adds a prescription entry to an existing patient record
// ====================
void addPrescription(vector<Person>& patients) {
    clearScreen();
    printLine('=', 60);
    cout << setw(42) << "💊 Add Prescription 💊\n";
    printLine('=', 60);

    if (patients.empty()) {
        cout << "\n⚠️  No patients registered to add prescriptions.\n";
        return;
    }

    string id;
    cout << "🆔 Enter Personal ID: ";
    getline(cin, id);

    for (auto& patient : patients) {
        if (patient.personalID == id) {
            cout << "\n🔍 Patient found: " << patient.firstName << " " << patient.lastName << "\n";

            if (!patient.prescriptions.empty()) {
                cout << "📋 Existing prescriptions:\n";
                for (int i = 0; i < patient.prescriptions.size(); ++i) {
                    cout << "  " << (i + 1) << ". " << patient.prescriptions[i]
                         << " (Quantity: " << patient.quantities[i] << ")\n";
                }
            } else {
                cout << "⚠️  No prescriptions yet for this patient.\n";
            }

            cout << "\n📝 Enter prescription name to add: ";
            string prescriptionName;
            getline(cin, prescriptionName);

            int quantity;
            cout << "🔢 Enter quantity allowed: ";
            while (!(cin >> quantity) || quantity < 1) {
                cout << "❌ Invalid input. Please enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            patient.prescriptions.push_back(prescriptionName);
            patient.quantities.push_back(quantity);

            cout << "\n✅ Prescription added successfully.\n";
            return;
        }
    }

    cout << "\n❌ No patient found with the provided Personal ID.\n";
}

// ====================
// Displays all prescriptions for a specific patient
// ====================
void showPrescriptions(const vector<Person>& patients) {
    clearScreen();
    printLine('=', 60);
    cout << setw(42) << "🔍 Show Patient Prescriptions 🔍\n";
    printLine('=', 60);

    if (patients.empty()) {
        cout << "\n⚠️  No patients registered.\n";
        return;
    }

    string id;
    cout << "🆔 Enter Personal ID of the patient: ";
    getline(cin, id);

    for (const auto& patient : patients) {
        if (patient.personalID == id) {
            cout << "\n👤 Patient: " << patient.firstName << " " << patient.lastName << "\n";

            if (patient.prescriptions.empty()) {
                cout << "⚠️  No prescriptions found for this patient.\n";

            } else {
                // Print table header
                printLine('-', 60);
                cout << left << setw(6) << "No." << setw(35) << "Prescription Name" << setw(15) << "Quantity" << "\n";
                printLine('-', 60);

                // Print all prescriptions
                for (int i = 0; i < patient.prescriptions.size(); ++i) {
                    cout << left << setw(6) << (i + 1)
                         << setw(35) << patient.prescriptions[i] 
                         << setw(15) << patient.quantities[i] << "\n";
                }
                printLine('=', 60);
            }
            return;
        }
    }

    cout << "\n❌ No patient found with the given Personal ID.\n";
}

// ====================
// Main program loop
// ====================
int main() {
    vector<Person> patients;
    int choice;

    do {
        clearScreen();
        showMainMenu();

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 0 and 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                clearScreen();
                registerPatient(patients);
                break;
            case 2:
            clearScreen();
                displayPatients(patients);
                break;
            case 3:
            clearScreen();
                removePatient(patients);
                break;
            case 4:
            clearScreen();
                addPrescription(patients);
                break;
            case 5:
            clearScreen();
                showPrescriptions(patients);
                break;
            case 0:
                clearScreen();
                printLine('=');
                cout << setw(40) << "Thank you for using the system. Goodbye!\n";
                printLine('=');
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress ENTER to return to the main menu...";
            cin.get();
        }

    } while (choice != 0);

    return 0;
}
