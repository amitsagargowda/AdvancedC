#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define STDOUT 1
#define STDIN 0

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
	system(tempbuff);
	
	}//end-while
	

return 0;
}
