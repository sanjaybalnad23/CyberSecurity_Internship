#include <stdio.h>

void displayStudent(char name[], int roll, char branch[], int semester) {
    printf("\nStudent Information\n");
    printf("Name      : %s\n", name);
    printf("Roll No   : %d\n", roll);
    printf("Branch    : %s\n", branch);
    printf("Semester  : %d\n", semester);
}

int main() {
    char name[100];
    char branch[50];
    int roll, semester;

    printf("Enter Student Name: ");
    scanf(" %[^\n]", name);

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    printf("Enter Branch: ");
    scanf("%s", branch);

    printf("Enter Semester: ");
    scanf("%d", &semester);

    displayStudent(name, roll, branch, semester);

    return 0;
}