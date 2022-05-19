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
#include <arpa/inet.h>

#define ERR_EXIT(m) \
	do { perror(m); exit(EXIT_FAILURE);} while(0)

void echo_cli(int sock){
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
		sendto(sock,sendbuf,strlen(sendbuf),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		recvfrom(sock,recvbuf,sizeof(recvbuf),0,NULL,NULL);
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(recvbuf));
		memset(recvbuf,0,sizeof(sendbuf));
	}
	close(sock);

}

int main(){
	int sock;

	if((sock=socket(PF_INET,SOCK_DGRAM,0))<0)
		ERR_EXIT("socket");
	
	echo_cli(sock);

	return 0;
}
