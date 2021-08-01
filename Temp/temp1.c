#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void error (char *str);

int main (int argc, char **argv)
{
    char filename [64] = "/tmp/mkstemp-example-XXXXXX";
    char buf [128];

    int fd;

    if ((fd = mkstemp (filename)) == -1)
        error ("mkstemp");
    unlink (filename);

    strcpy (buf, "Hello World!\n");

    if (write (fd, buf, strlen (buf)) == -1)
        error ("write");

    return 0;
}

void error (char *str)
{
    perror (str);
    exit (1);
}
