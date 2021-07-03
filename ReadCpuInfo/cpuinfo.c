#include <stdio.h>
#include <string.h>

void get_cpu_info()
{
	FILE *fp;
	char buffer[1024];
	size_t bytes_read;

	fp=fopen("/proc/cpuinfo","r");

	bytes_read=fread(buffer,1,sizeof(buffer),fp);
	fclose(fp);
	if(bytes_read == 0 || bytes_read == sizeof(buffer))
		buffer[bytes_read]='\0';
	printf("The CPU information is:\n %s",buffer);
}

int main()
{
	get_cpu_info();
	return 0;
}

