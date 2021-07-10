all: myfilesys

myfilesys: myfilesys.c
	gcc -Wall myfilesys.c `pkg-config fuse3 --cflags --libs` -o myfilesys


clean:
	rm -rf myfilesys
