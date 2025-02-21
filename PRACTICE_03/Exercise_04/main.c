#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid;
    int exit_code;
    int status;

    child_pid = fork();

    if (0 <= child_pid)
    {
        if (0 == child_pid)
        {
            printf("I am Child process, my PID: %d, my Parent process PID: %d\n", getpid(), getppid());
            printf("Enter exit code for Child process: ");
            scanf("%d", &exit_code);

            printf("Child process finish its execution with exit code: %d\n", exit_code);
            exit(exit_code);
        }
        else
        {
            printf("I am Parent process, my PID: %d, my Child proces PID: %d\n", getpid(), child_pid);
            
            // Cho Child process ket thuc
            wait(&status);
            
            // Kiem tra xem Child process ket thuc co binh thuong khong bang macro WIFEXITED
            if (WIFEXITED(status)) 
            {
                // Neu Child process ket thuc binh thuong, lay ra exit code bang macro WEXITSTATUS
                printf("Child process exited normally with exit code: %d\n", WEXITSTATUS(status));
            } 
            else 
            {
                printf("Child process did not exit normally.\n");
            }
    
            printf("Parent process finished!\n");
        }
    }
    else
    {
        printf("fork() unsuccessfully!\n");
    }

    return 0;
}