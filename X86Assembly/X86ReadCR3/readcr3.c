#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned long u64;

static u64 get_cr3(void)
{
	__asm__ __volatile__(
		    "movq %cr3, %rax");	
}

int main(void)
{
	printf("Hello, inline assembly:\n [CR3] = 0x%lx\n", get_cr3());
	exit(0);
}

