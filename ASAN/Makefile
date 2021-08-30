all: asan1 asan1_asan asan2 asan2_asan asan3 asan3_asan asan4 asan4_asan asan5 asan5_asan

asan1: asan1.c
	gcc -g -O0 -o asan1 asan1.c -lpthread

asan1_asan: asan1.c
	gcc -g -O0 -o asan1_asan asan1.c -g -fsanitize=address

asan2: asan2.c
	gcc -g -O0 -o asan2 asan2.c -lpthread

asan2_asan: asan2.c
	gcc -g -O0 -o asan2_asan asan2.c -g -fsanitize=address

asan3: asan3.c
	gcc -g -O0 -o asan3 asan3.c -lpthread

asan3_asan: asan3.c
	gcc -g -O0 -o asan3_asan asan3.c -g -fsanitize=address

asan4: asan4.c
	gcc -g -O0 -o asan4 asan4.c -lpthread

asan4_asan: asan4.c
	gcc -g -O0 -o asan4_asan asan4.c -g -fsanitize=address

asan5: asan5.c
	gcc -g -O0 -o asan5 asan5.c -lpthread

asan5_asan: asan5.c
	gcc -g -O0 -o asan5_asan asan5.c -g -fsanitize=address


clean:
	rm -rf *.o asan1 asan1_asan asan2 asan2_asan asan3 asan3_asan asan4 asan4_asan asan5 asan5_asan
