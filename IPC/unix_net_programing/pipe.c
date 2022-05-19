#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int fd[2];
	int ret;
	if((pipe(fd))<0) {
		perror("pipe");
	}

	int pid;
	char sendbuf[64]={0};
	char recvbuf[64]={0};
	pid=fork();
	if(pid<0) perror("fork");
	else if(pid==0){
		close(fd[1]);
		while(read(fd[0],recvbuf,sizeof(recvbuf))!=0){
			printf("%s",recvbuf);
			memset(recvbuf,0,sizeof(recvbuf));
		}
	}
	close(fd[0]);
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
		write(fd[1],sendbuf,strlen(sendbuf));
		memset(sendbuf,0,sizeof(recvbuf));
	}
	waitpid(pid,NULL,WNOHANG);

	return 0;
	
}
	
