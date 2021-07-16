#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<errno.h>
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>

int main()
{
	int semaphore_id;
	key_t sem_key=3434;
	semaphore_id=semget(sem_key,1,IPC_CREAT|S_IRWXU);
	if(errno!=0)
		fprintf(stderr,"An error occured in semget:\n%s\n",strerror(errno));
	else
		fprintf(stdout,"The semaphore ID is: %d\n",semaphore_id);
	return 0;
}
