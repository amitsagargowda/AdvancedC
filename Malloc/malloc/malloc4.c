#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>

int main()
{
    char* pStr;

    //Enable memory leak trace.
    //Must be called before calling malloc() etc.
    mtrace();

    pStr = (char*) calloc(1, 10); 

    //Disable memory tracing before exit
    muntrace();

    return 0;
}

//MALLOC_TRACE=./malloc4.txt ./malloc4
//mtrace malloc4 malloc4.txt
