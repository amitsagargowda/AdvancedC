#include <stdio.h>
#include <unistd.h>

int main()
{
	char buffer[256];
	FILE* stream=popen("ls","r");
  	while ( fgets( buffer, sizeof(buffer),stream))
  	{
	    printf("%s",buffer);
  	}
	pclose(stream);
	fprintf(stdout,"Finished!\n");
	return 0;
}
