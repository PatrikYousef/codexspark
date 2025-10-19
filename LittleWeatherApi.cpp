#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <curl/curl.h>
#include "jansson.h"

using namespace std;

struct City {
    string name;
    string lat;
    string lon;
};

struct Memory {
    string response;
};

static size_t WriteCallback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t bytes = size * nmemb;
    if (bytes == 0) return 0;
    Memory *mem = static_cast<Memory*>(userp);
    mem->response.append(static_cast<const char*>(data), bytes);
    return bytes;
}

vector<City> cities = {
    {"Stockholm", "59.3293", "18.0686"},
    {"Göteborg", "57.7089", "11.9746"},
    {"Malmö", "55.6050", "13.0038"},
    {"Uppsala", "59.8586", "17.6389"},
    {"Västerås", "59.6099", "16.5448"},
    {"Örebro", "59.2741", "15.2066"},
    {"Linköping", "58.4109", "15.6216"},
    {"Helsingborg", "56.0465", "12.6945"},
    {"Jönköping", "57.7815", "14.1562"},
    {"Norrköping", "58.5877", "16.1924"},
    {"Lund", "55.7047", "13.1910"},
    {"Gävle", "60.6749", "17.1413"},
    {"Sundsvall", "62.3908", "17.3069"},
    {"Umeå", "63.8258", "20.2630"},
    {"Luleå", "65.5848", "22.1567"},
    {"Kiruna", "67.8558", "20.2253"}
};

void visaCities() {
    cout << "\n🌍 Tillgängliga städer:\n";
    for (size_t i = 0; i < cities.size(); ++i)
        cout << i + 1 << ") " << cities[i].name << "\n";
}

City valjStad() {
    visaCities();
    string input;
    cout << "\nVilken stad: ";
    cin >> input;
    for (const auto& c : cities) {
        if (input == c.name) {
            cout << "\n✅ " << c.name << " (Lat: " << c.lat << ", Lon: " << c.lon << ")\n";
            return c;
        }
    }
    cout << "\n⚠️ Stad ej hittad.\n";
    return {"", "", ""};
}

string skapaUrl(const City& city) {
    ostringstream url;
    if (city.lat.empty() || city.lon.empty()) {
        cerr << "❌ Fel: Ingen latitud eller longitud tillgänglig.\n";
        return "";
    }
    url << "https://api.open-meteo.com/v1/forecast?latitude=" << city.lat
        << "&longitude=" << city.lon << "&current_weather=true";
        
    return url.str();
}

void visaJson(const string& json_text) {
    
    json_error_t error;
    json_t *root = json_loads(json_text.c_str(), 0, &error);

    if (!root) {
        cerr << "❌ JSON parse error: " << error.text << " at line " << error.line << endl;
        return;
    }

    json_t *weather = json_object_get(root, "current_weather");
    if (json_is_object(weather)) {
        json_t *temp = json_object_get(weather, "temperature");

        json_t *wind = json_object_get(weather, "windspeed");
        json_t *time = json_object_get(weather, "time");


        cout << "\n🌤️ Aktuellt väder:\n";
        if (json_is_number(temp)){
            cout << "🌡️ Temperatur: " << json_number_value(temp) << " °C\n";
        }

        if (json_is_number(wind)){
            cout << "💨 Vindhastighet: " << json_number_value(wind) << " km/h\n";

        }

        if (json_is_string(time)){
            cout << "🕓 Tid: " << json_string_value(time) << "\n";
        }
    
    } else {
        cout << "\n⚠️ Ingen 'current_weather'-data hittades.\n";
    }

    json_decref(root);
}

void hamtaDataMedCurl(const string& url) {
    if (url.empty()) {
        cerr << "❌ Ingen giltig URL att hämta.\n";
        return;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        cerr << "❌ Curl init fel.\n";
        return;
    }

    Memory chunk;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "❌ Curl fel: " << curl_easy_strerror(res) << endl;
    } else {
        visaJson(chunk.response);
    }

    curl_easy_cleanup(curl);
}

void runcode(){
    City stad = valjStad();
    if (stad.name.empty()) {
        return;
    }

    string url = skapaUrl(stad);
    if (url.empty()) {
        return;
    }

    cout << "\n🌦️ URL: " << url << "\n";
    hamtaDataMedCurl(url);
    cout << "\n✅ Klart!\n";
}

int main() {
    runcode();
    return 0;
}
