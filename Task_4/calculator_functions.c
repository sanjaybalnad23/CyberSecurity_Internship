#include <stdio.h>

float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b == 0) {
        printf("Division by zero is not allowed.\n");
        return 0;
    }
    return a / b;
}

int main() {
    int choice;
    float num1, num2;

    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");

    printf("Enter Choice: ");
    scanf("%d", &choice);

    printf("Enter First Number: ");
    scanf("%f", &num1);

    printf("Enter Second Number: ");
    scanf("%f", &num2);

    switch(choice) {
        case 1:
            printf("Result = %.2f\n", add(num1, num2));
            break;
        case 2:
            printf("Result = %.2f\n", subtract(num1, num2));
            break;
        case 3:
            printf("Result = %.2f\n", multiply(num1, num2));
            break;
        case 4:
            printf("Result = %.2f\n", divide(num1, num2));
            break;
        default:
            printf("Invalid Choice\n");
    }

    return 0;
}