#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "students.txt"

int securityScores[100];
int scoreCount = 0;

int login() {
    char username[50];
    char password[50];

    printf("\n===== LOGIN =====\n");

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if(strcmp(username, "admin") == 0 &&
       strcmp(password, "admin123") == 0) {
        printf("Login Successful!\n");
        return 1;
    }

    printf("Invalid Credentials!\n");
    return 0;
}

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "a");

    char id[20];
    char name[50];
    char branch[30];
    char email[50];

    printf("\nStudent ID: ");
    scanf("%s", id);

    getchar();

    printf("Student Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Branch: ");
    fgets(branch, sizeof(branch), stdin);
    branch[strcspn(branch, "\n")] = 0;

    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    fprintf(fp, "%s,%s,%s,%s\n",
            id, name, branch, email);

    fclose(fp);

    printf("Student Added Successfully!\n");
}

void viewStudents() {
    FILE *fp = fopen(FILE_NAME, "r");

    if(fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    char line[200];

    printf("\n===== STUDENTS =====\n");

    while(fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "r");

    if(fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    char key[50];
    char line[200];

    printf("Enter Name or ID: ");
    scanf("%s", key);

    int found = 0;

    while(fgets(line, sizeof(line), fp)) {

        if(strstr(line, key)) {
            printf("%s", line);
            found = 1;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    char id[20];
    char line[200];

    int found = 0;

    printf("Enter Student ID: ");
    scanf("%s", id);

    while(fgets(line, sizeof(line), fp)) {

        char copy[200];
        strcpy(copy, line);

        char *token = strtok(copy, ",");

        if(strcmp(token, id) != 0) {
            fputs(line, temp);
        }
        else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if(found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}

void securityAssessment() {

    char mfa[10];
    char update[10];
    char antivirus[10];

    int length;
    int score = 0;

    printf("Is MFA Enabled? (yes/no): ");
    scanf("%s", mfa);

    if(strcmp(mfa, "yes") == 0)
        score += 25;

    printf("Password Length: ");
    scanf("%d", &length);

    if(length >= 12)
        score += 25;
    else if(length >= 8)
        score += 15;

    printf("System Updated? (yes/no): ");
    scanf("%s", update);

    if(strcmp(update, "yes") == 0)
        score += 25;

    printf("Antivirus Installed? (yes/no): ");
    scanf("%s", antivirus);

    if(strcmp(antivirus, "yes") == 0)
        score += 25;

    securityScores[scoreCount++] = score;

    printf("\nSecurity Score: %d/100\n", score);

    if(score >= 90)
        printf("Status: Excellent\n");
    else if(score >= 70)
        printf("Status: Good\n");
    else if(score >= 50)
        printf("Status: Moderate\n");
    else
        printf("Status: Poor\n");
}

void generateReport() {

    FILE *fp = fopen(FILE_NAME, "r");

    int students = 0;
    char line[200];

    if(fp) {
        while(fgets(line, sizeof(line), fp))
            students++;

        fclose(fp);
    }

    printf("\n===== REPORT =====\n");

    printf("Total Students: %d\n", students);

    int sum = 0;
    int poor = 0;

    for(int i = 0; i < scoreCount; i++) {

        printf("Score %d: %d\n",
               i + 1,
               securityScores[i]);

        sum += securityScores[i];

        if(securityScores[i] < 50)
            poor++;
    }

    if(scoreCount > 0) {

        printf("Average Score: %.2f\n",
               (float)sum / scoreCount);

        printf("Poor Ratings: %d\n", poor);
    }
}

void passwordStrengthChecker() {

    char password[100];

    int upper = 0;
    int lower = 0;
    int digit = 0;
    int special = 0;

    printf("Enter Password: ");
    scanf("%s", password);

    for(int i = 0; password[i]; i++) {

        if(isupper(password[i]))
            upper = 1;
        else if(islower(password[i]))
            lower = 1;
        else if(isdigit(password[i]))
            digit = 1;
        else
            special = 1;
    }

    int score =
        upper + lower + digit + special;

    if(strlen(password) >= 8)
        score++;

    if(score == 5)
        printf("Strong Password\n");
    else if(score >= 3)
        printf("Medium Password\n");
    else
        printf("Weak Password\n");
}

void usernameGenerator() {

    char name[100];

    getchar();

    printf("Enter Full Name: ");
    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = 0;

    printf("Generated Username: ");

    for(int i = 0; name[i]; i++) {

        if(name[i] != ' ')
            printf("%c", tolower(name[i]));
    }

    printf("123\n");
}

void cyberTools() {

    int choice;

    while(1) {

        printf("\n===== CYBER TOOLS =====\n");
        printf("1. Password Strength Checker\n");
        printf("2. Username Generator\n");
        printf("3. Back\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                passwordStrengthChecker();
                break;

            case 2:
                usernameGenerator();
                break;

            case 3:
                return;

            default:
                printf("Invalid Choice\n");
        }
    }
}

int main() {

    if(!login())
        return 0;

    int choice;

    while(1) {

        printf("\n==========================\n");
        printf("Student Security Manager\n");
        printf("==========================\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Security Assessment\n");
        printf("6. Generate Report\n");
        printf("7. Cyber Security Tools\n");
        printf("8. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: securityAssessment(); break;
            case 6: generateReport(); break;
            case 7: cyberTools(); break;

            case 8:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}