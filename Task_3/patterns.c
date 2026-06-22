#include <stdio.h>

int main() {

    printf("Pattern 1:\n");

    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    printf("\nPattern 2:\n");

    for(int i = 5; i >= 1; i--) {
        for(int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    printf("\nPattern 3:\n");

    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= i; j++) {
            printf("%d", j);
        }
        printf("\n");
    }

    return 0;
}