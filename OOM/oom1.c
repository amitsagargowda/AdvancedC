#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ARRAY[100*1024*1024];
#define NUMALLOC (127*1024)
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
		printf("Init Memory Started\n");
	//	memset(ptr[i],0xFF,1024*1024*1024);
		memcpy(ARRAY,ptr[i],sizeof(ARRAY));
		printf("Init Memory Ended\n");
		sleep(5);
	}
	while(1);

	return 0;
}
