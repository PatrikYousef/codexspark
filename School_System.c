#include <stdio.h>
#include  <string.h>
#include <stdlib.h>

typedef struct schoolsystem
{
   char name[40];
   char lastname[40];
   long long int computer;
   int group;
   int personGrade;


}schoolsystem;

    schoolsystem people[10000];   
    int peopleCount = 0;   
    
typedef struct {
    int number;
    const char *name;
} Grade;

typedef struct {
    int id;
    const char *roomName;
} GroupRoom;

typedef struct {
    int grade;         
    const char* room; 
} Booking;

  Booking bookings[100];
  int bookingCount = 0;   

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void WaitForEnter() {
    printf("\n\n⏳ Press ENTER to continue...");
    getchar();
    getchar();
}


void SchoolSystemAppendInformation(){
    schoolsystem s;

    printf("🔤 Enter the name: ");
    scanf("%39s", s.name);

    printf("🔤 Enter the lastname: ");
    scanf("%39s", s.lastname);

    printf("🔤 Enter the computercode: ");
    scanf("%lld", &s.computer);

    // Array of grades
    Grade grades[] = {
        {1,  "1st Grade"}, {2,  "2nd Grade"}, {3,  "3rd Grade"},
        {4,  "4th Grade"}, {5,  "5th Grade"}, {6,  "6th Grade"},
        {7,  "7th Grade"}, {8,  "8th Grade"}, {9,  "9th Grade"},
        {10, "10th Grade"}, {11, "11th Grade"}, {12, "12th Grade"}
    };

    int count = sizeof(grades) / sizeof(grades[0]);

    for (int i = 0; i < count; i++) {
        printf("%d → %s\n", grades[i].number, grades[i].name);
    }

    printf("\nEnter the class the person is in: ");
    scanf("%d", &s.personGrade);

    if (s.personGrade >= 1 && s.personGrade <= 12) {
        printf("You selected: %s\n", grades[s.personGrade - 1].name);
    } else {
        printf("Invalid grade!\n");
    }

    people[peopleCount] = s;
    peopleCount++;
}

void ShowAllStudentInformation() {

    if (peopleCount == 0) {
        printf("\nNo students saved yet.\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("                       ALL SAVED STUDENTS                      \n");
    printf("===============================================================\n");
    printf("| %-3s | %-15s | %-15s | %-12s | %-5s |\n",
           "ID", "Name", "Lastname", "Computer", "Grade");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < peopleCount; i++) {
        printf("| %-3d | %-15s | %-15s | %-12lld | %-5d |\n",
               i + 1,
               people[i].name,
               people[i].lastname,
               people[i].computer,
               people[i].personGrade);
    }

    printf("===============================================================\n\n");
}


void BookForaGroupToStudy() {

    int gradeChoice;
    int roomChoice;

    // Grades
    Grade grades[] = {
        {1,  "1st Grade"}, {2,  "2nd Grade"}, {3,  "3rd Grade"},
        {4,  "4th Grade"}, {5,  "5th Grade"}, {6,  "6th Grade"},
        {7,  "7th Grade"}, {8,  "8th Grade"}, {9,  "9th Grade"},
        {10, "10th Grade"}, {11, "11th Grade"}, {12, "12th Grade"}
    };

    int gradeCount = sizeof(grades) / sizeof(grades[0]);

    printf("Select grade to book a room:\n");
    for (int i = 0; i < gradeCount; i++) {
        printf("%d → %s\n", grades[i].number, grades[i].name);
    }

    scanf("%d", &gradeChoice);

    if (gradeChoice < 1 || gradeChoice > 12) {
        printf("Invalid grade!\n");
        return;
    }

    printf("Selected grade: %s\n", grades[gradeChoice - 1].name);


    // Rooms
    GroupRoom groups[] = {
        {1, "Room A"},
        {2, "Room B"},
        {3, "Room C"},
        {4, "Room D"},
        {5, "Room E"}
    };

    int groupCount = sizeof(groups) / sizeof(groups[0]);

    printf("\nAvailable rooms:\n");
    for (int i = 0; i < groupCount; i++) {
        printf("%d → %s\n", groups[i].id, groups[i].roomName);
    }

    scanf("%d", &roomChoice);

    if (roomChoice < 1 || roomChoice > groupCount) {
        printf("Invalid room selection!\n");
        return;
    }

    printf("Selected room: %s\n", groups[roomChoice - 1].roomName);


    bookings[bookingCount].grade = gradeChoice;
    bookings[bookingCount].room = groups[roomChoice - 1].roomName;
    bookingCount++;

    printf("\nBooking saved!\n");
}

void ShowAllBookings() {
    printf("\n--- All Room Bookings ---\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("Grade %d booked %s\n", bookings[i].grade, bookings[i].room);
    }
}


void ChangeOrAppendNewStuff() {
    schoolsystem s;

    printf("\n🔧✨  EDIT STUDENT INFORMATION  ✨🔧\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    printf("🔤 Enter first name: ");
    scanf("%39s", s.name);

    printf("🔤 Enter last name: ");
    scanf("%39s", s.lastname);

    // Loop for matching student
    for (int i = 0; i < peopleCount; i++) {

        if (strcmp(s.name, people[i].name) == 0 &&
            strcmp(s.lastname, people[i].lastname) == 0)
        {
            int choice;

            printf("\n🎯 Student found! What would you like to change?\n");
            printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
            printf("1️⃣  ➤  ✏️ Change first name\n\n");
            printf("2️⃣  ➤  ✏️ Change last name\n\n");
            printf("3️⃣  ➤  💻 Change computer code\n\n");
            printf("4️⃣  ➤  🏫 Change study group\n\n");
            printf("5️⃣  ➤  🎓 Change grade\n\n");
            printf("6️⃣  ➤  ❌ Cancel\n\n");
            printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
            printf("👉 Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {

                case 1:
                    printf("✏️ Enter new name: ");
                    scanf("%39s", people[i].name);
                    printf("✅ Name updated!\n");
                    break;

                case 2:
                    printf("✏️ Enter new lastname: ");
                    scanf("%39s", people[i].lastname);
                    printf("✅ Lastname updated!\n");
                    break;

                case 3:
                    printf("💻 Enter new computercode: ");
                    scanf("%lld", &people[i].computer);
                    printf("✅ Computer code updated!\n");
                    break;

                case 4:
                    printf("🏫 Enter new group number: ");
                    scanf("%d", &people[i].group);
                    printf("✅ Group updated!\n");
                    break;

                case 5:
                    printf("🎓 Enter new grade (1–12): ");
                    scanf("%d", &people[i].personGrade);

                    if (people[i].personGrade < 1 || people[i].personGrade > 12)
                        printf("⚠️ Invalid grade!\n");
                    else
                        printf("✅ Grade updated!\n");
                    break;

                case 6:
                    printf("❌ Edit cancelled.\n");
                    return;

                default:
                    printf("⚠️ Invalid choice.\n");
            }

            return; // after edit
        }
    }

    printf("\n❌ Person not found.\n");
}



void SerarchForaStudent(){
    schoolsystem s;

    printf("🔤 Enter the name of the person: ");
    scanf("%39s", s.name);

    printf("🔤 Enter the lastname of the person: ");
    scanf("%39s", s.lastname);


    // loop over all saved people
    for (int i = 0; i < peopleCount; i++) {

        if (strcmp(s.name, people[i].name) == 0 &&
            strcmp(s.lastname, people[i].lastname) == 0)
        {
       

        printf("\n========================================\n");
        printf("             STUDENT %d                 \n", i + 1);
        printf("========================================\n");
        printf("| %-12s | %-25s |\n", "Field", "Value");
        printf("========================================\n");
        printf("| %-12s | %-25s |\n", "Name",     people[i].name);
        printf("| %-12s | %-25s |\n", "Lastname", people[i].lastname);
        printf("| %-12s | %-25lld |\n", "Computer", people[i].computer);
        printf("| %-12s | %-25d |\n", "Group",    people[i].group);
        printf("| %-12s | %-25d |\n", "Grade",    people[i].personGrade);
        printf("========================================\n");
        return;
        }
    }

    printf("Person not found.\n");

}

int CompareStudents(const void *a, const void *b) {
    const schoolsystem *s1 = (const schoolsystem *)a;
    const schoolsystem *s2 = (const schoolsystem *)b;

    // First compare lastname
    int last = strcmp(s1->lastname, s2->lastname);
    if (last != 0) return last;

    // If lastnames are equal → compare firstname
    return strcmp(s1->name, s2->name);
}


void ShowSortedStudents() {
    if (peopleCount == 0) {
        printf("No students to sort.\n");
        return;
    }

    // Make a temporary copy so original order stays unchanged
    schoolsystem sorted[10000];
    memcpy(sorted, people, sizeof(schoolsystem) * peopleCount);

    // Sort the copy
    qsort(sorted, peopleCount, sizeof(schoolsystem), CompareStudents);

    // Print sorted students
    printf("\n=== Sorted Students ===\n");
    for (int i = 0; i < peopleCount; i++) {
        printf("%s %s - Grade: %d, Computer: %lld, Group: %d\n",
               sorted[i].name,
               sorted[i].lastname,
               sorted[i].personGrade,
               sorted[i].computer,
               sorted[i].group);
    }
    printf("========================\n");
}


void Menu() {
    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("         🌟📚  SCHOOL SYSTEM MENU  📚🌟\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    printf("1️⃣  ➤  👨 Add student\n\n");
    printf("2️⃣  ➤  📖 Show students\n\n");
    printf("3️⃣  ➤  🏫 Book study room\n\n");
    printf("4️⃣  ➤  🔍 Search student\n\n");
    printf("5️⃣  ➤  ✏️  Edit student\n\n");
    printf("6️⃣  ➤  🗂️  Show bookings\n\n");
    printf("7️⃣  ➤  📊 Sorted students\n\n");
    printf("8️⃣  ➤  🚪 Exit\n\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}


void MenuToChoose() {
    while (1) {
        ClearScreen();

        Menu();

        int choice;
        printf("🔤 Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ClearScreen();
                SchoolSystemAppendInformation();
                WaitForEnter();
                break;

            case 2:
                ClearScreen();
                ShowAllStudentInformation();
                WaitForEnter();
                break;

            case 3:
                ClearScreen();
                BookForaGroupToStudy();
                WaitForEnter();
                break;

            case 4:
                ClearScreen();
                SerarchForaStudent();
                WaitForEnter();
                break;

            case 5:
                ClearScreen();
                ChangeOrAppendNewStuff();
                WaitForEnter();
                break;

            case 6:
                ClearScreen();
                ShowAllBookings();
                WaitForEnter();
                break;

            case 7:
                ClearScreen();
                ShowSortedStudents();
                WaitForEnter();
                break;
            
            case 8:
                ClearScreen();
                printf("Exiting program...\n");
                return;
            default:
                ClearScreen();
                printf("Invalid option, try again.\n");
        }
    }
}


int main(){     
    MenuToChoose();
    return 0;
}