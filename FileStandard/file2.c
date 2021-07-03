#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	int fd;
	FILE* fptr;

	fd=open("file.txt",O_RDONLY);
	
	fptr=fdopen(fd,"r");

	if(NULL==fptr){
		perror("File open:");
		exit(-1);
	}

	fclose(fptr);

	return 0;
}

