all: tsan1 tsan1_tsan tsan2 tsan2 tsan2_tsan

tsan1: tsan1.c
	gcc -g -O0 -o tsan1 tsan1.c -lpthread

tsan1_tsan: tsan1.c
	gcc -g -O0 -o tsan1_tsan tsan1.c -g -fsanitize=thread

tsan2: tsan2.c
	gcc -g -O0 -o tsan2 tsan2.c -lpthread

tsan2_tsan: tsan2.c
	gcc -g -O0 -o tsan2_tsan tsan2.c -g -fsanitize=thread


clean:
	rm -rf *.o tsan1 tsan1_tsan tsan2 tsan2_tsan
