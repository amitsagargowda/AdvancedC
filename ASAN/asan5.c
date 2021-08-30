#include <stdlib.h>
int main(int argc, char **argv) {
 int *array =  malloc(sizeof(int)*100);
 free(array);
 return array[argc]; // BOOM
}

