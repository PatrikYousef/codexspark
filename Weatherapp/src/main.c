#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#include "login.h"
#include "utils.h"
#include "weather.h"

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    int choice;
    login();
    while (true) {
        clearScreen();

        printf("═══════════════════════════════════════════════════════════════\n");
        printf("            🌤️  VÄDERHÄMTARE FÖR SVENSKA STÄDER  🌤️\n");
        printf("═══════════════════════════════════════════════════════════════\n");
        tiden();
        printf("═══════════════════════════════════════════════════════════════\n");
        printf("\n1️⃣  Avsluta programmet\n");
        printf("\n2️⃣  Hämta väder för vald stad\n");
        printf("\n3️⃣  Hjälp / Instruktioner\n");
        printf("\n4️⃣  Om programmet\n");
        printf("\n5️⃣  Visa tid och datum\n");
        printf("\n6️⃣  Skapa ett konto\n");
        printf("\n7️⃣  Visa alla konton\n");
        printf("\n8️⃣  Läs sparad JSON (stack)\n");
        printf("\n9️⃣  Läs sparad JSON (heap)\n");

        printf("═══════════════════════════════════════════════════════════════\n");
        printf(" 👉 Ange ditt val (1-7): ");

        if (scanf("%d", &choice) != 1) {
            clearScreen();
            printf("\n❌ Felaktig inmatning. Endast siffror tillåtna!\n\n");
            break;
        }

        switch (choice) {
            case 1: // Avslutning
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
                tiden();
                waitForEnter();
                break;

            case 6:
                clearScreen();
                createLogin();
                waitForEnter();
                break;
                
            case 7:
                clearScreen();
                showlogin();
                waitForEnter();
                break;
            case 8: 
                Stack();
                waitForEnter();
                break;


            case 9: 
                clearScreen();
                Heap();
                waitForEnter();
                break;


            default:
                clearScreen();
                printf("❌ Ogiltigt val. Ange en siffra mellan 1 och 7.\n");
        }
    }

    curl_global_cleanup();
    return 0;
}
