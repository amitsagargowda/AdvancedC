#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define POLICY SCHED_FIFO
//#define POLICY SCHED_RR

static void *thread1(void *tmp)
{
	while(1){
		printf("##########thread 1#########\n");
		sleep(1);
	}
	return NULL;
}

static void* thread2(void *tmp)
{
	while(1){
		printf("**********thread 2********\n");
	}
	return NULL;
}

int main(void)
{
	pthread_t thread_id1,thread_id2;
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
	rc = pthread_create(&thread_id1, &attr, thread1, NULL);
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
        rc = pthread_create(&thread_id2, &attr, thread2, NULL);
        if (rc != 0) {
                printf("Error:pthread_create\n");
                exit(0);
        }
        param.sched_priority = 0;


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

	return 0;
}
