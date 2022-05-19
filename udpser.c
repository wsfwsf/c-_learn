#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define ERR_EXIT(m) \
	do { perror(m); exit(EXIT_FAILURE);} while(0)

void echo_serv(int sock){

	char recvbuf[1024]={0};
	struct sockaddr_in peeraddr;
	socklen_t peerlen;
	int n;
	while(1){
		peerlen=sizeof(peeraddr);
		n=recvfrom(sock,recvbuf,sizeof(recvbuf),0,(struct sockaddr*)&peeraddr,&peerlen);
		if(n==-1){ 
			if(errno=EINTR) continue;
			ERR_EXIT("recvfrom");
		}
		else if(n>0){
			fputs(recvbuf,stdout);
			sendto(sock,recvbuf,n,0,(struct sockaddr*)&peeraddr,peerlen);
		}	
		memset(recvbuf,0,sizeof(recvbuf));
	}
	close(sock);
}

int main(){
	int sock;
	if((sock=socket(PF_INET,SOCK_DGRAM,0))<0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("bind");

	echo_serv(sock);

	return 0;
}
