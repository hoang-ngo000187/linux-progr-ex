#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create_zombie(void)
{
    pid_t child_pid = fork();

    if (0 <= child_pid)
    {
        if (0 == child_pid)
        {
            printf("I am Child process (PID: %d), my Parent process (PPID: %d)\n", getpid(), getppid());
            printf("Child process termination now!\n");
            exit(0); // Kết thúc tiến trình con, tạo Zombie Process
        }
        else
        {
            printf("I am Parent process (PID: %d), my Child process PID: %d\n", getpid(), child_pid);
            while(1);
        }
    }
    else
    {
        printf("fork() unsuccessfully!\n");
    }
}

void create_orphane(void)
{
    pid_t child_pid = fork();

    if (0 <= child_pid)
    {
        if (0 == child_pid)
        {
            printf("I am Child process (PID: %d), my Parent process (PPID: %d)\n", getpid(), getppid());
            while(1);
        }
        else
        {
            printf("I am Parent process (PID: %d), my Child process PID: %d\n", getpid(), child_pid);
            printf("Parent process termination now!\n");
            exit(0); // Tiến trình cha kết thúc để tiến trình con trở thành tiến trình Orphane
        }
    }
    else
    {
        printf("fork() unsuccessfully!\n");
    }
}

int main()
{   
    int choice;

    printf("Select '0' for Create Zombie process, '1' for Create Orphane process: ");
    scanf("%d", &choice);

    if (choice == 0)
    {
        create_zombie();
    }
    else if (choice == 1)
    {
        create_orphane();
    }
    else
    {
        printf("Invalid option!\n");
    }
    
    return 0;
}