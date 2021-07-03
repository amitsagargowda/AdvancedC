#include <stdio.h>
#include <unistd.h>
int main (void) {
	printf("I am  process %ld\n", (long)getpid());
	printf("My parent id is %ld\n", (long)getppid());
	return 0; 
}

