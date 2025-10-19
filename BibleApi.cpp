#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include "jansson.h"
#include <limits>

using namespace std;

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

string skapaUrl(const string& book, string chapter, int verse) {
    ostringstream url;
    url << "https://bible-api.com/" << book << "+" << chapter << ":" << verse;  // Fixad URL
    return url.str();
}

void visaJson(const string& json_text) {
    
    json_error_t error;
    json_t* root = json_loads(json_text.c_str(), 0, &error);
    if (!root) {
        cerr << "❌ JSON parse error: " << error.text << " at line " << error.line << endl;
        return;
    }

    json_t* verses = json_object_get(root, "verses");
    if (json_is_array(verses)) {
        size_t index;
        json_t* verse;
        json_array_foreach(verses, index, verse) {
            json_t* book = json_object_get(verse, "book_name");
            json_t* chapter = json_object_get(verse, "chapter");
            json_t* verse_num = json_object_get(verse, "verse");
            json_t* text = json_object_get(verse, "text");

            if (json_is_string(book) && json_is_number(chapter) &&
                json_is_number(verse_num) && json_is_string(text)) {

                cout << json_string_value(book) << " "
                     << json_integer_value(chapter) << ":"
                     << json_integer_value(verse_num) << " - "
                     << json_string_value(text) << endl;
            }
        }
    } 
    
    else {
        cout << "⚠️ No 'verses' found.\n";
    }

    json_decref(root); 
}

void hamtaDataMedCurl(const string& url) {

    CURL *curl = curl_easy_init();
    if (!curl) {
        cerr << "❌ Curl init fel.\n";
        return;
    }

    Memory chunk;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "❌ Curl fel: " << curl_easy_strerror(res) << endl;
    } else {
        visaJson(chunk.response);
    }

    curl_easy_cleanup(curl);
}


void fasvar() {
    string book;
    cout << "Book: ";
    getline(cin, book); 
    
    string chapter;
    cout << "Capital: ";
    getline(cin, chapter);  
    
    int verse;
    cout << "Ange vers: ";
    cin >> verse;  
    
 
    for (char& c : book) {
        if (c == ' ') c = '+';
    }
    
    string url = skapaUrl(book, chapter, verse);
    hamtaDataMedCurl(url);
}


int main() {
    fasvar();
    return 0;
}
