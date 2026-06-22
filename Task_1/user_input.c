#include <stdio.h>

int main() {
    char name[50];
    char tech[50];
    int age;

    printf("Enter Name: ");
    scanf("%49s", name);

    printf("Enter Age: ");
    scanf("%d", &age);

    printf("Enter Favorite Technology: ");
    scanf("%49s", tech);

    printf("\nHello %s!\n", name);
    printf("You are %d years old.\n", age);
    printf("Your favorite technology is %s.\n", tech);

    return 0;
}