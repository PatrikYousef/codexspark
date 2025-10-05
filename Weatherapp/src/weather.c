#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "weather.h"
#include "utils.h"
#include "cache.h"
#include "cities.h"

struct Memory {
    char *response;
    size_t size;
};

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

#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include "utils.h"
#include "weather.h"

void hanteraAPIFel(cJSON *root) {
    cJSON *error = cJSON_GetObjectItem(root, "error");
    if (cJSON_IsTrue(error)) {
        cJSON *reason = cJSON_GetObjectItem(root, "reason");
        if (cJSON_IsString(reason))
            printf("❌ API-fel: %s\n", reason->valuestring);
        else
            printf("❌ Okänt API-fel.\n");
    }
}

void visaAktuelltVader(cJSON *cw) {
    if (!cw) return;

    printf("\n=====================================================\n");
    printf(" 📊 Aktuellt väder just nu 📊 \n");
    printf("=====================================================\n\n");

    cJSON *temp = cJSON_GetObjectItem(cw, "temperature");
    cJSON *wind = cJSON_GetObjectItem(cw, "windspeed");
    cJSON *dir  = cJSON_GetObjectItem(cw, "winddirection");
    cJSON *wcode= cJSON_GetObjectItem(cw, "weathercode");

    if (cJSON_IsNumber(temp))
        printf(" 🌡️ Temperatur: %.1f °C\n", temp->valuedouble);
    if (cJSON_IsNumber(wind))
        printf(" 💨 Vind: %.1f m/s\n", wind->valuedouble);
    if (cJSON_IsNumber(dir))
        printf(" 🧭 Vindriktning: %.0f°\n", dir->valuedouble);
    if (cJSON_IsNumber(wcode))
        printf(" 🌦️ Väder: %s\n", oversattVaderkod(wcode->valueint));
}

void visaDagligPrognos(cJSON *daily) {
    if (!daily) return;

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
    printf(" 📅 Prognos för %d dagar framåt \n", dagar);
    printf("-----------------------------------------------------\n\n");

    for (int i = 0; i < dagar; i++) {
        const char *datum = cJSON_GetArrayItem(dates, i)->valuestring;
        printf("📅 %s\n", datum);

        if (tmax && tmin) {
            double max = cJSON_GetArrayItem(tmax, i)->valuedouble;
            double min = cJSON_GetArrayItem(tmin, i)->valuedouble;
            printf(" 📈 Max temp: %.1f°C\n", max);
            printf(" 📉 Min temp: %.1f°C\n", min);
        }

        if (sunrise && sunset) {
            printf(" 🌅 Soluppgång: %s\n", cJSON_GetArrayItem(sunrise, i)->valuestring);
            printf(" 🌇 Solnedgång: %s\n", cJSON_GetArrayItem(sunset, i)->valuestring);
        }

        if (uv)
            printf(" 🔆 UV-index: %.1f\n", cJSON_GetArrayItem(uv, i)->valuedouble);
        if (rain)
            printf(" 🌧️ Nederbörd: %.1f mm\n", cJSON_GetArrayItem(rain, i)->valuedouble);
        if (snow)
            printf(" ❄️ Snöfall: %.1f cm\n", cJSON_GetArrayItem(snow, i)->valuedouble);
        if (windmax)
            printf(" 💨 Maxvind: %.1f m/s\n", cJSON_GetArrayItem(windmax, i)->valuedouble);
        if (phours)
            printf(" ⏳ Nederbördstimmar: %.0f h\n", cJSON_GetArrayItem(phours, i)->valuedouble);

        if (sunshine) {
            int sek = cJSON_GetArrayItem(sunshine, i)->valueint;
            char buff[20];
            formatTid(sek, buff, sizeof(buff));
            printf(" 🌞 Soltimmar: %s\n", buff);
        }
        printf("-----------------------------------------------------\n\n");
    }
}

void visaTimvisPrognos(cJSON *hourly) {
    if (!hourly) return;

    cJSON *htimes = cJSON_GetObjectItem(hourly, "time");
    cJSON *htemp  = cJSON_GetObjectItem(hourly, "temperature_2m");
    cJSON *hwind  = cJSON_GetObjectItem(hourly, "windspeed_10m");
    cJSON *hcode  = cJSON_GetObjectItem(hourly, "weathercode");

    int timmar = cJSON_GetArraySize(htimes);
    printf("\n-----------------------------------------------------\n");
    printf(" ⏰ Timvis prognos (nästa 24 timmar) \n");
    printf("-----------------------------------------------------\n\n");
    printf(" %-16s %-10s %-12s %-15s\n", "Tid", "Temp", "Vind", "Väder");
    printf(" -------------------------------------------------\n");

    for (int i = 0; i < 24 && i < timmar; i++) {
        const char *tid = cJSON_GetArrayItem(htimes, i)->valuestring;
        double temp = cJSON_GetArrayItem(htemp, i)->valuedouble;
        double wind = cJSON_GetArrayItem(hwind, i)->valuedouble;
        int code = cJSON_GetArrayItem(hcode, i)->valueint;

        const char *klock = strchr(tid, 'T');
        if (klock) klock++; else klock = tid;

        printf(" %-16s 🌡️ %-6.1f°C 💨 %-6.1f m/s %s\n",
               klock, temp, wind, oversattVaderkod(code));
    }
}

void visaVaderdata(const char *json) {
    cJSON *root = cJSON_Parse(json);
    if (!root) {
        printf("❌ Kunde inte tolka JSON.\n");
        return;
    }

    hanteraAPIFel(root);

    cJSON *cw = cJSON_GetObjectItem(root, "current_weather");
    visaAktuelltVader(cw);

    cJSON *daily = cJSON_GetObjectItem(root, "daily");
    visaDagligPrognos(daily);

    cJSON *hourly = cJSON_GetObjectItem(root, "hourly");
    visaTimvisPrognos(hourly);

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
        "&hourly=temperature_2m,windspeed_10m,weathercode"
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
