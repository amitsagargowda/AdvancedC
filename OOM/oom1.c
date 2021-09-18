#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUMALLOC (10)
int main()
{
	void* ptr[NUMALLOC];
	int i;
	printf("Starting OOM killer\n");
	for(i=0;i<NUMALLOC;i++){
		ptr[i]=malloc(1024*1024*1024);
		if(NULL==ptr[i]){
			printf("Malloc failed\n");
		}else{
			printf("Malloc passed\n");
		}
	}

	for(i=0;i<NUMALLOC;i++){
		printf("Init Memory\n");
		memset(ptr[i],0xFF,1024*1024*1024);
		sleep(5);
	}
	while(1);
	return 0;
}
