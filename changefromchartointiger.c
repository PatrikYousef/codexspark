#include <stdio.h>
#include <stdlib.h>

int main() {
    char str1[4];
    char str2[4];

    scanf("%3s", str1);
    scanf("%3s", str2);

    int num1 = atoi(str1);
    int num2 = atoi(str2);

    printf("%d\n", num1 + num2); 
    return 0;
}
