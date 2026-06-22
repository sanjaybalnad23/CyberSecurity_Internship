#include <stdio.h>

int main() {
    float marks[5];
    float total = 0, percentage;
    char grade;

    for(int i = 0; i < 5; i++) {
        printf("Enter Marks for Subject %d: ", i + 1);
        scanf("%f", &marks[i]);
        total += marks[i];
    }

    percentage = total / 5;

    if (percentage >= 90)
        grade = 'A';
    else if (percentage >= 80)
        grade = 'B';
    else if (percentage >= 70)
        grade = 'C';
    else if (percentage >= 60)
        grade = 'D';
    else
        grade = 'F';

    printf("\nTotal Marks : %.2f\n", total);
    printf("Percentage  : %.2f%%\n", percentage);
    printf("Grade       : %c\n", grade);

    return 0;
}