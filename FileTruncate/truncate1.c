#include <unistd.h> 
#include <stdio.h> 
 
int main(  ) 
{ 
        int ret; 
 
        ret = truncate ("./truncate.txt", 5); 
        if (ret == -1) { 
                perror ("truncate"); 
                return -1; 
        } 
 
        return 0; 
} 

 
