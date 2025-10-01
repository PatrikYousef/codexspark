#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <sys/stat.h>
#include "cJSON.h"
#include <sys/stat.h>   // mkdir
#include <sys/types.h>  // mode_t
#ifdef _WIN32
#include <direct.h>
#endif

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    printf("\n👉 Tryck ENTER för att fortsätta...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    getchar();
}

void tiden() {
    time_t t; struct tm *info; char buffer[80];
    time(&t); info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", info);
    printf("        ⏰ Aktuell tid: %s\n", buffer);
}

void showHelp() {
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("ℹ️  Hjälp / Instruktioner:\n");
    printf("───────────────────────────────────────────────────────────────\n");
    printf("\n1️⃣  Avsluta programmet – Stänger ner Väderhämtaren.\n");
    printf("\n2️⃣  Hämta väder för vald stad – Ange stadens namn för aktuell prognos.\n");
    printf("\n3️⃣  Hjälp / Instruktioner – Visar denna hjälptext.\n");
    printf("\n4️⃣  Om programmet – Information om utveckling och syfte.\n");
    printf("\n5️⃣  Visa tid och datum – Hämtar aktuell systemtid och datum.\n");
    printf("\n6️⃣  Skapa ett konto – Registrera en ny användare.\n");
    printf("───────────────────────────────────────────────────────────────\n");
    printf("👉 Ange ett val från huvudmenyn (1-6) för att fortsätta.\n");
    printf("═══════════════════════════════════════════════════════════════\n");
}

void showAbout() {
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("💻 Om programmet:\n");
    printf("  \n🔹 Hämtar väderdata från Open-Meteo API.\n");
    printf("  \n🔹 Stöd för flera svenska städer.\n");
    printf("  \n🔹 Skrivet i C med libcurl och stor omsorg ❤️\n");
    printf("═══════════════════════════════════════════════════════════════\n");
}

void saveJSON(const char *stad, const char *rawJson) {
    // Skapa cache-mapp om den inte finns
    struct stat st = {0};
    if (stat("cache", &st) == -1) {
        mkdir("cache", 0700); // RWX för ägaren
    }

    // Filnamn i cache-mappen
    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s_weather.json", stad);

    // Tolka rå JSON
    cJSON *json = cJSON_Parse(rawJson);
    if (!json) {
        printf("❌ Kunde inte tolka JSON-data.\n");
        return;
    }

    // Konvertera till ”pretty printed” JSON-sträng
    char *formatted = cJSON_Print(json);

    FILE *f = fopen(filename, "w");
    if (f) {
        fprintf(f, "%s", formatted);
        fclose(f);
        printf("💾 Vädret för %s sparades i %s\n", stad, filename);
    } else {
        printf("❌ Kunde inte skapa filen %s\n", filename);
    }

    free(formatted);
    cJSON_Delete(json);
}