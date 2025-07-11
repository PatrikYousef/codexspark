#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(const char*)a - *(const char*)b);
}

int main() {
    char bokstäver[21]; 
    scanf("%20s", bokstäver);  

    int size = strlen(bokstäver);  

    qsort(bokstäver, size, sizeof(char), compare);

    printf("%s\n", bokstäver);

    return 0;
}

