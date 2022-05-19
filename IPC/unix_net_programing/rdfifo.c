#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd;
	fd=open("myfifo",O_RDONLY);
	char recvbuf[64]={0};
	while(read(fd,recvbuf,sizeof(recvbuf))!=0){
		fputs(recvbuf,stdout);
		memset(recvbuf,0,sizeof(recvbuf));
	}
	return 0;
}
	
