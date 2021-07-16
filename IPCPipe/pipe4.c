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

	pipe(fd);

	pid=fork();

	if(pid == (pid_t) 0){
		char string[10];
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		scanf("%s",string);
		fprintf(stdout,"The message is: %s.\n",string);
	}else{
		FILE* stream;
		close(fd[0]);
		stream=fdopen(fd[1],"w");
		fprintf(stream,"%s","Hello!");
		fflush(stream);
		fprintf(stdout,"A message has been written to pipe.\n");
		close(fd[1]);
		waitpid(pid,NULL,0);
	}
	return 0;
}
