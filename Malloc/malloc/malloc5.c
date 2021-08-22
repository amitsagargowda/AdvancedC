#include <malloc.h>
#include <stdlib.h>
extern void *__libc_malloc(size_t);
extern void __libc_free(void*);

void *malloc(size_t size)
{
    void* result;
    result= __libc_malloc(size);
    return result;
}

void free(void *ptr)
{
	__libc_free(ptr);
}

int main ()
{
    char *p = malloc(sizeof(char));
    free(p);
}
