#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<time.h>

int main()
{
	int id;
	struct shmid_ds info;
	id=shmget(3434,0,IPC_CREAT|S_IRWXU);

	shmctl(id,IPC_STAT,&info);

	fprintf(stdout,"Here is some information about shared memory:\n"
			"Size of segment: %ld\n"
			"PID of creator: %d\n"
			"Last attach time: %s\n",info.shm_segsz,info.shm_cpid,ctime(&info.shm_atime));


	shmctl(id,IPC_RMID,0);

	if(errno !=0)
		fprintf(stderr,"An error occured i shmctl!:\n%s\n",strerror(errno));

	return 0;
}
