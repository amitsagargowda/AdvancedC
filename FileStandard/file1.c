#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	FILE* fptr;

	fptr=fopen("file.txt","r");

	if(NULL==fptr){
		perror("File open:");
		exit(-1);
	}

	fclose(fptr);

	return 0;
}
