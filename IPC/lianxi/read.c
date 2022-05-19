#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define ERR_EXIT(m) \
	do{perror(m);exit(EXIT_FAILURE);} while(0)

int main(){
	int fd;
	fd=open("1.txt",O_CREAT|O_RDWR,0666);
	if(fd<0) ERR_EXIT("open");

	char buf[1024]={0};
	strcpy(buf,"Hello c++\n");
	write(fd,buf,strlen(buf));
	write(fd,buf,strlen(buf));

	memset(buf,0,strlen(buf));
	lseek(fd,0,SEEK_SET);
	if(read(fd,buf,sizeof(buf))<0) ERR_EXIT("read");

	printf("read:%s\n",buf);
	close(fd);	
	return 0;
	
}
