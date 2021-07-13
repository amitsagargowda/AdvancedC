all: add_main

add_main: add_main.o add.o
	gcc -g $^ -o $@

add_main.o: add_main.c
	gcc -g -c  $^

add.o: add.s
	gcc -g -c $^

clean:
	rm -rf *.o add_main
