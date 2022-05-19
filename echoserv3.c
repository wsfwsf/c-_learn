#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
        do {perror(m);exit(EXIT_FAILURE);}while(0)

ssize_t readn(int fd,void *buf,size_t count){
        size_t nleft=count;
        ssize_t nread;

        char* bufp=(char*)buf;
        while(nleft>0){
                if((nread=read(fd,buf,nleft))<0){
                        if(errno=EINTR) continue;
                        return -1;
                }else if(nread==0){
                        return count-nleft;
                }
                bufp += nread;
                nleft -= nread;
        }

        return count;
}

ssize_t writen(int fd,void *buf,size_t count){
        size_t nleft=count;
        ssize_t nwrite;

        char* bufp=(char*)buf;
        while(nleft>0){
                if((nwrite=write(fd,buf,nleft))<0){
                        if(errno=EINTR) continue;
			return -1;
                }else if(nwrite==0){
                        continue;
                }
                bufp += nwrite;
                nleft -= nwrite;
        }

        return count;
}


void do_service(int connfd){
	char recvbuf[1024];
        int ret;
        while(1){
        	memset(recvbuf,0,sizeof(recvbuf));
                ret=readn(connfd,recvbuf,sizeof(recvbuf));
		if(ret==0){
			printf("peer close\n");
			break;
		}else if(ret==-1){
			ERR_EXIT("read");
		}
                fputs(recvbuf,stdout);
                writen(connfd,recvbuf,sizeof(recvbuf));
        }

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
	pid_t pid;
	while(1){
		if((connfd=accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
			ERR_EXIT("accept");

		printf("ip=%s,port=%d\n",inet_ntoa(peeraddr.sin_addr),peeraddr.sin_port);
		//fflush(stdout);
		pid = fork();
		if(pid==-1) ERR_EXIT("fork");
		else if(pid==0){
			close(listenfd);
			do_service(connfd);
			exit(EXIT_SUCCESS);
		}else{
			close(connfd);
		}
	}

	return 0;
}
