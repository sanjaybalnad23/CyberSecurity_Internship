#include <stdio.h>
#include <time.h>

int main() {
    time_t now = time(NULL);

    printf("Name: Sanjay Balnad\n");
    printf("College: Your College Name\n");
    printf("Branch: MCA\n");
    printf("Internship: Cyber Security Summer Internship\n");
    printf("Date & Time: %s", ctime(&now));

    return 0;
}