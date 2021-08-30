/* Example of use of fork system call */
#include <stdio.h>
// Required by for routine
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
 
int main()
{
  int pid;
 
  pid = fork();
 
  if (pid < 0) { // error occurred 
	  fprintf(stderr, "Fork failed!\n");
	  exit(-1);
  }else if (pid == 0) { // child process 
	  printf("I am the child, return from fork=%d\n", pid);
	  execlp("/media/sf_shared/git/AdvancedC/GDB/test", "test", NULL);
  }else { // parent process 
	  printf("I am the parent, return from fork, child pid=%d\n", pid);
	  printf("Parent exiting!\n");
	  exit(0);
  }
}
