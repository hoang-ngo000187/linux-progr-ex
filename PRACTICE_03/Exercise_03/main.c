#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("Child process receive signal SIGUSR1 from Parent process (%d)\n", signum);
    exit(0);
}

int main()
{
    pid_t child_pid;

    child_pid = fork();

    if (0 <= child_pid)
    {
        if (0 == child_pid)
        {
            printf("I am Child process, my PID: %d, my Parent process PID: %d\n", getpid(), getppid());
            // Dang ky ham xu  ly signal
            signal(SIGUSR1, signal_handler);

            while (1)
            {
                printf("Child process is waiting for signal from Parent process ... ... ...\n");
                pause();
            }
        }
        else
        {
            printf("I am Parent process, my PID: %d, my Child proces PID: %d\n", getpid(), child_pid);
            printf("Parent process will send a signal 'SIGUSR1' to Child process after 3s ... ... ...\n");

            sleep(3);

            // Gui signal SIGUSR1 den tien trinh con
            kill(child_pid, SIGUSR1);

            // Doi 1s cho tien trinh con xu ly signal
            sleep(1);

            wait(NULL);
            printf("Parent process finished!\n");
        }
    }
    else
    {
        printf("fork() unsuccessfully!\n");
    }

    return 0;
}