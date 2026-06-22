#include <stdio.h>
#include <string.h>

int main() {
    char employees[][20] = {
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Emma"
    };

    char search[20];
    int found = 0;

    printf("Enter employee name: ");
    scanf("%19s", search);

    for (int i = 0; i < 5; i++) {
        if (strcasecmp(search, employees[i]) == 0) {
            found = 1;
            break;
        }
    }

    if (found)
        printf("Record Found\n");
    else
        printf("Record Not Found\n");

    return 0;
}