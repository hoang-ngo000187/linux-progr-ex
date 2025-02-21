/*
Giải thích điều gì xảy ra với tiến trình ban đầu sau khi exec được gọi:
. Khi hàm execlp() được gọi, tiến trình con sẽ bị thay thế hoàn toàn bởi tiến trình mới, hay nói cách khác là bộ nhớ, mã lệnh, stack, heap của tiến trình con sẽ bị xóa và chỉ giữ lại PID của nó. 
. Bên cạnh đó, hàm execlp() khi thực thi xong sẽ không quay lại tiến trình gốc, do đó ta sẽ thấy khi execlp() thực hiện thành công thì dòng lệnh printf("execlp() unsuccessfully\n") sẽ không được thực hiện, còn khi execlp() không thực hiện thành công thì tiến trình con sẽ tiếp tục thực hiện lệnh printf("execlp() unsuccessfully\n").
Còn tiến trình cha không chạy execlp() mà chỉ đợi tiến trình con kết thúc.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LS_FUNCTION     1
#define TIME_FUNCTION   2

int main(int argc, char* agrv[])
{
    int function;
    pid_t child_pid;

    child_pid = fork();

    if (0 <= child_pid)
    {
        if (0 == child_pid)
        {
            /* Tien trinh con dang chay */
            function = atoi(agrv[1]);

            switch (function)
            {
            case LS_FUNCTION:
                printf("Thuc hien lenh 'ls -l' tu Child process voi execlp: \n");
                execlp("ls", "ls", "-l", NULL);
                break;

            case TIME_FUNCTION:
                printf("Thuc hien lenh 'date' tu Child process voi execlp: \n");
                execlp("date", "date", NULL);
                break;

            default:
                printf("Invalid function\n");
                break;
            }
            
            /*
                Neu exec thanh cong, dong lenh printf sau se khong bao gio chay
                Neu exec that bai, chuong trinh tiep tuc chay printf("execlp() unsuccessfully\n")

            */
            printf("execlp() unsuccessfully\n");
        }
        else
        {
            /*
                Tien trinh cha dang chay 
                Goi wait(NULL); de doi Child process ket thuc.
            */
            wait(NULL);
            printf("Parent process finish!\n");
        }
    }
    else
    {
        printf("fork() unsuccessfully\n");
    }
}