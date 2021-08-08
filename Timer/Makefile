all: timer1 timer2 timer3 timer4

timer1: timer1.c
	gcc -g -O0 -o timer1 timer1.c -lpthread -lrt

timer2: timer2.c
	gcc -g -O0 -o timer2 timer2.c -lpthread -lrt

timer3: timer3.c
	gcc -g -O0 -o timer3 timer3.c -lpthread -lrt

timer4: timer4.c
	gcc -g -O0 -o timer4 timer4.c -lpthread -lrt

clean:
	rm -rf *.o timer1 timer2 timer3 timer4
