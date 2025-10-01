#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdbool.h>
#include "weather.h"
#include "utils.h"

struct Memory {
    char *response;
    size_t size;
};

// Lista städer
static const char *stader[] = {
    "Stockholm:59.3293:18.0686", "Göteborg:57.7089:11.9746", "Malmö:55.6050:13.0038",
    "Uppsala:59.8586:17.6389", "Västerås:59.6099:16.5448", "Örebro:59.2741:15.2066",
    "Linköping:58.4109:15.6216", "Helsingborg:56.0465:12.6945", "Jönköping:57.7815:14.1562",
    "Norrköping:58.5877:16.1924", "Lund:55.7047:13.1910", "Gävle:60.6749:17.1413",
    "Sundsvall:62.3908:17.3069", "Umeå:63.8258:20.2630", "Luleå:65.5848:22.1567",
    "Kiruna:67.8558:20.2253"
};

static int antalStader = sizeof(stader) / sizeof(stader[0]);

#include "cJSON.h"
#include <sys/stat.h>

// Läs sparad JSON till STACK
void lasJSONStack(const char *stad) {
    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s_weather.json", stad);

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("❌ Kunde inte öppna %s\n", filename);
        return;
    }

    char buffer[10000]; // stack
    size_t n = fread(buffer, 1, sizeof(buffer)-1, f);
    buffer[n] = '\0';
    fclose(f);

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        printf("❌ Kunde inte tolka JSON.\n");
        return;
    }
    printf("📂 (STACK) Lyckades läsa sparad JSON för %s\n", stad);

    cJSON_Delete(json);
}

// Läs sparad JSON till HEAP
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

    char *buffer = malloc(size + 1); // heap
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        printf("❌ Kunde inte tolka JSON.\n");
        free(buffer);
        return;
    }
    printf("📂 (HEAP) Lyckades läsa sparad JSON för %s\n", stad);

    cJSON_Delete(json);
    free(buffer);
}

// Enkel callback för att spara data från libcurl i minnet.
static size_t WriteCallback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t bytes = size * nmemb;
    if (bytes == 0) return 0;
    
    struct Memory *mem = userp;
    char *newbuf = realloc(mem->response, mem->size + bytes + 1);
    if (!newbuf) return 0;
    
    mem->response = newbuf;
    memcpy(mem->response + mem->size, data, bytes);
    mem->size += bytes;
    mem->response[mem->size] = '\0';
    
    return bytes;
}

void Stack() {
    while (true) {
        clearScreen();
        visaStader();                     
        int val;
        printf("👉 Välj en stad (nummer, 0 för att gå tillbaka): ");
        if (scanf("%d", &val) != 1) {
            printf("❌ Felaktig inmatning.\n");
            break;
        }

        if (val == 0) {
            break;
        }

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
    while (true) {
        clearScreen();
        visaStader();                     
        int val;
        printf("👉 Välj en stad (nummer, 0 för att gå tillbaka): ");
        if (scanf("%d", &val) != 1) {
            printf("❌ Felaktig inmatning.\n");
            break;
        }

        if (val == 0) {
            break; 
        }

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

void visaStader() {
    printf("\n=====================================================\n");
    printf("             🌍  Tillgängliga städer  🌍             \n");
    printf("=====================================================\n\n");

    for (int i = 0; i < antalStader; i++) {
        char namn[100];
        sscanf(stader[i], "%99[^:]", namn);

        printf(" %2d) 🏙️  %-20s\n", i + 1, namn);
    }

    printf("\n=====================================================\n");
    printf("   📌 Välj en stad genom att ange dess nummer\n");
    printf("=====================================================\n\n");
}

static const char* oversattVaderkod(int code) {
    switch (code) {
        case 1: case 2: case 3: return "⛅ Molnigt";
        case 45: case 48: return "🌫️ Dimma";
        case 51: case 53: case 55: return "🌦️ Duggregn";
        case 61: case 63: case 65: return "🌧️ Regn";
        case 71: case 73: case 75: return "❄️ Snöfall";
        case 80: case 81: case 82: return "🌧️ Skurar";
        case 95: return "⛈️ Åska";
        case 0: return "☀️ Klart";
        default: return "❓ Okänt väder";
    }
}

void formatTid(int sekunder, char *buff, size_t buffsize) {
    int timmar = sekunder / 3600;
    int minuter = (sekunder % 3600) / 60;
    snprintf(buff, buffsize, "%dh %dmin", timmar, minuter);
}



void visaVaderdata(const char *json) {
    cJSON *root = cJSON_Parse(json);
    if (!root) {
        printf("❌ Kunde inte tolka JSON.\n");
        return;
    }

    // ===== API-fel =====
    cJSON *error = cJSON_GetObjectItem(root, "error");


    if (cJSON_IsTrue(error)) {
        cJSON *reason = cJSON_GetObjectItem(root, "reason");
        if (cJSON_IsString(reason)) {
            printf("❌ API-fel: %s\n", reason->valuestring);
        } else {
            printf("❌ Okänt API-fel.\n");
        }
        cJSON_Delete(root);
        return;
    }

    // ===== Aktuellt väder =====
    cJSON *cw = cJSON_GetObjectItem(root, "current_weather");


    if (cw) {
        printf("\n=====================================================\n");
        printf("              📊  Aktuellt väder just nu  📊         \n");
        printf("=====================================================\n\n");

        cJSON *temp = cJSON_GetObjectItem(cw, "temperature");
        cJSON *wind = cJSON_GetObjectItem(cw, "windspeed");
        cJSON *dir  = cJSON_GetObjectItem(cw, "winddirection");
        cJSON *wcode= cJSON_GetObjectItem(cw, "weathercode");

        if (cJSON_IsNumber(temp))
            printf(" 🌡️  Temperatur:   %.1f °C\n", temp->valuedouble);
        if (cJSON_IsNumber(wind))
            printf(" 💨 Vind:          %.1f m/s\n", wind->valuedouble);
        if (cJSON_IsNumber(dir))
            printf(" 🧭 Vindriktning:  %.0f°\n", dir->valuedouble);
        if (cJSON_IsNumber(wcode))
            printf(" 🌦️  Väder:        %s\n", oversattVaderkod(wcode->valueint));
    }

    // ===== Prognos för flera dagar =====
    cJSON *daily = cJSON_GetObjectItem(root, "daily");

    
    if (daily) {
        cJSON *dates   = cJSON_GetObjectItem(daily, "time");
        cJSON *sunrise = cJSON_GetObjectItem(daily, "sunrise");
        cJSON *sunset  = cJSON_GetObjectItem(daily, "sunset");
        cJSON *tmax    = cJSON_GetObjectItem(daily, "temperature_2m_max");
        cJSON *tmin    = cJSON_GetObjectItem(daily, "temperature_2m_min");
        cJSON *uv      = cJSON_GetObjectItem(daily, "uv_index_max");
        cJSON *rain    = cJSON_GetObjectItem(daily, "precipitation_sum");
        cJSON *snow    = cJSON_GetObjectItem(daily, "snowfall_sum");
        cJSON *windmax = cJSON_GetObjectItem(daily, "windspeed_10m_max");
        cJSON *phours  = cJSON_GetObjectItem(daily, "precipitation_hours");
        cJSON *sunshine= cJSON_GetObjectItem(daily, "sunshine_duration");

        int dagar = cJSON_GetArraySize(dates);

        printf("\n-----------------------------------------------------\n");
        printf("         📅 Prognos för %d dagar framåt              \n", dagar);
        printf("-----------------------------------------------------\n\n");

        for (int i = 0; i < dagar; i++) {
            const char *datum = cJSON_GetArrayItem(dates, i)->valuestring;
            printf("📅 %s\n", datum);

            if (tmax && tmin) {
                double max = cJSON_GetArrayItem(tmax, i)->valuedouble;
                double min = cJSON_GetArrayItem(tmin, i)->valuedouble;
                printf("   📈 Max temp:       %.1f°C\n", max);
                printf("   📉 Min temp:       %.1f°C\n", min);
            }
            if (sunrise && sunset) {
                printf("   🌅 Soluppgång:     %s\n", cJSON_GetArrayItem(sunrise, i)->valuestring);
                printf("   🌇 Solnedgång:     %s\n", cJSON_GetArrayItem(sunset, i)->valuestring);
            }
            if (uv)
                printf("   🔆 UV-index:       %.1f\n", cJSON_GetArrayItem(uv, i)->valuedouble);
            if (rain)
                printf("   🌧️ Nederbörd:      %.1f mm\n", cJSON_GetArrayItem(rain, i)->valuedouble);
            if (snow)
                printf("   ❄️ Snöfall:        %.1f cm\n", cJSON_GetArrayItem(snow, i)->valuedouble);
            if (windmax)
                printf("   💨 Maxvind:        %.1f m/s\n", cJSON_GetArrayItem(windmax, i)->valuedouble);
            if (phours)
                printf("   ⏳ Nederbördstimmar: %.0f h\n", cJSON_GetArrayItem(phours, i)->valuedouble);
            if (sunshine) {
                int sek = cJSON_GetArrayItem(sunshine, i)->valueint;
                char buff[20];
                formatTid(sek, buff, sizeof(buff));
                printf("   🌞 Soltimmar:      %s\n", buff);
            }

            printf("-----------------------------------------------------\n\n");
        }
    }

    // ===== Prognos per timme =====
    cJSON *hourly = cJSON_GetObjectItem(root, "hourly");
    if (hourly) {
        cJSON *htimes = cJSON_GetObjectItem(hourly, "time");
        cJSON *htemp  = cJSON_GetObjectItem(hourly, "temperature_2m");
        cJSON *hwind  = cJSON_GetObjectItem(hourly, "windspeed_10m");
        cJSON *hcode  = cJSON_GetObjectItem(hourly, "weathercode");

        int timmar = cJSON_GetArraySize(htimes);

        printf("\n-----------------------------------------------------\n");
        printf("         ⏰ Timvis prognos (nästa 24 timmar)        \n");
        printf("-----------------------------------------------------\n\n");

        printf("   %-16s %-10s %-12s %-15s\n", "Tid", "Temp", "Vind", "Väder");
        printf("   -------------------------------------------------\n");

        for (int i = 0; i < 24 && i < timmar; i++) {
            const char *tid = cJSON_GetArrayItem(htimes, i)->valuestring;
            double temp = cJSON_GetArrayItem(htemp, i)->valuedouble;
            double wind = cJSON_GetArrayItem(hwind, i)->valuedouble;
            int code    = cJSON_GetArrayItem(hcode, i)->valueint;

            // Snygga till tiden: bara "HH:MM"
            const char *klock = strchr(tid, 'T');
            if (klock) klock++; else klock = tid;

            printf("   %-16s 🌡️ %-6.1f°C 💨 %-6.1f m/s %s\n",
                   klock, temp, wind, oversattVaderkod(code));
        }
    }

    printf("\n=====================================================\n\n");
    cJSON_Delete(root);
}

void hamtaVader() {
    visaStader();

    int val;
    printf("👉 Välj en stad (nummer): ");
    if (scanf("%d", &val) != 1) return;

    if (val < 1 || val > antalStader) {
        printf("❌ Ogiltigt val.\n");
        return;
    }

    char stad[100];
    double lat, lon;

    if (sscanf(stader[val - 1], "%99[^:]:%lf:%lf", stad, &lat, &lon) != 3) {
        printf("❌ Kunde inte tolka data för stad %d.\n", val);
        return;
    }

    char url[512];
   snprintf(url, sizeof(url),
    "https://api.open-meteo.com/v1/forecast?"
    "latitude=%.4f&longitude=%.4f"
    "&current_weather=true"
    "&hourly=temperature_2m,relativehumidity_2m,precipitation,cloudcover,pressure_msl,"
    "apparent_temperature,dewpoint_2m,visibility,"
    "windspeed_10m,winddirection_10m,weathercode"
    "&daily=temperature_2m_max,temperature_2m_min,precipitation_sum,uv_index_max,sunrise,sunset"
    "&timezone=auto",
    lat, lon);



    printf("\n🔎 Hämtar väderdata för %s (lat: %.4f, lon: %.4f)\n", stad, lat, lon);

    CURL *curl = curl_easy_init();
    if (!curl) return;

    struct Memory chunk = { .response = malloc(1), .size = 0 };
    if (!chunk.response) {
        curl_easy_cleanup(curl);
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        visaVaderdata(chunk.response);
        saveJSON(stad, chunk.response);
    } else {
        fprintf(stderr, "❌ CURL-fel: %s\n", curl_easy_strerror(res));
    }

    free(chunk.response);
    curl_easy_cleanup(curl);
}
