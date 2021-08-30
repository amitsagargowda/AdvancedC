#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    char *msg = "Hello world!";
    char *ptr = NULL;

    ptr = malloc(strlen(msg));

    strcpy(ptr, msg);

    printf("%s\n", ptr);

    return 0;
}
