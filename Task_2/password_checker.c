#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[100];
    int hasUpper = 0;
    int hasDigit = 0;

    printf("Enter Password: ");
    scanf("%99s", password);

    int length = strlen(password);

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i]))
            hasUpper = 1;

        if (isdigit(password[i]))
            hasDigit = 1;
    }

    if (length >= 8 && hasUpper && hasDigit)
        printf("Strong Password\n");
    else if (length >= 8)
        printf("Moderate Password\n");
    else
        printf("Weak Password\n");

    return 0;
}