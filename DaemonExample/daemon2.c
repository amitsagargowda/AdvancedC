#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int nochdir=1;
	int noclose=0;	

	daemon(nochdir,noclose);
	
	return 0;	
}
