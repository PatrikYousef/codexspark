#ifndef WEATHER_H
#define WEATHER_H

#include "cJSON.h"

// Hämtar väderdata via API
void hamtaVader();
void visaVaderdata(const char *json);
void hanteraAPIFel(cJSON *root);
void visaAktuelltVader(cJSON *cw);
void visaDagligPrognos(cJSON *daily);
void visaTimvisPrognos(cJSON *hourly);

#endif
