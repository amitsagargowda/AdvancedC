#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int number=14;

void* func1(void* args)
{
	while(number!=0)
	{
		sleep(1);
		number--;
		printf("%d %d\n",(int)args,number);
	}
	return NULL;
}

int main()
{
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,&func1,(void*)111);
	pthread_create(&tid2,NULL,&func1,(void*)222);
	pthread_create(&tid2,NULL,&func1,(void*)333);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	return 0;
}
