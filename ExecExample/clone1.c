#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
int main() {
    char* commandpath = "/bin/ls";
    char* commandfile = "ls";
    char* argument_list_file[] = {"ls", "-l", NULL};
    char* argument_list_path[] = {"/bin/ls","-l",NULL};
 
    printf("Before calling execvp()\n");
 
    //int status_code= execl(commandpath,"/bin/ls","-l",NULL);
    //int status_code= execlp(commandfile,"ls","-l",NULL);
    //int status_code = execv(commandpath, argument_list_path);
    int status_code = execvp(commandfile, argument_list_file);
 
    if (status_code == -1) {
        printf("Process did not terminate correctly\n");
        exit(1);
    }
 
    printf("This line will not be printed if exec() runs correctly\n");
 
    return 0;
}
