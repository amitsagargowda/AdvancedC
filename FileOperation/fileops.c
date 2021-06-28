#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main (){
	 int fd, read_bytes;
	 char buff[256];
	 fd = open("/home/test/testfile",O_RDWR);
	 if (fd < 0){
		perror("Error opening file\n");
		return 0;
	 }
	 printf("FD (%d)\n", fd);
	 read_bytes = read(fd, buff, 15);
	 if (read_bytes < 0){
		printf("Read Error\n");
		close(fd);
		return 0;
	 }
	 printf("File contents\n");
	 printf("%s\n", buff);
	 strcpy(buff,"testing_write_system_call");
	 read_bytes = write(fd, buff, 20);
	 if(read_bytes<0){
		 printf("Write:%s\n",strerror(errno));
	 }
	 close(fd);
}
