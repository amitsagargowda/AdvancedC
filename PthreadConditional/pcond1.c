#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>

pthread_mutex_t fill_mutex;
int arr[10];
int flag=0;
pthread_cond_t cond_var=PTHREAD_COND_INITIALIZER;

void *fill() {
int i=0;
printf("\nEnter values\n");
for(i=0;i<4;i++) {
scanf("%d",&arr[i]);
}
pthread_mutex_lock(&fill_mutex); 
pthread_cond_signal(&cond_var);
pthread_mutex_unlock(&fill_mutex);
pthread_exit(NULL);
}


void *read() {
int i=0;
pthread_mutex_lock(&fill_mutex);
pthread_cond_wait(&cond_var,&fill_mutex);
pthread_mutex_unlock(&fill_mutex);
printf("Values filled in array are");
for(i=0;i<4;i++) {
printf("\n %d \n",arr[i]);
}
pthread_exit(NULL);

}


int main() {

pthread_t thread_id,thread_id1;
pthread_attr_t attr;
int ret;
void *res;
ret=pthread_create(&thread_id,NULL,&fill,NULL);
ret=pthread_create(&thread_id1,NULL,&read,NULL);
printf("\n Created threads");
pthread_join(thread_id,&res);
pthread_join(thread_id1,&res);
return 0;
}

