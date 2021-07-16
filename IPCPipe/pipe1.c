#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	int status;

	status = pipe(fd);

	if(status < 0) {
		perror("Pipe Failed:");
		exit(-1);
	}else{
		printf("Pipe creation successfull\n");
	}

	close(fd[0]);
	close(fd[1]);

	return 0;
}
