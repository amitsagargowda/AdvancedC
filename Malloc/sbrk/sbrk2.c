#include <stdio.h>
#include <unistd.h>
int  main ()  
{  
 /* Allocate 10 bytes of space and return the first address of the space */
 void * p = sbrk (12);  
 void * p2 = sbrk (4);  
 void * p3 = sbrk (4);  
 void * p4 = sbrk (4);  
  /* Use parameter 0 to get the starting position of unallocated space */
 void *p0 = sbrk (0);
 void * p5 = sbrk (-24);
 void *p01 = sbrk(0);
 printf ( "p =%p\n" , p);  
 printf ( "p2 =%p\n" , p2);  
 printf ( "p3 =%p\n" , p3);  
 printf ( "p4 =%p\n" , p4);  
 printf ( "p0 =%p\n" , p0);  
 printf ( "p5 =%p\n" , p5);  
 printf ( "p01=%p\n", p01);
 printf ( "pid =%d\n" , getpid ());  
 while (1);  
}  
