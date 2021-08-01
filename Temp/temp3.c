#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error (char *str);

int main (int argc, char **argv)
{
    char buf [128];

    FILE *fp;

    if ((fp = tmpfile ()) == NULL)
        error ("tmpfile");

    strcpy (buf, "Hello World!\n");

    if (fwrite (buf, strlen (buf), 1, fp) != 1)
        error ("fwrite");

    return 0;
}

void error (char *str)
{
    perror (str);
    exit (1);
}
