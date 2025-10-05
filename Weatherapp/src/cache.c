#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "cache.h"
#include "utils.h"
#include "cities.h"
#include <string.h>
#include <sys/stat.h>   // För mkdir på macOS/Linux

// === Läs sparad JSON till STACK ===
void lasJSONStack(const char *stad) {
    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s_weather.json", stad);

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ Kunde inte öppna %s\n", filename);
        return;
    }

    char buffer[10000];
    size_t n = fread(buffer, 1, sizeof(buffer) - 1, f);
    buffer[n] = '\0';
    fclose(f);

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        printf("❌ Kunde inte tolka JSON.\n");
        return;
    }

    printf("📂 (STACK) Läste JSON för %s\n", stad);
    cJSON_Delete(json);
}

// === Läs sparad JSON till HEAP ===
void lasJSONHeap(const char *stad) {
    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s_weather.json", stad);

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ Kunde inte öppna %s\n", filename);
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        printf("❌ Kunde inte tolka JSON.\n");
        free(buffer);
        return;
    }

    printf("📂 (HEAP) Läste JSON för %s\n", stad);
    cJSON_Delete(json);
    free(buffer);
}

// === Spara JSON till fil ===
void saveJSON(const char *stad, const char *data) {
    // Skapa cache-mapp om den inte finns
#ifdef _WIN32
    _mkdir("cache");
#else
    mkdir("cache", 0777);
#endif

    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s_weather.json", stad);

    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("❌ Kunde inte spara till %s\n", filename);
        return;
    }

    fwrite(data, 1, strlen(data), f);
    fclose(f);

    printf("💾 Sparade väderdata till %s\n", filename);
}

void Stack() {
    while (1) {
        clearScreen();
        visaStader();

        int val;
        printf("👉 Välj en stad (nummer, 0 för att gå tillbaka): ");
        if (scanf("%d", &val) != 1) {
            printf("❌ Felaktig inmatning.\n");
            break;
        }

        if (val == 0)
            break;

        if (val < 1 || val > antalStader) {
            printf("❌ Ogiltigt val.\n");
            waitForEnter();
            continue;
        }

        char stad[100];
        sscanf(stader[val - 1], "%99[^:]", stad);
        lasJSONStack(stad);
        waitForEnter();
    }
}

void Heap() {
    while (1) {
        clearScreen();
        visaStader();

        int val;
        printf("👉 Välj en stad (nummer, 0 för att gå tillbaka): ");
        if (scanf("%d", &val) != 1) {
            printf("❌ Felaktig inmatning.\n");
            break;
        }

        if (val == 0)
            break;

        if (val < 1 || val > antalStader) {
            printf("❌ Ogiltigt val.\n");
            waitForEnter();
            continue;
        }

        char stad[100];
        sscanf(stader[val - 1], "%99[^:]", stad);
        lasJSONHeap(stad);
        waitForEnter();
    }
}
