/** @file
 *
 * minimal example for fat filesystem using high-level API
 *
 * Compile with:
 *
 *     gcc -Wall fuse1.c `pkg-config fuse3 --cflags --libs` -o fuse1
 *
 * ## Source code ##
 * \include fat1.c
 */


#define FUSE_USE_VERSION 31

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

FILE *fp=NULL;
int startOfRoot=0;

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

typedef struct {
    unsigned char *fileName;
	unsigned char *extension;
    int attribute;
    int startingCluster;
    int fileSize;
    int creationTime;
    int fineTime;
    int creationDate;
} entry;

unsigned char* seekSData(FILE *fp, int offset, int bytes);
int seekIData(FILE *fp, int offset, int bytes);

//Return the string value of the data found at the offset location
unsigned char* seekSData(FILE *fp, int offset, int bytes) {
    unsigned char* buff = malloc(sizeof(unsigned char)*(bytes+2));
	memset(buff,0x0,sizeof(unsigned char)*(bytes+2));
    fseek(fp, offset, SEEK_SET);
    fread(buff, 1, bytes, fp);
    rewind(fp);
    return buff;
}

//Return the integer value of hex data found at the offset location
int seekIData(FILE *fp, int offset, int bytes) {
    unsigned char* buff = seekSData(fp, offset, bytes);
    int i, value = 0;
    for (i = 0; i < bytes; i++) {
        value += (unsigned int)(unsigned char)buff[i] << 8*i;
    }
    return value;
}

//Iterates through files in root directory and prints their information
void scanRootEntries(void *buf,fuse_fill_dir_t filler) {
    int totalRoot = seekIData(fp, 0x11, 2);
    int i;
    for (i = 0; i < totalRoot; i++) {
        int index = startOfRoot+i*32;
        int check = seekIData(fp, index, 1);
        if (check == 0) break;
        else if (check == 229) continue;
		
        entry newEntry = {
            seekSData(fp, index, 8),
			seekSData(fp, index+8,3),
            seekIData(fp, index+11, 1),
            seekIData(fp, index+26, 2),
            seekIData(fp, index+28, 4),
            seekIData(fp, index+14, 2),
            seekIData(fp, index+13, 1),
            seekIData(fp, index+16, 2)
        };
		
		for (size_t i = 0; i < strlen(newEntry.fileName); ++i) {
			if(newEntry.fileName[i] == ' '){
				newEntry.fileName[i]=0;
				continue;
			}
			newEntry.fileName[i] = tolower((unsigned char)newEntry.fileName[i]);
		}
		
		for (size_t i = 0; i < strlen(newEntry.extension); ++i) {
			if(newEntry.extension[i] == ' '){
				newEntry.extension[i]=0;
				continue;
			}
			newEntry.extension[i] = tolower((unsigned char)newEntry.extension[i]);
		}
		
        if (newEntry.attribute == 0 && newEntry.startingCluster <= 0) continue; //If not a file/directory
        else if (CHECK_BIT(newEntry.attribute, 3)) continue; //If volume label
		struct stat stbuf;
		char buffer[16];		
		if(CHECK_BIT(newEntry.attribute, 4)){
			stbuf.st_mode = S_IFDIR | 0755;
			stbuf.st_nlink = 2;
			sprintf(buffer,"%s",newEntry.fileName);			
		}else{
			stbuf.st_mode = S_IFREG | 0755;
			stbuf.st_nlink = 1;
			stbuf.st_size = newEntry.fileSize;
			sprintf(buffer,"%s.%s",newEntry.fileName,newEntry.extension);
		}
		filler(buf,buffer,&stbuf,0,0);
    }
}

//Iterates through files in root directory and prints their information
void findstbuf(const char* path,struct stat *stbuf) {
    int totalRoot = seekIData(fp, 0x11, 2);
    int i;
    for (i = 0; i < totalRoot; i++) {
        int index = startOfRoot+i*32;
        int check = seekIData(fp, index, 1);
        if (check == 0) break;
        else if (check == 229) continue;
		
        entry newEntry = {
            seekSData(fp, index, 8),
			seekSData(fp, index+8,3),
            seekIData(fp, index+11, 1),
            seekIData(fp, index+26, 2),
            seekIData(fp, index+28, 4),
            seekIData(fp, index+14, 2),
            seekIData(fp, index+13, 1),
            seekIData(fp, index+16, 2)
        };
		
		for (size_t i = 0; i < strlen(newEntry.fileName); ++i) {
			if(newEntry.fileName[i] == ' '){
				newEntry.fileName[i]=0;
				continue;
			}
			newEntry.fileName[i] = tolower((unsigned char)newEntry.fileName[i]);
		}
		
		for (size_t i = 0; i < strlen(newEntry.extension); ++i) {
			if(newEntry.extension[i] == ' '){
				newEntry.extension[i]=0;
				continue;
			}
			newEntry.extension[i] = tolower((unsigned char)newEntry.extension[i]);
		}
		
        if (newEntry.attribute == 0 && newEntry.startingCluster <= 0) continue; //If not a file/directory
        else if (CHECK_BIT(newEntry.attribute, 3)) continue; //If volume label		
		char buffer[16];
		if(CHECK_BIT(newEntry.attribute, 4)){
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
			
			sprintf(buffer,"/%s",newEntry.fileName);			
		}else{
			stbuf->st_mode = S_IFREG | 0755;
			stbuf->st_nlink = 1;
			stbuf->st_size = newEntry.fileSize;
			sprintf(buffer,"/%s.%s",newEntry.fileName,newEntry.extension);
		}
		if(strcmp(path,buffer) == 0){
			    return;
		}
    }
}


static int fat_getattr(const char *path, struct stat *stbuf,
				struct fuse_file_info *fi)
{
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));
    if(strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else {
		findstbuf(path,stbuf);
    }
	
    return res;
}

static int fat_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi,enum fuse_readdir_flags flags)
{
    (void) offset;
    (void) fi;

    if(strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0,0);
    filler(buf, "..", NULL, 0,0);
	scanRootEntries(buf,filler);

    return 0;
}

static struct fuse_operations fat_oper = {
    .getattr	= fat_getattr,
    .readdir	= fat_readdir,
};

int main(int argc, char *argv[])
{
    int bytesPerSect  = 0;
    int reserved      = 0;
    int numFAT        = 0;
    int sectPerFAT    = 0;
	
    fp = fopen("test.img", "rb");
    if (fp == NULL) {
        printf("Could not read disk! Exiting program..\n");
        exit(0);
    }
	
    bytesPerSect  = seekIData(fp, 0x0B, 2);
    reserved      = seekIData(fp, 0x0E, 2);
    numFAT        = seekIData(fp, 0x10, 1);
    sectPerFAT    = seekIData(fp, 0x16, 2);
    startOfRoot   = bytesPerSect*(reserved + numFAT*sectPerFAT);
	
    return fuse_main(argc, argv, &fat_oper,NULL);
}
