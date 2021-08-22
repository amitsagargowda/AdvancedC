#include <stdio.h>
#include <unistd.h>
int  main ()  
{  
 void * p = sbrk (0);  
 int * p1 = p;  
 brk (p1 + 4); //16 bytes of space allocated
 p1 [0] = 10;  
 p1 [1] = 20;  
 p1 [2] = 30;  
 p1 [3] = 40;  
 p1 [4] = 50;  
 int * p2 = sbrk (4);  
 printf ( "* p2 =% d\n" , * p2);  
 brk (p1 + 1024); //Allocate the space of the whole page
 brk (p1 + 512); //Free half of the space
 brk (p1); //Free all space
} 
