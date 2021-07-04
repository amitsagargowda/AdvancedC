#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main()
{
    pid_t pid;
    int fd=0;
    char buf[256];
    fd=open("./testfile",O_RDONLY);
    pid = fork();
    if (pid < 0) {
        printf("failed to fork..\n");
    } else if (pid == 0) {
	printf("child process...\n");
	read(fd,buf,sizeof(buf));
	printf("Data=%s\n",buf);
    } else if (pid > 0) {
        printf("parent process..\n");
    }

    sleep(2);
    return 0;
}
