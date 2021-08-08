#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
        uid_t uid = 1001; // user
	int real;
        real = getuid();
  	printf("The REAL UID =: %d\n", real);
        setuid(uid);
        real = getuid();
        printf("The REAL UID =: %d\n", real);
        setuid(uid);
	return 0;
}
