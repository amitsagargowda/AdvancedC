#include <pthread.h>
#include <sched.h>
#include <stdio.h>

void*
evenCountThread(void* ignore)
{
int i;
unsigned int count=0;

for (;;) {

for(i=0; i<5; i++) {
printf ("even Thr: %d\n", count);
count += 2;
}
sched_yield();
}

return NULL;
}


void*
oddCountThread(void* ignore)
{
int i;
unsigned int count=1;

for (;;) {

for(i=0; i<5; i++) {
printf ("odd Thr: %d\n", count);
count += 2;
}
sched_yield();
}

return NULL;
}

int
main()
{
pthread_t t1,t2;

pthread_create (&t1, NULL, evenCountThread, NULL);
pthread_create (&t2, NULL, oddCountThread, NULL);
pthread_join(t2, NULL);
return 0;
}
