#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "login.h"
#include "utils.h"
#include "weather.h"
#include "cache.h"
#include "cities.h"

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    int choice;

    // 🔐 Startar inloggning
    login();

    while (true) {
        clearScreen();

        printf("═══════════════════════════════════════════════════════════════\n");
        printf("            🌤️  VÄDERHÄMTARE FÖR SVENSKA STÄDER  🌤️\n");
        printf("═══════════════════════════════════════════════════════════════\n");
        tiden();
        printf("═══════════════════════════════════════════════════════════════\n\n");

        printf("🌍  HUVUDMENY:\n\n");
        printf("\n1️⃣  🚪 Avsluta programmet\n");
        printf("\n2️⃣  ☀️  Hämta väder för vald stad\n");
        printf("\n3️⃣  🆘 Hjälp / Instruktioner\n");
        printf("\n4️⃣  ℹ️  Om programmet\n\n");
printf("═══════════════════════════════════════════════════════════════\n\n");
        printf("\n💾  KONTO & LAGRING:\n\n");
        printf("\n5️⃣  👤 Skapa ett konto\n");
        printf("\n6️⃣  📂 Visa alla konton\n");
        printf("\n7️⃣  📄 Läs sparad JSON (🧠 Stack)\n");
        printf("\n8️⃣  💾 Läs sparad JSON (📦 Heap)\n");

        printf("\n═══════════════════════════════════════════════════════════════\n");
        printf(" 👉 Ange ditt val (1–10): ");

        if (scanf("%d", &choice) != 1) {
            clearScreen();
            printf("\n❌ Felaktig inmatning. Endast siffror tillåtna!\n\n");
            while (getchar() != '\n'); // rensa inmatningsbufferten
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                printf("═══════════════════════════════════════════════════════════════\n");
                printf(" 👋 Tack för att du använde 🌤️ Väderhämtaren.\n");
                printf("    Må Gud välsigna din dag! 🙏✨\n");
                printf("═══════════════════════════════════════════════════════════════\n\n");
                curl_global_cleanup();
                return 0;

            case 2:
                clearScreen();
                hamtaVader();
                waitForEnter();
                break;

            case 3:
                clearScreen();
                showHelp();
                waitForEnter();
                break;

            case 4:
                clearScreen();
                showAbout();
                waitForEnter();
                break;

            case 5:
                clearScreen();
                createLogin();
                waitForEnter();
                break;

            case 6:
                clearScreen();
                showlogin();
                waitForEnter();
                break;

            case 7:
                clearScreen();
                Stack();
                waitForEnter();
                break;

            case 8:
                clearScreen();
                Heap();
                waitForEnter();
                break;

            default:
                clearScreen();
                printf("❌ Ogiltigt val. Ange en siffra mellan 1 och 10.\n");
                waitForEnter();
                break;
        }
    }

    curl_global_cleanup();
    return 0;
}
