#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERR_EXIT(m) \
	do{perror(m);exit(EXIT_FAILURE);}while(0)

int main(){
	mqd_t mqid;
	if((mqid=mq_open("/abc",O_CREAT|O_RDWR,0666,NULL))==(mqd_t)-1)
		ERR_EXIT("mq_open");

	printf("mq_open success\n");

	char msg[32]={0};
	strcpy(msg,"Hello c++");
	mq_send(mqid,msg,strlen(msg),0);
	return 0;
}
