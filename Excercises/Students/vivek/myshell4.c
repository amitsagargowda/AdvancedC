#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define STDOUT 1
#define STDIN 0

void parshCommands(char *buff, char **argv){
int sumlen=0;
int len = strlen(buff);

for(int i=0, j=0; i < len; ++i ){
	if( buff[i] == ' ' || buff[i] == '\n' ){
		buff[i] = '\0';
	}
}

int i=0;
for( i=0; sumlen < len ; ++i){
argv[i] = ( buff + sumlen ); 
sumlen += strlen( (buff+sumlen) );
sumlen++;
//printf("## %s\n", argv[i]);
}
argv[i] = NULL;
//printf("## %s\n", argv[i]);
}

int main(void ){
	
	char tempbuff[512] = { "\n*****************************\n \
		                \nWelcome to my cuatom shell\n \
                                \n*****************************\n" };	       

	write(STDOUT, tempbuff, sizeof(tempbuff));

	/* @ Take commands form user.
	 *
	 */
	while(1){
	memset(tempbuff, '\0', sizeof(tempbuff));
        write(STDOUT, "\nmyshell>> ", sizeof("\nmyshell>> ") );
	read(STDIN, tempbuff, sizeof(tempbuff));
	char *argv[50];
        parshCommands(tempbuff, argv);
	int childpid = fork();
	
	if( childpid == 0 ){
	  if( execvp(argv[0], argv) < 0 )
		  perror("Error : ");
	   exit(0);
	}
	else{
	// parent waiting for child termination
	//printf("childpid = %d\n", childpid);
	int state;
	 wait(&state);

	}
	
	}//end-while
	

return 0;
}
