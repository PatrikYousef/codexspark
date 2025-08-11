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
```

## Royal Hotel Bokningssystem 

🏨 Välkommen till **Royal Hotel Bokningssystem** — en enkel och användarvänlig C++-konsolapplikation för att hantera hotellbokningar, rumstilldelningar och gästinformation på ett effektivt sätt.

---

## Funktioner

- 🧾 Lägg till nya gäster med information som förnamn, efternamn, personnummer, antal dagar och rumsnummer.
- 📋 Visa en komplett lista över alla gäster med deras bokningsdetaljer.
- 🔍 Sök efter en gäst via personnummer för snabb åtkomst till bokningsinformation.
- 🛠️ Uppdatera gästens information om du råkat lägga in fel data.
- 🏨 Visa en tydlig rumskarta som visar vilka rum (0-99) som är lediga (✅) eller bokade (❌).
- ✅ Validering av inmatning för att säkerställa korrekt data.
- ✨ Användarvänligt gränssnitt med emojis för tydlig navigering och bättre användarupplevelse.
- 💰 Automatisk beräkning av totalpris baserat på antal dagar.

---

🏨💫═════════════════════════════════════════════════════════════════════════💫🏨
🌟                     WELCOME TO THE ROYAL HOTEL BOOKING SYSTEM            🌟
🏨💫═════════════════════════════════════════════════════════════════════════💫🏨

🛎️  Please select an option below to continue:

1️⃣  ➤ 🧾 Add New Guest to the Hotel
2️⃣  ➤ 📋 View All Guests (Guest List)
3️⃣  ➤ 🔍 Search Guest by Personal Number
4️⃣  ➤ 🛠️ Update Guest Details
5️⃣  ➤ 🏨 Show Room Status Map
6️⃣  ➤ ❌ Exit the Booking System

👉 Enter your choice (1–6):

# 📚 Bibliotekssystem i C++

Välkommen till detta enkla och användarvänliga **bibliotekssystem** utvecklat i C++. Programmet hanterar böcker, användare och lånefunktioner via ett terminalgränssnitt med tydliga menyer och emojis.

---

## Funktioner

- ➕ Lägg till nya böcker med namn, bokkod och antal exemplar.
- 📖 Visa alla registrerade böcker i biblioteket.
- ➕ Lägg till nya användare med förnamn, efternamn, personnummer, användarnamn och lösenord.
- 👥 Visa alla registrerade användare.
- 📚 Låna ut böcker till registrerade användare baserat på personnummer och bokkod.
- 🔍 Sök efter böcker via bokkod.
- 🔍 Sök efter användare via personnummer.
- 📜 Visa bibliotekets regler för utlåning.
- 📚 Visa böcker som en användare har lånat.
- ❌ Avsluta programmet.

---

