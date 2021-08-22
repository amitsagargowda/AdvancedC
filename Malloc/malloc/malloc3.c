#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
int main()
{
 
    void* p=malloc(10);

    printf("#####################################\n");
 
    malloc_info(0,stdout);

    void* p2=malloc(20);

    printf("#####################################\n");

    malloc_info(0,stdout);

    void* p3=malloc(200);

    printf("#####################################\n");

    malloc_info(0,stdout);

    return 0;
}
