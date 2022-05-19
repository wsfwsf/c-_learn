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
#include <sys/wait.h>

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

ssize_t recv_peek(int sockfd,void* buf,size_t len){
	int ret;
	while(1){
		ret=recv(sockfd,buf,len,MSG_PEEK);
		if(ret==-1&&errno==EINTR)
			continue;
		return ret;
	}
}

ssize_t readline(int sockfd,void* buf,size_t maxline){
	int ret;
	int nread;
	char *bufp=buf;
	int nleft=maxline;
	while(1){
		ret=recv_peek(sockfd,bufp,nleft);
		if(ret <= 0) return ret;
		nread = ret;
		int i;

		for(i=0;i<nread;i++){
			if(bufp[i]=='\n'){
				ret=readn(sockfd,bufp,i+1);
				if(ret!=i+1) exit(EXIT_FAILURE);
				
				return ret;
			}
		}
		
		if(nread>nleft) exit(EXIT_FAILURE);

		nleft -= nread;
		ret = readn(sockfd,bufp,nread);
		if(ret!=nread) exit(EXIT_FAILURE);

		bufp += nread;
	}
	return -1;
}

void echo_serv(int connfd){
        char recvbuf[1024];
	int ret;
	while(1){
        	memset(recvbuf,0,sizeof(recvbuf));
                ret=readline(connfd,recvbuf,sizeof(recvbuf));
		if(ret==-1){
			ERR_EXIT("readline");
		}else if(ret==0){
			printf("client close\n");
			break;
		}
                fputs(recvbuf,stdout);
		sleep(4);
                writen(connfd,recvbuf,ret);
        }

}

void handler_chld(int sig){
	/*wait(NULL);*/
	waitpid(-1,NULL,WNOHANG);
}

void handler_pipe(int sig){
	printf("recv a sig=%d\n",sig);
}

int main(){
	/*signal(SIGCHLD,SIG_IGN);*/
	signal(SIGCHLD,handler_chld);
	signal(SIGPIPE,handler_pipe);
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

	int client[FD_SETSIZE];
	int i;
	for(i=0;i<FD_SETSIZE;i++){
		client[i]=-1;
	}

	int ret;
	int nready;
	int maxfd=listenfd;
	int maxi=0;

	fd_set rset;
	fd_set allset;
	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(listenfd,&allset);
	while(1){
		rset=allset;
		nready=select(maxfd+1,&rset,NULL,NULL,NULL);
		if(nready==-1){
			if(errno==EINTR) continue;
			ERR_EXIT("select");
		}else if(nready==0) continue;

		if(FD_ISSET(listenfd,&rset)){
			peerlen=sizeof(peeraddr);
			connfd = accept(listenfd,(struct sockaddr*)&servaddr,&peerlen);
			if(connfd ==-1) ERR_EXIT("accept");

			for(i=0;i<FD_SETSIZE;i++){
				if(client[i]==-1){
					client[i]=connfd;
					if(i>maxi) maxi=i;
					break;
				}
			}

			if(i==FD_SETSIZE){
				fprintf(stderr,"too many client\n");
				exit(EXIT_FAILURE);
			}
			printf("ip=%s,port=%d\n",inet_ntoa(peeraddr.sin_addr),peeraddr.sin_port);
			FD_SET(connfd,&allset);
			if(connfd > maxfd) maxfd=connfd;
			if(--nready<=0) continue;
		}
		
		for(i=0;i<maxi+1;i++){
			connfd = client[i];
			if(connfd == -1) continue;
			if(FD_ISSET(connfd,&rset)){
				char recvbuf[1024]={0};
				ret= readline(connfd,recvbuf,sizeof(recvbuf));
				if(ret == -1) ERR_EXIT("readline");
				if(ret == 0){
					printf("client close\n");
					client[i]=-1;
					FD_CLR(connfd,&allset);
				}
				fputs(recvbuf,stdout);
				sleep(4);
				writen(connfd,recvbuf,strlen(recvbuf));

				if(--nready<=0) break;
			}
		}
	}
	return 0;
}
