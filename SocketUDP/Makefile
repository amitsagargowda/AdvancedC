all: udpserv1 udpclient1

udpserv1: udpserv1.c
	gcc -g -O0 -o udpserv1 udpserv1.c -lpthread

udpclient1: udpclient1.c
	gcc -g -O0 -o udpclient1 udpclient1.c -lpthread

clean:
	rm -rf *.o udpserv1 udpclient1
