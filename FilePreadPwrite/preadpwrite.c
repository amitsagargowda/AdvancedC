#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
 
int main()
{
    int fd = open("test.txt", O_RDWR);
    if(fd < 0)
    {
        perror("open failed");
        return 1;
    }
 
    char buf[1024] = {0};
    int offset = 5;
    ssize_t ret = 0;
    int count = 10;
    if((ret = pread(fd, buf, count, offset)) == -1)
    {
        perror("pread failed");
        return 1;
    }
    
    printf("read buf = %s\n",buf);

    strcpy(buf,"Is this true");

    if((ret = pwrite(fd, buf, count, offset)) == -1)
    {
        perror("pread failed");
        return 1;
    }

    return 0;

}

