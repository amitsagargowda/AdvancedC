all: ioctl1 ioctl2

ioctl1: ioctl1.c
	gcc -g -O0 -o ioctl1 ioctl1.c -lpthread -lrt

ioctl2: ioctl2.c
	gcc -g -O0 -o ioctl2 ioctl2.c -lpthread -lrt

clean:
	rm -rf *.o ioctl1 ioctl2
