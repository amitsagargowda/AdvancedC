all: fat1

fat1: fat1.c
	gcc -g -O0 fat1.c `pkg-config fuse3 --cflags --libs` -o fat1 -lm

clean:
	rm -rf fat1
