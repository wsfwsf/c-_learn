#include <pthread.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>

int main(){
	mqd_t mq;
	mq=mq_open("/abc",O_CREAT|O_EXCL,0666,NULL);
	if(mq==(mqd_t)-1) printf("error!\n");
	else printf("success!\n");
	
	return 0;
}
