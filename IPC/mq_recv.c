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
	if((mqid=mq_open("/abc",O_RDWR))==(mqd_t)-1)
		ERR_EXIT("mq_open");

	printf("mq_open success\n");

	struct mq_attr attr;
	mq_getattr(mqid,&attr);

	char msg[32]={0};
	unsigned msg_prio;

	if(mq_receive(mqid,msg,(size_t)attr.mq_msgsize,&msg_prio)<0)
		ERR_EXIT("mq_receive");
	
	printf("receive:%s,prio=%u\n",msg,msg_prio);

	mq_close(mqid);
	
	return 0;
}
