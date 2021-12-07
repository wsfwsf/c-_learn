#include"apue.h"
#include<fcntl.h>

char buf1[]="abcdefghi";
char buf2[]="ABCDEFGHI";

int main(void){
	int fd;
	if((fd=creat("file.hole",FILE_MODE))<0)
		err_sys("creat error");
	if(write(fd,buf1,10)!=10)
		err_sys("buf1 write error");
	if(lseek(fd,16384,SEEK_SET)==-1)
		err_sys("lseek eror");
	if(write(fd,buf2,10)!=10)
		err_sys("buf2 write error");
	ssize_t n;
	char buf[1024];
	memset(&buf,0,sizeof(buf));
	fd=open("1.c",O_RDWR);
	if((n=read(fd,buf,1024))==-1)
		err_sys("read error");
	printf("read:%s\n",buf);
	exit(0);
}
