#include <stdio.h>

int main() {
    int marks[5];
    int highest, lowest;
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        printf("Enter marks for student %d: ", i + 1);
        scanf("%d", &marks[i]);
    }

    highest = lowest = marks[0];

    for (int i = 0; i < 5; i++) {
        if (marks[i] > highest)
            highest = marks[i];

        if (marks[i] < lowest)
            lowest = marks[i];

        sum += marks[i];
    }

    printf("\nHighest Marks: %d\n", highest);
    printf("Lowest Marks: %d\n", lowest);
    printf("Average Marks: %.2f\n", (float)sum / 5);

    return 0;
}