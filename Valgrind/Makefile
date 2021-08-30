all: val1 val2 val3 val4 val5 val6 val7 val8 val9 val10

val1: val1.c
	gcc -g -O0 -o val1 val1.c

val2: val2.c
	gcc -g -O0 -o val2 val2.c

val3: val3.c
	gcc -g -O0 -o val3 val3.c

val4: val4.c
	gcc -g -O0 -o val4 val4.c

val5: val5.c
	gcc -g -O0 -o val5 val5.c

val6: val6.c
	gcc -g -O0 -o val6 val6.c -lpthread

val7: val7.c
	gcc -g -O0 -o val7 val7.c -lpthread

val8: val8.c
	gcc -g -O0 -o val8 val8.c -lpthread

val9: val9.c
	gcc -g -O0 -o val9 val9.c -lpthread

val10: val10.c
	gcc -g -O0 -o val10 val10.c 

clean:
	rm -rf *.o val1 val2 val3 val4 val5 cachegrind* callgrind* val6 val7 val8 val9 val10 massif*
