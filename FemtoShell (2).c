#include<stdio.h>
#include<string.h>

#define count 1000

int main(int argc, char **argv)
{
    char buf[count];

    while (1) {
        printf("M-BOT ;D :> ");
        fgets(buf, count, stdin);       

        if ((strncmp(buf, "echo", 4) == 0)) {   
            printf("%s", buf + 5);
        } else if (strncmp(buf, "exit", 4) == 0) {
            printf("GOOD BYE\n");
            return 0;
        } else if ((buf[0] == '\n')) {
            continue;


        } else
            printf("INVALIED COMMAND\n");

    }
    return 0;
}