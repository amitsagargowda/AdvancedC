#include<stdio.h>
#include<unistd.h>
#include<signal.h>
 
void sig_handler(int signum){
 
  printf("Inside handler function\n");
}
 
int main(){
 
  signal(SIGALRM,sig_handler); // Register signal handler
 
  alarm(4);  // Scheduled alarm after 4 seconds
  alarm(1);  // Scheduled alarm after 1 seconds
 
  for(int i=1;;i++){
 
    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
}
 
return 0;
}

