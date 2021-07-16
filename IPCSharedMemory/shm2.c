#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char* shared_memory;
	int id;
	id=shmget(3434,0,IPC_CREAT|S_IRWXU);
	if(errno!=0)
		fprintf(stderr,"An error occured in shmget:\n%s\n",strerror(errno));

	shared_memory=shmat(id,NULL,0);

	if(errno!=0)
		fprintf(stderr,"An error occured in shmat:\n%s\n",strerror(errno));

	sprintf(shared_memory,"%s","Hello, World!\n");
	fprintf(stdout,"Something put in shared memory!\n");
	
	system("ipcs -m");

	shmdt(shared_memory);

	return 0;
}
