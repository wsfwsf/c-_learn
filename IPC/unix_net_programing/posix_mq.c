#include <pthread.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
	mqd_t mq;
	mqd_t ret;
	mq=mq_open("/abc",O_CREAT|O_RDWR,0666,NULL);

	if(mq==(mqd_t)-1) perror("create error!\n");
	else printf("success!\n");

	struct mq_attr attr;
	ret=mq_getattr(mq,&attr);
	if(ret==(mqd_t)-1) perror("mq_getattr error\n");
	else printf("mq_getattr success\n");
	
	printf("mq_flags:%ld\n",attr.mq_flags);
	printf("mq_maxmsg:%ld\n",attr.mq_maxmsg);
	printf("mq_msgsize:%ld\n",attr.mq_msgsize);
	printf("ma_curmsgs:%ld\n",attr.mq_curmsgs);

	attr.mq_maxmsg=(long) 64;
	
	ret=mq_setattr(mq,&attr,NULL);
	printf("mq_flags:%ld\n",attr.mq_flags);
	printf("mq_maxmsg:%ld\n",attr.mq_maxmsg);
	printf("mq_msgsize:%ld\n",attr.mq_msgsize);
	printf("ma_curmsgs:%ld\n",attr.mq_curmsgs);
	if(ret==(mqd_t)-1) perror("mq_setattr error\n");
	else printf("mq_setattr success\n");
	
	pid_t pid;
	int count=0;
	pid=fork();
	if(pid<0) perror("fork error");
	else if(pid==0){
		sleep(1);
		char recvbuf[attr.mq_msgsize];
		int priority=0;
		ret=mq_receive(mq,recvbuf,sizeof(recvbuf),&priority);
		if(ret==(mqd_t)-1) perror("recv error\n");
		printf("recv from mq:%s,priority is %d\n",recvbuf,priority);
	}else{	
		char message[32]="Hello posix mq!\n";
		mq_send(mq,message,sizeof(message),1);
		waitpid(pid,NULL,WNOHANG);
		ret=mq_unlink("/abc");
		if(ret==(mqd_t)-1) perror("mq_unlink\n");
		else{
			printf("mq_unlink success\n");
		}
	}
	return 0;
}
