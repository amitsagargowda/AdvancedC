#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned long u64;

static u64 get_rcx(void)
{
	__asm__ __volatile__("push %rcx\n\t"
				"movq $5, %rcx\n\t"
				"movq %rcx, %rax");/* at&t syntax: movq <src_reg>, <dest_reg> */
	__asm__ __volatile__("pop %rcx");
}

int main(void)
{
	printf("Hello, inline assembly:\n [RCX] = 0x%lx\n", get_rcx());
	exit(0);
}
