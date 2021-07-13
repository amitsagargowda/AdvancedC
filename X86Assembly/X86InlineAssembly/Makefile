all: inline

inline: inline.o
	gcc -g $^ -o $@

inline.o: inline.c
	gcc -g -c  $^

clean:
	rm -rf *.o inline
