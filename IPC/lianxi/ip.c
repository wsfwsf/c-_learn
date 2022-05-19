#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main(){
	char *addr="127.0.0.1";
	int ret;
	struct in_addr add;
	memset(&add,0,sizeof(add));
	if((ret=inet_aton(addr,&add))<0){
		printf("inet_aton\n");
		return -1;
	}
	printf("s_addr:%d\n",add.s_addr);
	return 0;
}
