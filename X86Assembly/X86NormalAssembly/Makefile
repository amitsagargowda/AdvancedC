all: hello

hello: hello.o
	gcc -g $^ -o $@

hello.o: hello.s
	gcc -g -c  $^

clean:
	rm -rf *.o hello
