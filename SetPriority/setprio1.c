#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   int prio_process, prio_pgroup, prio_user; 
   pid_t pid=getpid();

   printf("Sleeping1 ...\n");
   sleep(10);
   prio_process = setpriority(PRIO_PROCESS, pid,10);

   printf("Process (%d) Priority is %d.\n", pid, prio_process);

   sleep(10);
   
   return 0;
}
