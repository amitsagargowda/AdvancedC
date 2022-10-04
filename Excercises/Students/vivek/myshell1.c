#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
/*
#include <>
#include <>
#include <>
#include <>
#include <>
#include <>
*/



void parshCommands(char *arg, char **argv){

	int len = strlen(arg);

	int i=0;

	while( i < len ){
		if( *arg == ' ' || arg[i] == '\n'){
			*arg++ = '\0';
		}
		if( i < len ){
			strcpy(*argv++, arg);
		}
	}
}//end-parshCommands



int main(void ){
	printf("\n*****************************\n");
	printf("\nWelcome to my cuatom shell\n ");
	printf("\n*****************************\n");
	
	
	char readarg[50];
	int i=0;

	/* @ Take commands form user.
	 *
	 */
	while(1){
	i=0;
	fflush(stdin);
	printf("\nmyshell>> ");
	scanf("%[^\n]s", readarg);

	system(readarg);

	getchar();
	
	for(int j=0; j < 50; j++)
		memset(readarg,'\0',10);
	
	fflush(stdin);
	fflush(stdout);
	fflush(NULL);
	}//end-while
	

return 0;
}
