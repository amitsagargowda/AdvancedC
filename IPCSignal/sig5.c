#include<signal.h>
#include<string.h>
#include<stdio.h>

sig_atomic_t sig_count=0;

void handler(int sig_num)
{
	++sig_count;
}

int main()
{
	struct sigaction new_disposition;
	memset(&new_disposition,0,sizeof(new_disposition));
	new_disposition.sa_handler=&handler;
	sigaction(SIGINT,&new_disposition,NULL);

	while(sig_count !=5);

	fprintf(stdout,"CTRL+c was pushed %d times. \n",sig_count);

	return 0;
}
