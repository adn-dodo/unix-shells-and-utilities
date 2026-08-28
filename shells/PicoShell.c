#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define count 8000

int main(int argc, char **argv)
{
    char buf[count];

    while (1) {
        printf("M-BOT ;) HEHEHEHE $ ");
        fgets(buf, count, stdin);

        buf[strcspn(buf, "\n")] = 0;

        if (strlen(buf) == 0)
            continue;

        if (strncmp(buf, "echo ", 4) == 0) {
            printf("%s\n", buf + 5);
        } else if (strcmp(buf, "pwd") == 0) {
            if (getcwd(buf, sizeof(buf)) != 0) {
                printf("%s\n", buf);
            } else {
                printf("pwd error\n");
            }
        } else if (strncmp(buf, "cd ", 2) == 0) {
            if (chdir(buf + 3) != 0) {
                printf("cannot change directory\n");
            }
        } else if (strcmp(buf, "exit") == 0) {
            printf("Good Bye :)\n");
            return 0;
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}

