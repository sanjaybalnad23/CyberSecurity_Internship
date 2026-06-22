#include <stdio.h>
#include <string.h>

int main() {
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "password123") == 0)
        printf("Login Successful\n");
    else
        printf("Invalid Credentials\n");

    return 0;
}