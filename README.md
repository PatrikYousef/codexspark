# Bank Account Management System (C++ Console App) bankaccount.cpp
---

## 📋 Projektbeskrivning

En enkel och användarvänlig konsolapplikation skriven i C++ för att skapa och hantera bankkonton och användare.  
Perfekt som ett läroprojekt för att visa grundläggande programmeringskoncept som datastrukturer, funktioner, användarhantering, säkerhet och användargränssnitt i terminalen.

---

## 🚀 Funktioner

- **Användarhantering**  
  - Skapa och ta bort användarkonton med unika användarnamn  
- **Bankkonton**  
  - Skapa konto med automatiskt genererade kontonummer, CVV och PIN-kod  
  - Ange bankens namn och kontoinnehavarens namn  
  - Visa konton i snygg tabell  
  - Ta bort konto baserat på kundens förnamn  
- **Pengarhantering**  
  - Sätt in och ta ut pengar med PIN-autentisering  
  - Kontroll av saldo vid uttag  
- **Användarvänligt gränssnitt**  
  - Menyer med val, tydlig layout och emojis för bättre upplevelse  
  - Automatisk rensning av skärm för ökad läsbarhet

---

## 📦 Kom igång

### Kompilera och kör

1. Klona repo eller ladda ner koden.  
2. Kompilera med valfri C++-kompilator (t.ex. g++):

```bash
g++ -o bankapp main.cpp
Kör programmet:
./bankapp
Användning
Följ menyn för att skapa användare och bankkonton.
Hantera pengar med insättning och uttag via PIN-kod.
Visa eller ta bort konton enkelt.
📖 Exempel på meny
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
🔧 Tekniker och bibliotek
C++ Standardbibliotek
Konsolbaserat användargränssnitt
Slumpgenerering för kontonummer, CVV och PIN-kod

```

# GitHub Stats Tracker (C++ Console App) GitHubStatsTracker.cpp



---

## 🚀 Projektbeskrivning

Ett terminalbaserat C++-program för att manuellt spåra statistik från dina GitHub-projekt.  
GitHub visar trafikdata bara för de senaste 14 dagarna — detta verktyg hjälper dig att logga och analysera data över tid, inklusive:

- Antal **kloner**
- Antal **unika kloner**
- Antal **visningar**
- Totalt antal **projekt**

---

## 🛠️ Funktioner

- 📥 **Lägg till nya statistikvärden** för projekt  
- 📊 **Visa total statistik** och nyckeltal per projekt  
- ♻️ **Återställ alla sparade data**  
- 🕓 **Visa historik** med tidsstämplar  
- 🚪 Enkel och tydlig menystyrning med emojis och layout  
- Plattformoberoende skärmhantering (Windows / Unix)

---

## 📥 Kom igång

### Bygga och köra

1. Klona eller ladda ner projektet.  
2. Kompilera med exempelvis `g++`:

```bash
g++ -o github_tracker main.cpp
Kör programmet:
./github_tracker
📋 Användning
Programmet visar en enkel meny:
[1] ➕  Add Project Stats
[2] 📊  Show Total Stats
[3] ♻️   Reset All Stats
[4] ❌  Exit Program
[5] 🕓  View Project Log


