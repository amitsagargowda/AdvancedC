#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
	printf("Before fork\n");
	vfork();
	printf("after fork\n");
}
