#include <stdio.h>
#include <string.h>

int main() {
    char blacklist[][20] = {
        "192.168.1.10",
        "10.0.0.5",
        "172.16.0.8"
    };

    char ip[20];
    int found = 0;

    printf("Enter IP Address: ");
    scanf("%19s", ip);

    for (int i = 0; i < 3; i++) {
        if (strcmp(ip, blacklist[i]) == 0) {
            found = 1;
            break;
        }
    }

    if (found)
        printf("IP Found in Blacklist\n");
    else
        printf("IP Not Found\n");

    return 0;
}