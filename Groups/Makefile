all: grp1 grp2 grp3

grp1: grp1.c
	gcc -g -O0 -o grp1 grp1.c -lpthread -lrt

grp2: grp2.c
	gcc -g -O0 -o grp2 grp2.c -lpthread -lrt
	sudo chown root grp2
	sudo chmod ug+s grp2

grp3: grp3.c
	gcc -g -O0 -o grp3 grp3.c -lpthread -lrt

clean:
	rm -rf *.o grp1 grp2 grp3
