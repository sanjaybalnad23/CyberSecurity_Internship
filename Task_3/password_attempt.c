#include <stdio.h>
#include <string.h>

int main() {
    char password[] = "admin123";
    char input[50];
    int attempts = 0;

    while(attempts < 3) {

        printf("Enter Password: ");
        scanf("%s", input);

        if(strcmp(password, input) == 0) {
            printf("Access Granted\n");
            return 0;
        }

        attempts++;
        printf("Incorrect Password!\n");
    }

    printf("Account Locked\n");

    return 0;
}