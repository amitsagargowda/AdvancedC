#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t s;

int main(int argc,char* argv[]) 
{
	int i=0;

	i=atoi(argv[1]);

	sem_init(&s, 0, 10); 
  
	while(i--){
		sem_wait(&s); 
	}

	sem_post(&s); 

	sem_destroy(&s); 
}
