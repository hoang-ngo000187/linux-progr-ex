#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char* filename; // tên file
    int num_bytes;  // số byte muốn read/write
    // 'r': thực hiện đọc từ filename và in ra màn hình; 'w': thực hiện ghi vào filename
    char mode;
    char* buff;     // nội dung bất kỳ muốn read/write vào filename
    int fd;
    char read_buff[num_bytes + 1];
    int numb_write, numb_read;

    // argv[0] = ./example_program
    filename = argv[1];
    num_bytes = atoi(argv[2]);
    mode = argv[3][0]; // gia tri o index 0, neu de argv[3] thi day chi la 1 con tro
    buff = argv[4];

    /* Đọc file */
    fd = open((const char*)filename, O_RDWR|O_CREAT, 0666);
    if (-1 == fd)
    {
        printf("open() filename failed\n");
    }

    /* Thực hiện đọc từ  filename và in ra màn hình */
    if ('r' == mode)
    {
        numb_read = read(fd, read_buff, num_bytes);
        if (-1 == numb_read)
        {
            printf("read() filename failed\n");
        }
        else
        {
            read_buff[numb_read] = '\0';
            printf("Read %d bytes from file %s: %s\n", num_bytes, (const char*)filename, read_buff);
        }
    }
    /* Thực hiện ghi vào filename */
    else if ('w' == mode)
    {
        numb_write = write(fd, buff, num_bytes);
        if (-1 == numb_write)
        {
            printf("write() filename failed\n");
        }
        else
        {
            printf("Write %d bytes to file %s\n", numb_write, (const char*)filename);
        }
    }
    else
    {
        printf("Invalid mode\n");
    }

    close(fd);

    return 0;
}