#include<errno.h>
#include<stdio.h>
#include <string.h>

int main()
{
	FILE* fd;
	fd=fopen("/etc/shadow","w");
	if(fd==NULL)
	{
		printf("Failed=%d\n",errno);
		printf("%s\n",strerror(errno));
	}
	else
	{
		fclose(fd);
	}
	return 0;
}