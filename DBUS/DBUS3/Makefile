all: dbus-ping-listen dbus-ping-send

dbus-ping-listen: dbus-ping-listen.c
	gcc -o $@ $< `pkg-config --cflags --libs dbus-1 dbus-glib-1`

dbus-ping-send: dbus-ping-send.c
	gcc -o $@ $< `pkg-config --cflags --libs dbus-1 dbus-glib-1`

clean:
	rm -rf  dbus-ping-listen dbus-ping-send
