#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;
    int numb_write;
    char buf1[12] = "hello world\n";

    /* 1. Mo file hello.txt voi co O_APPEND */
    fd = open("hello.txt", O_RDWR|O_CREAT|O_APPEND, 0666); // O_RDWR | O_CREAT
    
    if (-1 == fd)
    {
        printf("open() hello.txt failed\n");
    }

    /* 2. Di chuyen con tro chuot ve dau file */
    lseek(fd, 0, SEEK_SET);

    /* 3. Ghi mot vai ky tu vao file */
    numb_write = write(fd, buf1, strlen(buf1));
    printf("Write %d byte to the begin of hello.txt\n", numb_write);

    close(fd);

    return 0;
}