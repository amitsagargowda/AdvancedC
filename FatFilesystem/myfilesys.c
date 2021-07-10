#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


struct Directory_entry {
         char filename[24]; //up to 24 bytes
         int64_t creation_time;
         int64_t access_time;
         uint32_t file_length;
         int32_t start_block;
         uint32_t flag;
         uint32_t unused;
};

struct Superblock {
         uint32_t magicnum; //0x2345beef
         uint32_t total_blocks; //N (passed in as param)
         uint32_t fat_size; // = k = (N / 256)
         uint32_t block_size; // 1024
         uint32_t root_block; // k + 1
};

struct Fatblock {
         int32_t fatentry[256];
};

int32_t* fattable = NULL;
struct Directory_entry directoryblock[16]; // 1024/64=dirperblock
struct Superblock super;
int disk_fd;

int write_block(int fd, int blocknum, void* wblock){
        lseek(fd, blocknum*1024, SEEK_SET);
        return write(fd, wblock, 1024);
}

int read_block(int fd, int blocknum, void* rblock){
        lseek(fd, blocknum*1024, SEEK_SET);
        return read(fd, rblock, 1024);
}



//max path of 100
int find_path(const char *path, char *names[100]){
	char *token;
	char * temp;
	int count=0;
	strcpy(temp, path);
	while((token = strsep(&temp, "/")) != NULL){
		names[count] = token;
		count++;
	}
	return count;
}

//always starts at root directory
int find(const char* path, struct Directory_entry* de, int* offset){
	int i;
	int j;
	int start;
	void* rblock_rootdir = calloc(1024,1);
	int count;
	char * names[100];
	count = find_path(path, names);
	for(i = 0; i<count; i++){
		if(i == 0){
			read_block(disk_fd, super.root_block, (void*)directoryblock);
			//memcpy(directoryblock, rblock_rootdir, sizeof(directoryblock));
			//memcpy(de, rblock_rootdir, sizeof(struct Directory_entry));
			//assert(de->filename == ".");
		} else {
			read_block(disk_fd, de->start_block, (void*) directoryblock);
		}
		j = 0;
		//search 
		while(j<16){
			//found name
			if(!strcmp(directoryblock[j].filename, names[i])){
				//correct directory
				if(((directoryblock[j].flag & 1) == 1) && directoryblock[j].start_block != 0 ){
					start = de->start_block;
					memcpy(de, &directoryblock[j], sizeof(struct Directory_entry));
					break;
					//go to next level
				} else if ((directoryblock[j].flag & 1) == 0){
					//not a directory
					return -1;
				}

			}
			j++;
		}
		//checked all directory entries and couldnt find
		if(j == 16)
			return -1;
	}
	*offset = j;
	free(rblock_rootdir);
	return start;
}

static int my_getattr(const char *path, struct stat *stbuf){
	void* dir_block = calloc(sizeof(struct Directory_entry),1);
	struct Directory_entry *de = dir_block;
	int where;
	int offset;
	where = find(path, de,&offset);
	if(where < 0){
		return -1;
	} else {
		stbuf->st_ctime= de->creation_time;
		stbuf->st_atime= de->access_time;
		stbuf->st_dev = 0;
		stbuf->st_ino = 0;
		stbuf->st_nlink = 1;
		stbuf->st_mtime = de->access_time;
		//stbuf->st_birthtime = 0;
		stbuf->st_size = super.total_blocks * 1024;
		stbuf->st_blksize = super.block_size;
		stbuf->st_blocks = super.total_blocks * 2;
		stbuf->st_uid = getuid();
		stbuf->st_gid = getgid();
		stbuf->st_mode = 0040777;
	}
	free(dir_block);
	return 0;
}

static int my_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi){
	//Make new directory block and replace it
	int x = 0;
	int i=1;
	int blockIs = find(path, directoryblock, &x);
	if(blockIs<0){
		return -1;
	}

	read_block(disk_fd, blockIs, (void*)directoryblock);
	
	//file is only 1 block long
	if(directoryblock[x].file_length <= 1024){
		read_block(disk_fd, directoryblock[x].start_block, (void*)buf);
		return directoryblock[x].file_length;

	} else {
		int next;
		next = fattable[directoryblock[x].start_block];
		read_block(disk_fd, directoryblock[x].start_block, (void*)buf);
		//fattable[directoryblock[x].start_block] = 0;
		//directoryblock[x].start_block = 0;
		//goes through fat chain 
		while(next != -2){
			int oldnext = next;
			next = fattable[next];
			read_block(disk_fd, fattable[oldnext], (void*)buf + (i*1024) );
			i++;
		}
		//clears -2
		read_block(disk_fd, fattable[next], (void*)buf + (i*1024) );

	}

	
	return 0;

}


static struct fuse_operations my_oper = {
	.getattr	= my_getattr,
	.readdir	= my_readdir,
};

int main(int argc, char *argv[]){
	//char* file;
	//strcpy(file, argv[1]);
	
	if ((disk_fd = open("mydisk.img", O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0){
		perror("couldnt open file");	
		return -1;
	}
	return fuse_main(argc, argv, &my_oper, NULL);
}
