#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Operating System: Windows\n\n");

    printf("Current User:\n");
    system("whoami");

    printf("\nCurrent Directory:\n");
    system("cd");

    return 0;
}