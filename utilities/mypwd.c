#include<stdio.h>
#include <unistd.h>

#define count 10000


int main(int argc, char **argv)
{

    char buf[count];

    char *x = getcwd(buf, sizeof(buf));
    printf("%s\n", buf);
    return 0;

}
