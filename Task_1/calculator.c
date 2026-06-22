#include <stdio.h>

int main() {
    float a, b;

    printf("Enter First Number: ");
    scanf("%f", &a);

    printf("Enter Second Number: ");
    scanf("%f", &b);

    printf("Addition: %.2f\n", a + b);
    printf("Subtraction: %.2f\n", a - b);
    printf("Multiplication: %.2f\n", a * b);

    if (b != 0)
        printf("Division: %.2f\n", a / b);
    else
        printf("Division: Cannot divide by zero\n");

    return 0;
}