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

int main(){
	int sock;
	if((sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("connect");

	char sendbuf[1024]={0};
	char recvbuf[1024]={0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL){
		writen(sock,sendbuf,sizeof(sendbuf));
		readn(sock,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		memset(recvbuf,0,sizeof(recvbuf));
		memset(sendbuf,0,sizeof(sendbuf));
	}

	close(sock);

	return 0;
}
