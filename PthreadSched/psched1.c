#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#define PRIORITY 20
#define POLICY SCHED_FIFO

static void *thread(void *tmp)
{
	struct sched_param param;
	int policy;
	if (pthread_getschedparam(pthread_self(), &policy, &param) != 0) {
		printf("pthread_getschedparam failed\n");
		exit(0);
	}
	if (policy == SCHED_FIFO) {
		printf("Sched policy=FIFO\n");
	}else if (policy == SCHED_RR) {
		printf("Sched policy=RR\n");
	}else if(policy == SCHED_OTHER){
		printf("Sched Policy=Other\n");
	}else{
		printf("Unknown Scheduling policy\n");
	}
	printf("Scheduling priority=%d\n",param.sched_priority);
	return NULL;
}

int main(void)
{
	pthread_t thread_id;
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
#if 0
	param.sched_priority = PRIORITY;
#else
	int priority;
	priority = sched_get_priority_max(POLICY);
	if (priority == -1) {
		printf("Error: sched_priority_get_max\n");
		exit(0);
	}
	param.sched_priority = priority;
#endif
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
	rc = pthread_create(&thread_id, &attr, thread, NULL);
	if (rc != 0) {
		printf("Error:pthread_create\n");
		exit(0);
	}

	rc = pthread_join(thread_id, NULL);
	if (rc != 0) {
		printf("Error:pthread_join\n");
		exit(0);
	}
	return 0;
}
