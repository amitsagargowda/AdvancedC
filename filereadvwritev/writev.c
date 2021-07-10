#include <stdio.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/uio.h> 
#include <unistd.h>
#include <string.h>
 
int main (  ) 
{ 
        char foo[48], bar[51], baz[49]; 
        struct iovec iov[3]; 
        ssize_t nr; 
        int fd, i; 
 
        fd = open ("test.txt", O_RDWR); 
        if (fd == -1) { 
                perror ("open"); 
                return 1; 
        } 

	strcpy(foo,"Test Data1");
	strcpy(bar,"Test Data2");
	strcpy(baz,"Test Data3");
 
        /* set up our iovec structures */ 
        iov[0].iov_base = foo; 
        iov[0].iov_len = strlen(foo); 
        iov[1].iov_base = bar; 
        iov[1].iov_len = strlen(bar); 
        iov[2].iov_base = baz; 
        iov[2].iov_len = strlen(baz); 
 
        /* read into the structures with a single call */ 
        ssize_t ret = 0; 
 
        for (i = 0; i < 3; i++) { 
                ssize_t nr; 
 
                nr = write (fd, iov[i].iov_base, iov[i].iov_len); 
                if (nr == -1) { 
                        ret = -1; 
                        break; 
                } 
                ret += nr; 
        } 
 
        return 0; 
} 
