#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#define POLICY SCHED_RR

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

static void *low(void *tmp)
{
	printf("I am Low Thread\n");
	pthread_mutex_lock(&mutex1);
	while(1){
		printf("##########Low#########\n");
		
	}
	return NULL;
}

static void* mid(void *tmp)
{
	printf("I am mid thread\n");
	sleep(5);
	while(1){
		printf("**********Mid********\n");
	}
	return NULL;
}

static void* high(void* tmp)
{
        printf("I am High thread\n");
	sleep(2);
	pthread_mutex_lock(&mutex1);
        while(1){
                printf("@@@@@@@@@@@@@High@@@@@@@@@@@@@\n");
        }
        return NULL;
	
}

int main(void)
{
	pthread_t thread_id1,thread_id2,thread_id3;
	pthread_attr_t attr;
	struct sched_param param;
	int rc = 0;

	rc = pthread_attr_init(&attr);
	if (rc != 0) {
		printf("Error: pthread_attr_init\n");
		exit(0);
	}

	rc = pthread_attr_setschedpolicy(&attr, POLICY);
	if (rc != 0) {
		printf("Error: pthread_attr_setschedpolicy\n");
		exit(0);
	}
	int priority;
	priority = sched_get_priority_max(POLICY);
	if (priority == -1) {
		printf("Error: sched_priority_get_max\n");
		exit(0);
	}
	param.sched_priority = priority-6;

	rc = pthread_attr_setschedparam(&attr, &param);
	if (rc != 0) {
		printf("Error:pthread_attr_setschedparam\n");
		exit(0);
	}

	rc = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if (rc != 0) {
		printf("Error:pthread_attr_setinheritsched\n");
		exit(0);
	}

	/* Create the thread with the attr */
	rc = pthread_create(&thread_id1, &attr, low, NULL);
	if (rc != 0) {
		printf("Error:pthread_create\n");
		exit(0);
	}
        param.sched_priority = priority-4;

        rc = pthread_attr_setschedparam(&attr, &param);
        if (rc != 0) {
                printf("Error:pthread_attr_setschedparam\n");
                exit(0);
        }

        rc = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        if (rc != 0) {
                printf("Error:pthread_attr_setinheritsched\n");
                exit(0);
        }

        /* Create the thread with the attr */
        rc = pthread_create(&thread_id2, &attr,mid, NULL);
        if (rc != 0) {
                printf("Error:pthread_create\n");
                exit(0);
        }
        param.sched_priority = priority;

        rc = pthread_attr_setschedparam(&attr, &param);
        if (rc != 0) {
                printf("Error:pthread_attr_setschedparam\n");
                exit(0);
        }

        rc = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        if (rc != 0) {
                printf("Error:pthread_attr_setinheritsched\n");
                exit(0);
        }

        /* Create the thread with the attr */
        rc = pthread_create(&thread_id3, &attr,high, NULL);
        if (rc != 0) {
                printf("Error:pthread_create\n");
                exit(0);
        }



	rc = pthread_join(thread_id1, NULL);
	if (rc != 0) {
		printf("Error:pthread_join\n");
		exit(0);
	}

        rc = pthread_join(thread_id2, NULL);
        if (rc != 0) {
                printf("Error:pthread_join\n");
                exit(0);
        }


        rc = pthread_join(thread_id3, NULL);
        if (rc != 0) {
                printf("Error:pthread_join\n");
                exit(0);
        }



	return 0;
}
