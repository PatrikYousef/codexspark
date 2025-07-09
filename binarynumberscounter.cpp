#include <iostream>
#include <string>

using namespace std;

int main() {
    string binary;
    
    // Display a formatted header for the program
    cout << "======================================" << endl;
    cout << "     BINARY TO DECIMAL CONVERTER" << endl;
    cout << "======================================" << endl;

    // Prompt the user to enter an 8-bit binary number
    cout << "Enter an 8-bit binary number (e.g., 00011101): ";
    cin >> binary;

    
    // Validate the input:
    // - Must be exactly 8 characters long
    // - Must contain only '0' and '1' characters
    if (binary.length() != 8 || binary.find_first_not_of("01") != string::npos) {
        cout << "\n[ Error ] Invalid input! Please enter exactly 8 digits (0 or 1 only)." << endl;
        return 1; // Exit with error code
    }

    // Convert the binary string to a decimal integer
    // stoi() with base 2 interprets the string as a binary number
    int decimal = stoi(binary, nullptr, 2);

    // Display the original binary input and its decimal equivalent
    cout << "\n--------------------------------------" << endl;
    cout << " Binary Input : " << binary << endl;
    cout << " Decimal Value: " << decimal << endl;
    cout << "--------------------------------------" << endl;

    return 0; // Successful execution
}
