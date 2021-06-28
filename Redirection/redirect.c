#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
	int a,b;
	int fd;
	fd = open("file1",O_WRONLY);
	if(fd>=0){
		close(0);
		dup(fd);
		close(fd);
	}
	scanf("%d %d",&a,&b);
	printf("A=%d B=%d\n",a,b);
	return 0;
}
