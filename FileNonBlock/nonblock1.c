#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void show_nonblock_status(void) {
    char streams[3][7] = {"stdin", "stdout", "stderr"};

    for ( int i = 0; i < 3; ++i ) {
        int flag = fcntl(i, F_GETFL);
        if ( flag == -1 ) {
            perror("error getting flags");
            exit(EXIT_FAILURE);
        }

        if ( flag & O_NONBLOCK ) {
            printf("O_NONBLOCK is set for %s\n", streams[i]);
        } else {
            printf("O_NONBLOCK is not set for %s\n", streams[i]);
        }
    }
}

int main(void) {
    show_nonblock_status();

    int flag = fcntl(1, F_GETFL);
    if ( flag == -1 ) {
        perror("error getting flags");
        exit(EXIT_FAILURE);
    }

    flag = fcntl(1, F_SETFL, flag | O_NONBLOCK);
    if ( flag == -1 ) {
        perror("error getting flags");
        exit(EXIT_FAILURE);
    }

    show_nonblock_status();

    return 0;
}
