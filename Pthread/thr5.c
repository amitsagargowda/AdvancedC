#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>

struct character
{
	char my_char;
	int count;
};

void* thread_routine(void* args)
{
	struct character *ch = (struct character*) args;
	int i;
	for(i=0;i<ch->count;i++)
		fputc(ch->my_char,stderr);
	return NULL;
}

int main()
{
	pthread_t tid1,tid2;
	pthread_attr_t attr;
	struct character t1args,t2args;
	t1args.my_char='x';
	t2args.my_char='y';
	t1args.count=3000;
	t2args.count=2000;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&tid1,&attr,&thread_routine,(void*)&t1args);
	pthread_create(&tid2,&attr,&thread_routine,(void*)&t2args);
	sleep(100);
	return 0;
}
