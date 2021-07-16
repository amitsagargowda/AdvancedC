#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void writer(FILE* stream)
{
	int count=0;
	for(count=0;count<=5;count++)
	{
		fprintf(stream,"This is a message number %d.\n",count);
		fflush(stream);
		sleep(1);
	}
}

void reader(FILE* stream)
{
	char buffer[100];
	while(!feof(stream) && !ferror(stream) && fgets(buffer,sizeof(buffer),stream)!=NULL)
		fputs(buffer,stdout);
}

int main()
{
	int fd[2];
	pid_t pid;
	FILE* stream;

	pipe(fd);

	pid=fork();

	if(pid == (pid_t) 0){
		fprintf(stderr,"This is child process with pid: %d.\n",(int)getpid());
		close(fd[1]);
		stream=fdopen(fd[0],"r");
		reader(stream);
		close(fd[0]);
	}else{
		fprintf(stderr,"This is parent process with pid: %d.\n",(int)getpid());
		close(fd[0]);
		stream=fdopen(fd[1],"w");
		writer(stream);
		close(fd[1]);
		wait(NULL);
	}
	return 0;
}
