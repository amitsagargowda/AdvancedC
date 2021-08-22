#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
void main(void)
{
    uint8_t *test;

    test = (uint8_t *)malloc(sizeof(uint8_t)*4);
    printf("sizeof(test) = %ld\n",malloc_usable_size(test));

    free(test); 
} 
