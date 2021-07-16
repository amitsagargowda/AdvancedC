#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<errno.h>
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

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
	struct sembuf operations[1];

	my_values[0]=1;
	args.array=my_values;

	semaphore_id=semget(sem_key,1,IPC_CREAT|S_IRWXU);

	semctl(semaphore_id,0,SETALL,args);

	
	operations[0].sem_num=0;
	operations[0].sem_op=-1;
	operations[0].sem_flg=SEM_UNDO;

	semop(semaphore_id,operations,1);

	system("ipcs -s");

	semctl(semaphore_id,0,IPC_RMID,args);

	return 0;
}
