#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(){
	int fd;
	if(mkfifo("myfifo",0666)<0) perror("mkfifo");
	fd=open("myfifo",O_WRONLY);
	char recvbuf[64]={0};
	while(fgets(recvbuf,sizeof(recvbuf),stdin)!=NULL){
		write(fd,recvbuf,strlen(recvbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}
	unlink("myfifo");
	return 0;
}
	
