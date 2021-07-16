#include <stdlib.h>                                                                                          
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

/* message structure */
struct message {
    long mtype;
    char mtext[8192];
};

int main(void)
{
    /* create message queue */
    int msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
    if (msqid == -1) {
        perror("msgget");

        return EXIT_FAILURE;
    }

    /* fork a child process */
    pid_t pid = fork();
    if (pid == 0) {
        /* child */

        struct message message;
        message.mtype = 23;
        memset(&(message.mtext), 0, 8192 * sizeof(char));
        (void)strcpy(message.mtext, "Hello parent!");

        /* send message to queue */
        if (msgsnd(msqid, &message, sizeof(long) + (strlen(message.mtext) * sizeof(char)) + 1, 0) == -1) {
            perror("msgsnd");

            return EXIT_FAILURE;
        }
    } else {
        /* parent */

        /* wait for child to finish */
        (void)waitpid(pid, NULL, 0);

        /* receive message from queue */
        struct message message;
        if (msgrcv(msqid, &message, 8192, 0, 0) == -1) {
            perror("msgrcv");

            return EXIT_FAILURE;
        }

        printf("%s\n", message.mtext);

        /* destroy message queue */
        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl");

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
