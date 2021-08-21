all: dbus-signal

dbus-signal: dbus-signal.c
	gcc -o $@ $< `pkg-config --cflags --libs dbus-1 dbus-glib-1`

clean:
	rm -rf  dbus-signal
