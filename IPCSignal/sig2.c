#include<stdio.h>
#include<wait.h>
#include<signal.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int stat;
    pid_t pid;
    if ((pid = fork()) == 0)
        while(1) ;
    else
    {
        kill(pid, SIGINT);
        wait(&stat);
        if (WIFSIGNALED(stat))
            psignal(WTERMSIG(stat), "Child term due to");
    }
}

