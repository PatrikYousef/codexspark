#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Skärm- och paushantering
void clearScreen();
void waitForEnter();

// Hjälpfunktioner
void formatTid(int sekunder, char *buff, size_t buffsize);
const char *oversattVaderkod(int code);

// Meny- och hjälpfunktioner
void showHelp();    // 📖 Visar hjälpmeny
void showAbout();   // ℹ️  Visar info om appen
void tiden();       // 🕒  Visar aktuell tid

#endif
