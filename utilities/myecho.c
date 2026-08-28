#include<stdio.h>
#include <unistd.h>


int main(int argc, char **argv)
{

    if (argc == 1) {
        printf("\n");
        return 0;
    }

    int i;
    for (i = 1; i < argc - 1; i++) {
        printf("%s ", argv[i]);
    }
    printf("%s\n", argv[i]);

    return 0;
}
