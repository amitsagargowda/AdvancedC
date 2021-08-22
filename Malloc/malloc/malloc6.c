#include <malloc.h>
#include <stdlib.h>
#include <alloca.h>

int main ()
{
    char *p = alloca(sizeof(char));
    printf("Mem=%p\n",p);
    while(1);
}
