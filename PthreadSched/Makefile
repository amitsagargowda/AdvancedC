all: psched1 psched2

psched1: psched1.c
	gcc -g -O0 -o psched1 psched1.c -lpthread

psched2: psched2.c
	gcc -g -O0 -o psched2 psched2.c -lpthread


clean:
	rm -rf *.o psched1 psched2
