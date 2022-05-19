#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
	int infd;
	int fd;
	char buf[1024];
	int n=0;
	char *path1="ls_test.c";
	char *path2="tmpfifo";
	infd=open(path1,O_RDONLY);
	if(infd==-1){
		perror("open error");
		exit(EXIT_FAILURE);
	}

	if(mkfifo(path2,0644)==-1){
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	fd=open(path2,O_WRONLY|O_CREAT);

	if(fd==-1){
		perror("open");
		exit(EXIT_FAILURE);
	}

	while((n=read(infd,buf,1024))){
		write(fd,buf,n);
	}

	close(infd);
	close(fd);
	printf("write success\n");
	return 0;
}
