# Binary to Decimal Converter binarynumberscounter.cpp

A simple C++ console application that converts an 8-bit binary number (entered as a string) to its decimal equivalent.

---

## Features

- **Input validation:** Ensures the binary string is exactly 8 characters long and contains only `0` or `1`.
- **User-friendly interface:** Clear prompts, formatted headers, and informative error handling.
- **Fast conversion:** Uses C++’s `stoi` function for efficient base-2 to decimal conversion.

---

## Usage

1. **Compile the program:**  
   ```bash
   g++ -o binary_converter main.cpp
   ```

2. **Run the program:**  
   ```bash
   ./binary_converter
   ```

3. **Follow the prompts:**  
   - Enter an 8-bit binary number (e.g., `00011101`).
   - The program will display the decimal equivalent.

---

## Example

```
======================================
     BINARY TO DECIMAL CONVERTER
======================================
Enter an 8-bit binary number (e.g., 00011101): 00011101

--------------------------------------
 Binary Input : 00011101
 Decimal Value: 29
--------------------------------------
```

---

## Input Validation

- **Valid Input:** Exactly 8 digits, each must be `0` or `1`.
- **Invalid Input:** Any other format results in an error message and program exit.

---

## Technologies Used

- C++ Standard Library (`iostream`, `string`)
- C++11 or later (for `stoi` with base)

---




