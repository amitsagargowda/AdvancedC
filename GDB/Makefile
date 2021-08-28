all: gdb1 gdb2 gdb3 test

gdb1: gdb1.c
	gcc -g -O0 -o gdb1 gdb1.c 

gdb2: gdb2.c
	gcc -g -O0 -o gdb2 gdb2.c 

gdb3: gdb3.c
	gcc -g -O0 -o gdb3 gdb3.c -lpthread

test: test.c
	gcc -g -O0 -o test test.c

clean:
	rm -rf *.o gdb1 gdb2 gdb3 test
