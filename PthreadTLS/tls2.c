#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct TLS_Big_data_ {
  int thread_id;
  int data[2048];
} TLS_Big_data;

void * thread_run(void *);
void show_my_tls();

pthread_key_t thr_id_key;

void main(int argc, void ** argv)
{
    pthread_t thread;
    TLS_Big_data * tls_data;
    int i;

    pthread_key_create(&thr_id_key, NULL);

    for(i = 1; i <= 10; i++)
    {
        tls_data = (TLS_Big_data *)malloc(sizeof(TLS_Big_data));
        tls_data->thread_id = i;
        pthread_create(&thread, NULL,
                       thread_run, (void *)(tls_data));
    }

    pthread_exit(NULL);
}

void * thread_run(void * param)
{
    void *tls_val = param;
  
    pthread_setspecific(thr_id_key, tls_val);

    show_my_tls();

    /* release the meory held by TLS*/
    TLS_Big_data * tls_data;
    tls_data = (TLS_Big_data *)pthread_getspecific(thr_id_key);

    if (tls_data) free(tls_data);
    
    return NULL;
}

void show_my_tls()
{
   TLS_Big_data * tls_data;
   tls_data = (TLS_Big_data *)pthread_getspecific(thr_id_key);

   if (tls_data) {
     printf("Thread %lx holds TLS has %d\n", pthread_self(),
        tls_data->thread_id);
   } else {
     printf("Thread %lx TLS data not found\n", pthread_self());
   }
}
