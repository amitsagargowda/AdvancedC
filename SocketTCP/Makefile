all: tcpserv1 tcpclient1

tcpserv1: tcpserv1.c
	gcc -g -O0 -o tcpserv1 tcpserv1.c -lpthread

tcpclient1: tcpclient1.c
	gcc -g -O0 -o tcpclient1 tcpclient1.c -lpthread

clean:
	rm -rf *.o tcpserv1 tcpclient1
