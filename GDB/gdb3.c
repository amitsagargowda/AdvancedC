#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
pthread_mutex_t first_mutex, second_mutex;
void *fun1(){
	pthread_mutex_lock(&first_mutex);
	puts("Thread ONE acquired first_mutex");
	sleep(1);
	pthread_mutex_lock(&second_mutex);
	puts("Thread ONE acquired second_mutex");
	pthread_mutex_unlock(&second_mutex);
	puts("Thread ONE released second_mutex");
	pthread_mutex_unlock(&first_mutex);
	puts("Thread ONE released first_mutex");
}
void *fun2(){
	pthread_mutex_lock(&second_mutex);
	puts("Thread TWO acquired second_mutex");
	sleep(1);
	pthread_mutex_lock(&first_mutex);
	puts("Thread TWO acquired first_mutex");
	pthread_mutex_unlock(&first_mutex);
	puts("Thread TWO released first_mutex");
	pthread_mutex_unlock(&second_mutex);
	puts("Thread TWO released second_mutex");
}

int main(){
	pthread_mutex_init(&first_mutex,NULL);
	pthread_mutex_init(&second_mutex,NULL);
	pthread_t one,two;
	pthread_create(&one,0,fun1,NULL);
	pthread_create(&two,0,fun2,NULL);
	pthread_join(one,NULL);
	pthread_join(two,NULL);
	printf("Thread Joined\n");

	return 0;
}
