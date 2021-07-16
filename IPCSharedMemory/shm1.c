#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/stat.h>
#include<errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char* shared_memory;
	size_t sh_size=0x80;
	int id;

	fprintf(stdout,"The system page size is: %d.\n",getpagesize());
	id=shmget(3434,sh_size,IPC_CREAT|S_IRWXU);

	if(errno!=0)
		fprintf(stderr,"An Error occured!\n%s\n",strerror(errno));

	fprintf(stdout,"The shared memory ID is:%d.\n",id);

	return 0;
}
