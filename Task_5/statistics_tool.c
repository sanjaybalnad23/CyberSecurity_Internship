#include <stdio.h>

int main() {
    int numbers[10];
    int largest, smallest;
    int sum = 0;
    int evenCount = 0;
    int oddCount = 0;

    printf("Enter 10 numbers:\n");

    for (int i = 0; i < 10; i++) {
        scanf("%d", &numbers[i]);
    }

    largest = smallest = numbers[0];

    for (int i = 0; i < 10; i++) {
        if (numbers[i] > largest)
            largest = numbers[i];

        if (numbers[i] < smallest)
            smallest = numbers[i];

        sum += numbers[i];

        if (numbers[i] % 2 == 0)
            evenCount++;
        else
            oddCount++;
    }

    printf("\nLargest Number: %d\n", largest);
    printf("Smallest Number: %d\n", smallest);
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", (float)sum / 10);
    printf("Even Numbers: %d\n", evenCount);
    printf("Odd Numbers: %d\n", oddCount);

    return 0;
}