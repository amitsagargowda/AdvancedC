#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alloc()
{
    char *ptr;

    ptr = malloc(10);

    memset(ptr, 0, 10);
}

int main(int argc, const char *argv[])
{
    int i;

    for (i = 0; i < 3; i++)
        alloc();

    printf("OK!\n");

    return 0;
}
