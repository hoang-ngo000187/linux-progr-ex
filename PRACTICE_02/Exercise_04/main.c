#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int fd;
    struct stat file_info;

    fd = open("hello.txt", O_RDWR | O_CREAT, 0777);

    if (-1 == fd)
    {
        printf("open() hello.txt failed\n");
    }
    else
    {
        if (-1 == fstat(fd, &file_info))
        {
            printf("Fail to get information of file\n");
        }
        else
        {
            /* 01 - Loại file */
            printf("Type of file: ");
            switch ((file_info.st_mode & S_IFMT))
            {
            // case S_ISBLK:
            //     printf("block device\n");
            //     break;
            case S_IFCHR:
                printf("character device\n");
                break;
            case S_IFDIR:
                printf("directory\n");
                break;
            case S_IFIFO:
                printf("pipe or FIFO\n");
                break;
            // case S_IFLNK:
            //     printf("file symbolic link\n");
            //     break;
            case S_IFREG:
                printf("regular file\n");
                break;
            // case S_IFSOCK:
            //     printf("socket\n");
            //     break;
            default:
                printf("unknown?\n");
                break;
            }
            /* 02 - Số I-node của file */
            printf("I-node number: %ld\n", (long)(file_info.st_ino));

            /* 03 - Kích thước file (bytes) */
            printf("Size of file: %lld bytes\n", (long long)(file_info.st_size));

            /* 04 - Thời gian lần cuối cùng file được đọc (nhưng không thay đổi nội dung) */
            printf("Last file access time: %s\n", ctime(&file_info.st_atime));

            /* 05 - Thời gian lần cuối cùng thay đổi khi đổi quyền (chmod), chủ sở hữu (chown) hoặc di chuyển file */
            printf("Last status change time: %s\n", ctime(&file_info.st_ctime));

            /* 06 - Thời gian lần cuối cùng chỉnh sửa nội dung file */
            printf("Last file modification time: %s\n", ctime(&file_info.st_mtime));
        }
    }

    close (fd);

    return 0;
}