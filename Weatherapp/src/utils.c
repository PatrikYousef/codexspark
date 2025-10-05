#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <string.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    printf("\nTryck [Enter] för att fortsätta...");
    getchar();
    getchar();
}

void formatTid(int sekunder, char *buff, size_t buffsize) {
    int timmar = sekunder / 3600;
    int minuter = (sekunder % 3600) / 60;
    snprintf(buff, buffsize, "%dh %dmin", timmar, minuter);
}

const char* oversattVaderkod(int code) {
    switch (code) {
        case 0: return "☀️ Klart";
        case 1: case 2: case 3: return "⛅ Molnigt";
        case 45: case 48: return "🌫️ Dimma";
        case 51: case 53: case 55: return "🌦️ Duggregn";
        case 61: case 63: case 65: return "🌧️ Regn";
        case 71: case 73: case 75: return "❄️ Snöfall";
        case 80: case 81: case 82: return "🌧️ Skurar";
        case 95: return "⛈️ Åska";
        default: return "❓ Okänt väder";
    }
}

// === Hjälp- och informationsmenyer ===


void showHelp() {
    clearScreen();

    printf("═══════════════════════════════════════════════════════════════\n");
    printf("                     🆘  HJÄLPMENY  🆘\n");
    printf("═══════════════════════════════════════════════════════════════\n\n");

    printf("💡  Välkommen till hjälpmenyn för 🌤️  *Väderhämtare för Svenska Städer*!\n");
    printf("Här får du en överblick över hur du använder programmet och vad varje menyval gör:\n\n");

    // --- Huvudfunktioner ---
    printf("🌍  HUVUDFUNKTIONER:\n");
    printf("➡️  2️⃣  ☀️  *Hämta väder för vald stad*\n");
    printf("     - Hämtar väderdata från Open-Meteo API.\n");
    printf("     - Visar temperatur, vind, UV-index och prognos för flera dagar.\n\n");

    printf("➡️  3️⃣  🆘  *Hjälp / Instruktioner*\n");
    printf("     - Visar denna hjälpmeny med information om programmets funktioner.\n\n");

    printf("➡️  4️⃣  ℹ️  *Om programmet*\n");
    printf("     - Information om utvecklaren och syftet bakom projektet.\n\n");

    // --- Konton & lagring ---
    printf("💾  KONTO & LAGRING:\n");
    printf("➡️  5️⃣  👤  *Skapa ett konto*\n");
    printf("     - Låter dig skapa en användarprofil för personlig användning.\n\n");

    printf("➡️  6️⃣  📂  *Visa alla konton*\n");
    printf("     - Visar en lista över alla sparade användarkonton.\n\n");

    // --- Stack & Heap förklaringar ---
    printf("➡️  7️⃣  📄  *Läs sparad JSON (🧠 Stack)*\n");
    printf("     - Läser tidigare sparad väderdata direkt till stack-minnet.\n");
    printf("     - Används för snabb visning av små filer, lagras temporärt i RAM.\n\n");

    printf("➡️  8️⃣  💾  *Läs sparad JSON (📦 Heap)*\n");
    printf("     - Läser samma data, men via heap-minnet med dynamisk allokering.\n");
    printf("     - Används för att hantera större filer eller mer komplexa data.\n\n");

    // --- Övrigt ---
    printf("⚙️  ÖVRIGT:\n");
    printf("➡️  9️⃣  🕒  *Visa tid och datum*\n");
    printf("     - Visar aktuell systemtid med en snygg layout.\n\n");

    printf("➡️  🔟  🧹  *Rensa cache*\n");
    printf("     - (Kommande funktion) Tar bort gamla väderfiler från cache-mappen.\n\n");

    printf("═══════════════════════════════════════════════════════════════\n");
    printf("📘  TIPS:\n");
    printf("     - Du kan använda både Stack och Heap för att lära dig minneshantering i C.\n");
    printf("     - Väderdata sparas automatiskt i mappen 'cache/'.\n");
    printf("     - Använd 'Om programmet' för att läsa mer om utvecklingen och syftet.\n");
    printf("═══════════════════════════════════════════════════════════════\n\n");

    waitForEnter();
}

void showAbout() {
    clearScreen();
    printf("\n=====================================================\n");
    printf("                   🌤️  Om WeatherApp                \n");
    printf("=====================================================\n\n");
    printf("🙏  Byggd för att kombinera C-programmering och tro\n");
    printf("🌍  Data från Open-Meteo API (gratis väderdata)\n");
    printf("💾  JSON-data sparas i 'cache/'-mappen\n");
    printf("\n=====================================================\n");
    waitForEnter();
}

void tiden() {
    time_t t; struct tm *info; char buffer[80];
    time(&t); info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info);
    printf("        ⏰ Aktuell tid: %s\n", buffer);
}
