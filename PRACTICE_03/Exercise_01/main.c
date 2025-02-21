#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
    pid_t child_pid;

    child_pid  = fork();

    if (0 <= child_pid)
    {
        if (0 == child_pid)
        {
            printf("\nI am the Child process, my PID: %d, my Parent PID: %d\n", getpid(), getppid());
        }
        else
        {
            printf("\nI am the Parent process, my PID: %d, my Child PID: %d\n", getpid(), child_pid);
        }
    }
    else
    {
        printf("fork() unsuccessfully\n");
    }
    return 0;
}