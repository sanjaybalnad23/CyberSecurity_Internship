#include <stdio.h>

int main() {
    FILE *fp;
    char ch;

    fp = fopen("student_data.txt", "r");

    if (fp == NULL) {
        printf("Unable to open student_data.txt\n");
        return 1;
    }

    printf("Reading File...\n\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);

    return 0;
}