//Unitialized variable access
#include <stdio.h>

int foo(int x)
{
    if(x < 10)
    {
        printf("x is less than 10\n");
    }
}

int main()
{
    int y;
    foo(y);
}
