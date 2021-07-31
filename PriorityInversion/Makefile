all: inv1 inv2

inv1: inv1.c
	gcc -g -O0 -o inv1 inv1.c -lpthread

inv2: inv2.c
	gcc -g -O0 -o inv2 inv2.c -lpthread

clean:
	rm -rf *.o inv1  inv2
