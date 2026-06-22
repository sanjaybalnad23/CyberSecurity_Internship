#include <stdio.h>

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (number % 2 == 0)
        printf("%d is an Even Number\n", number);
    else
        printf("%d is an Odd Number\n", number);

    return 0;
}