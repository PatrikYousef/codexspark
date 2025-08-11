# Bank Account Management System (C++ Console App) bankaccount.cpp

En enkel och användarvänlig konsolapplikation i C++ för att hantera bankkonton och användare. Perfekt som ett lärorikt projekt för att visa upp grundläggande och mellanliggande programmeringskoncept som filhantering, objektorientering och säker användarhantering.

---

## Funktioner

- **Användarhantering**  
  - Skapa och ta bort användarkonton (första namn, efternamn, användarnamn, lösenord)  
  - Enkel kontroll av unika användarnamn

- **Bankkonton**  
  - Skapa bankkonto med automatiskt genererat kontonummer (4 grupper av 4 siffror), CVV och PIN-kod  
  - Spara bankens namn och kundens namn  
  - Ange utgångsdatum för kort (MMYY)  
  - Visa alla bankkonton i tabellformat med snygg layout  
  - Ta bort bankkonto via kundens förnamn  

- **Pengarhantering**  
  - Insättning och uttag via PIN-kod-autentisering  
  - Kontroll av saldo vid uttag  
  - Felhantering för ogiltiga belopp eller PIN

- **Användarvänligt gränssnitt**  
  - Menyer med val för att navigera mellan funktioner  
  - Rensning av skärm för bättre läsbarhet  
  - Emoji och symboler för tydlig och trevlig visuell presentation  

---

## Installation och körning

1. **Kompilera** med valfri C++-kompilator, t.ex.:

bash
g++ -o bankapp main.cpp

Exempel
=== User Menu ===
1. Manage accounts (Create/Delete User)
2. Continue to Bank Menu
3. Exit
Your choice: 1

Enter first name: Anna
Enter last name: Svensson
Enter username: anna123
Enter password: hemligt

Account created successfully!

...

🏦 BANK ACCOUNT MENU 🏦

1️⃣  ➤ 🏦 Add bank account
2️⃣  ➤ 📄 Show all accounts
3️⃣  ➤ 🗑️ Delete a bank account
4️⃣  ➤ 💰 Manage funds
5️⃣  ➤ 🚪 Exit
6️⃣  ➤ 🔐 Back to User Menu
Your choice:


