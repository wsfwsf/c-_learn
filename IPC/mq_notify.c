#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m) \
	do{perror(m);exit(EXIT_FAILURE);}while(0)

mqd_t mqid;

void handle_sigusr1(int sig){
	struct mq_attr attr;
	mq_getattr(mqid,&attr);
	char msg[32]={0};
        unsigned msg_prio;

        if(mq_receive(mqid,msg,(size_t)attr.mq_msgsize,&msg_prio)<0)
                ERR_EXIT("mq_receive");

        printf("receive:%s,prio=%u\n",msg,msg_prio);
}

int main(){
	if((mqid=mq_open("/abc",O_RDWR))==(mqd_t)-1)
		ERR_EXIT("mq_open");

	printf("mq_open success\n");

	signal(SIGUSR1,handle_sigusr1);

	struct mq_attr attr;
	mq_getattr(mqid,&attr);

	struct sigevent sigev;
	sigev.sigev_notify=SIGEV_SIGNAL;
	sigev.sigev_signo=SIGUSR1;

	mq_notify(mqid,&sigev);

	for(;;)
		pause();

	mq_close(mqid);
	
	return 0;
}
