#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define count 100000
int main(int argc, char **argv)
{
    char buf[count];
    if (argc != 3) {
        return 1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        return 1;
    }
    int fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd2 < 0) {
        close(fd1);
        return 1;
    }
    int num_read = read(fd1, buf, count);
    write(fd2, buf, num_read);

    close(fd1);
    close(fd2);

    unlink(argv[1]);

    return 0;
}
