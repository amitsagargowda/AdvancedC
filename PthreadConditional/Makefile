all: pcond1 pcond2 pcond3

pcond1: pcond1.c
	gcc -g -O0 -o pcond1 pcond1.c -lpthread

pcond2: pcond2.c
	gcc -g -O0 -o pcond2 pcond2.c -lpthread

pcond3: pcond3.c
	gcc -g -O0 -o pcond3 pcond3.c -lpthread

clean:
	rm -rf *.o pcond1 pcond2 pcond3
