#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* fptr;

	char buff[256];

	fptr=fopen("file.txt","r");

	if(NULL==fptr){
		perror("File open:");
		exit(-1);
	}

	printf("Curr position1 =%ld\n",ftell(fptr));

	fgets(buff,sizeof(buff),fptr);

	printf("Curr position2 =%ld\n",ftell(fptr));

	printf("Data1:%s",buff);

	rewind(fptr);

	printf("Curr position3 =%ld\n",ftell(fptr));

	fscanf(fptr,"%s",buff);

	printf("Data2:%s",buff);

	printf("\nCurr position4 =%ld\n",ftell(fptr));

	rewind(fptr);

	fread(buff,1,sizeof(buff),fptr);

	printf("Data3:%s",buff);

	fprintf(fptr,"%s ","Appending Data1");

	fwrite("Appending Data2",1,strlen("Appending Data2"),fptr);

	printf("\nCurr position5 =%ld\n",ftell(fptr));

	fseek(fptr,0,SEEK_SET);

	printf("\nCurr position6 =%ld\n",ftell(fptr));

	fclose(fptr);

	return 0;
}
