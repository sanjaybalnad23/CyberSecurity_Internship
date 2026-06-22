#include <stdio.h>
#include <string.h>

int main() {
    char firstName[50];
    char lastName[50];
    int birthYear;

    printf("Enter First Name: ");
    scanf("%s", firstName);

    printf("Enter Last Name: ");
    scanf("%s", lastName);

    printf("Enter Birth Year: ");
    scanf("%d", &birthYear);

    int shortYear = birthYear % 100;

    printf("\nUsername Suggestions:\n");

    printf("1. %s%s%d\n", firstName, lastName, birthYear);
    printf("2. %c.%s%02d\n", firstName[0], lastName, shortYear);
    printf("3. %s_%s\n", lastName, firstName);
    printf("4. %s%d\n", firstName, shortYear);
    printf("5. %s_%d\n", lastName, birthYear);

    return 0;
}