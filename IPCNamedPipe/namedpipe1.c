#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>

int main()
{
	FILE* fptr;
	mkfifo("/tmp/myfifo",S_IRWXU|S_IROTH);
	fptr=fopen("/tmp/myfifo","w");
	fprintf(fptr,"%s\n","Hello!");
	fflush(fptr);
	fclose(fptr);
	return 0;
}
