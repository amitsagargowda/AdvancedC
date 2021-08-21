#
# Makefile
#

all: add-server add-client

%.o: %.c
	gcc -Wall -c $< `pkg-config --cflags dbus-1`

add-server: add-server.o
	gcc add-server.o -o add-server `pkg-config --libs dbus-1`

add-client: add-client.o
	gcc add-client.o -o add-client `pkg-config --libs dbus-1`

.PHONY: clean
clean:
	rm -rf *.o add-server add-client
