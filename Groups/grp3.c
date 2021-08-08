#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void print_uids();
void print_uids_and_wait_for_user_input();

int
main(void) {
    print_uids_and_wait_for_user_input();

    setuid(0);

    print_uids_and_wait_for_user_input();

    seteuid(1000);

    print_uids_and_wait_for_user_input();

    seteuid(0);
    setuid(1000);
    seteuid(0);

    print_uids_and_wait_for_user_input();
    
    printf("Replacing this process with 'sleep' and sleeping for 10 seconds...\n");
    execl("/bin/sleep", "/bin/sleep", "10", NULL);

    return 0;
}

void print_uids() {
    printf("ruid: %d\n", getuid());
    printf("euid: %d\n", geteuid());
}

void print_uids_and_wait_for_user_input() {
    print_uids();
    getchar();
}
