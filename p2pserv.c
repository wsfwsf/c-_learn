#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define ERR_EXIT(m) \
        do {perror(m);exit(EXIT_FAILURE);}while(0)

void handler(int sig){
	exit(EXIT_SUCCESS);
}

int main(){
	int listenfd;
	if((listenfd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int opt =1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&opt,sizeof(opt)))
		ERR_EXIT("setsockopt");
	
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("bind");

	if(listen(listenfd,SOMAXCONN)<0)
		ERR_EXIT("listen");

	struct sockaddr_in peeraddr;
	socklen_t peerlen=sizeof(peeraddr);
	int connfd;
	if((connfd=accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
		ERR_EXIT("accept");

	printf("ip=%s,port=%d\n",inet_ntoa(peeraddr.sin_addr),peeraddr.sin_port);
	//fflush(stdout);

	pid_t pid;
	pid=fork();
	if(pid<0) ERR_EXIT("fork");
	else if(pid==0){
		char sendbuf[1024]={0};
		while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
			write(connfd,sendbuf,strlen(sendbuf));
			memset(sendbuf,0,sizeof(sendbuf));
		}
		exit(EXIT_SUCCESS);
	}else{
		signal(SIGUSR1,handler);
		char recvbuf[1024];
		int ret;
		while(1){
			memset(recvbuf,0,1024);
			ret=read(connfd,recvbuf,1024);
			if(ret==-1) ERR_EXIT("read");
			else if(ret==0){
				printf("perr close\n");
				break;
			}
			fputs(recvbuf,stdout);
		}
		kill(pid,SIGUSR1);
		exit(EXIT_SUCCESS);
	}
	close(listenfd);
	close(connfd);
	return 0;
}
