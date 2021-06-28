#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#define PACKAGE "mmap"

int main(int argc, char *argv[]) {
 int input, output;
 size_t filesize;
 void *source, *target;

 if((input = open("mmap_test1", O_RDONLY)) == -1)
  fprintf(stderr, "%s: Error: opening file: %s\n", PACKAGE, argv[1]), exit(1);

 filesize = lseek(input, 0, SEEK_END);

 if((source = mmap(0, filesize, PROT_READ, MAP_SHARED, input, 0)) == (void *) -1)
  fprintf(stderr, "Error mapping input file: %s\n", argv[1]), exit(1);

 munmap(source, filesize);

 close(input);

 return 0;
}
