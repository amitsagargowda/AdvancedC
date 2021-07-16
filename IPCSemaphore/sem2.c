#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<errno.h>
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int* array;
	struct seminfo* __buf;
};

int main()
{
	int semaphore_id;
	key_t sem_key=3434;
	union semun args;
	unsigned short int my_values[1];

	my_values[0]=1;
	args.array=my_values;

	semaphore_id=semget(sem_key,1,IPC_CREAT|S_IRWXU);

	semctl(semaphore_id,0,SETALL,args);



	return 0;
}
