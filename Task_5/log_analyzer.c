#include <stdio.h>

int main() {
    int logs[] = {1, 1, 0, 1, 0, 0, 1};
    int total = sizeof(logs) / sizeof(logs[0]);

    int success = 0;
    int failed = 0;

    for (int i = 0; i < total; i++) {
        if (logs[i] == 1)
            success++;
        else
            failed++;
    }

    printf("Total Login Attempts: %d\n", total);
    printf("Successful Logins: %d\n", success);
    printf("Failed Logins: %d\n", failed);

    return 0;
}