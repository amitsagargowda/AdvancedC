#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned long u64;

static u64 get_cr0(void)
{
	__asm__ __volatile__("movq %cr0, %rax");
}

int main(void)
{
	printf("Hello, inline assembly:\n [CR0] = 0x%lx\n", get_cr0());
	exit(0);
}
