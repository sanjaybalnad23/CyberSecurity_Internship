#include <stdio.h>

int main() {
    FILE *fp;
    char website[100];
    char username[100];
    char password[100];
    char ch;

    printf("Enter Website Name: ");
    scanf("%s", website);

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    fp = fopen("password_vault.txt", "a");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }

    fprintf(fp, "Website: %s\n", website);
    fprintf(fp, "Username: %s\n", username);
    fprintf(fp, "Password: %s\n\n", password);

    fclose(fp);

    printf("\nRecord Saved Successfully.\n");

    fp = fopen("password_vault.txt", "r");

    if (fp == NULL) {
        printf("Unable to read file.\n");
        return 1;
    }

    printf("\nSaved Records:\n\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);

    return 0;
}