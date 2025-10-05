#include <stdio.h>
#include <string.h>
#include "login.h"

typedef struct {
    char name[50];
    char lastname[50];
    char username[50];
    char password[50];
} Loggain;

#define MAX_USERS 10000000
static Loggain users[MAX_USERS];
static int userCount = 0;

void login() {

    if (userCount == 0) {
        printf("Välkommen till Väderappen\n");
        return;
    }
    
    printf("\n═══════════════════════════════════════════════════════════════\n");
    printf("          🔐   LOGIN TO WEATHER APP   🔐\n");
    printf("═══════════════════════════════════════════════════════════════\n");

    char username[50], password[50];
    printf("🆔  Username : ");
    scanf("%49s", username);
    printf("🔑  Password : ");
    scanf("%49s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("═══════════════════════════════════════════════════════════════\n");
            printf("✅ Welcome, %s %s! You have access to the weather app. 🌤️\n",
                   users[i].name, users[i].lastname);
            printf("═══════════════════════════════════════════════════════════════\n\n");
            return;
        }
    }
    printf("❌ Invalid login. Please try again!\n");
}

void createLogin() {
    printf("\n═══════════════════════════════════════════════════════════════\n");
    printf("       📝   CREATE NEW ACCOUNT   📝\n");
    printf("═══════════════════════════════════════════════════════════════\n");

    printf("👤  First name   : ");
    scanf("%49s", users[userCount].name);
    printf("👤  Last name    : ");
    scanf("%49s", users[userCount].lastname);
    printf("🆔  Username     : ");
    scanf("%49s", users[userCount].username);
    printf("🔑  Password     : ");
    scanf("%49s", users[userCount].password);

    userCount++;

    printf("═══════════════════════════════════════════════════════════════\n");
    printf("✅ Account for %s %s created successfully!\n",
           users[userCount-1].name, users[userCount-1].lastname);
    printf("═══════════════════════════════════════════════════════════════\n\n");
}

void showlogin() {
    if (userCount == 0) {
        printf("🚫 No users have been registered yet.\n");
        return;
    }

    printf("\n═══════════════════════════════════════════════════════════════\n");
    printf("                 👥   REGISTERED USERS   👥\n");
    printf("═══════════════════════════════════════════════════════════════\n");

    // Tabellhuvud
    printf("%-5s | %-15s | %-15s | %-15s | %-10s\n",
           "ID", "First Name", "Last Name", "Username", "Password");
    printf("───────────────────────────────────────────────────────────────\n");

    // Skriv ut alla användare
    for (int i = 0; i < userCount; i++) {
        // Skapa en maskad version av lösenordet
        char masked[50];
        memset(masked, '*', strlen(users[i].password));
        masked[strlen(users[i].password)] = '\0';

        printf("%-5d | %-15s | %-15s | %-15s | %-10s\n",
               i + 1,
               users[i].name,
               users[i].lastname,
               users[i].username,
               masked);
    }
    
    printf("═══════════════════════════════════════════════════════════════\n\n");
}

    
