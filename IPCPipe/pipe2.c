#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include<sys/wait.h>


int main()
{
    int stat;
    int fd[2];
    int result = pipe(fd);
    if (result != 0)
    {
        perror("pipe create failed:");
	exit(0);
    }
    
    pid_t childid;
    childid = fork();
    if (childid == -1) {
        perror("Failed to fork:");
	exit(0);
    }

    if (childid == 0) {
        /* child */
        close(fd[1]); /* child closes the write end */
        char buffer[50];
        read(fd[0], buffer, sizeof(buffer));
        printf("Message from the parent: %s", buffer);
	close(fd[0]);
    }else{
        /* parent */
        close(fd[0]); /* parent closes the read end */
        char towrite[] = "Hello from parent!\n";
        write(fd[1], towrite, strlen(towrite) + 1);
        pid_t cpid = waitpid(childid, &stat, 0);
        if (WIFEXITED(stat))
            printf("Child %d terminated with status: %d\n",
                   cpid, WEXITSTATUS(stat));
	
	close(fd[1]);
    }

    return 0;
}
