/*
 * inline.c
 *
 * A small program that illustrates how to inline assembly in C code
 */
#include <stdio.h>

int main(void)
{
        int foo = 10, bar = 15;
        asm("addl  %%ebx,%%eax"
                             :"=a"(foo)
                             :"a"(foo), "b"(bar)
                             );
        printf("foo+bar=%d\n", foo);
        return 0;
}