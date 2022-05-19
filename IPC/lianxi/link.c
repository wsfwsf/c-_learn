#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	link("1.txt","2.txt");

	struct stat buf;
	lstat("2.txt",&buf);
	printf("2.txt inode num:%lu\n",buf.st_ino);
	if(buf.st_mode&S_IFLNK)
		printf("2.txt is a link\n");
	else 
		printf("2.txt is not a link\n");
	lstat("1.txt",&buf);
        printf("1.txt inode num:%lu\n",buf.st_ino);
	if(buf.st_mode&S_IFREG)
		printf("1.txt is a regular file\n");
	else
		printf("1.txt is not a regular file\n");

	
	return 0;
}
