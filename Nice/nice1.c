#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
       int nice(int inc);


int main()
{
	printf("Sleeping1 ...\n");
	sleep(10);
	nice(10);
	printf("Sleeping2 ...\n");
	sleep(10);
	nice(-10);
	printf("Sleeping3 ...\n");
	sleep(10);
	return 0;
}
