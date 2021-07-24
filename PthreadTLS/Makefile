all: tls1 tls2

tls1: tls1.c
	gcc -g -O0 -o tls1 tls1.c -lpthread

tls2: tls2.c
	gcc -g -O0 -o tls2 tls2.c -lpthread

clean:
	rm -rf *.o tls1 tls2
