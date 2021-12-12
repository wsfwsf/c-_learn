#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
	int fd;
	fd = open("1.txt",O_RDWR);//tttttt
	struct stat buf;
	memset(&buf,0,sizeof(buf));
	fstat(fd,&buf);
	printf("total size:%d bytes\n",(int)buf.st_size);
	return 0;
}
