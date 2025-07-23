# 👥 Person Manager (C++ Console App) person_manager.cpp

Welcome to **Person Manager**, a C++ console-based application that helps you **manage personal records** in a beautifully formatted, emoji-enhanced, and user-friendly interface. This project is dedicated to the **glory of God** and aims to deliver clean structure and practical utility with creativity and purpose.

---

## ✨ Features

- ➕ **Add New Person** with details like name, age, invoice, and VAT.
- 📋 **View All Persons** with VAT calculations and totals.
- ✏️ **Modify Existing Record** by updating any field interactively.
- 🗑️ **Delete a Person** securely using their personal number.
- 🔍 **Search Person** and view their detailed information.
- ✅ Clean and professional layout using `iomanip` and rich Unicode/emoji formatting.
- 🧼 Clear screen support for both Windows and macOS/Linux.
- 🚦 Input validation ensures smooth and error-free data entry.

---

## 🧾 VAT Calculation

When a person is added or viewed, their **VAT amount and total invoice** are automatically calculated:

```bash
VAT Amount = Invoice * (VAT / 100)
Total = Invoice + VAT Amount

