#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
	int outfd;
	int fd;
	char buf[1024];
	int n;
	char *path1="temp.txt";
	char* path2="tmpfifo";
	outfd=open(path1,O_WRONLY|O_CREAT|O_TRUNC);
	if(outfd==-1){
		perror("open error");
		exit(EXIT_FAILURE);
	}

	fd=open(path2,O_RDONLY);
	if(fd==-1){
		perror("open fifo error");
		exit(EXIT_FAILURE);
	}

	while((n=read(fd,buf,1024))){
		write(outfd,buf,n);
	}

	close(outfd);
	close(fd);
	printf("read success\n");

	return 0;
	
}
