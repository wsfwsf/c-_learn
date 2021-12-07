#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mqueue.h>
#include <stdio.h>

#define ERR_EXIT(m) \
        do {perror(m);exit(EXIT_FAILURE);}while(0)


int main(){
	mqd_t mqid;
	mqid=mq_open("/abc",O_CREAT | O_RDWR,0666,NULL);
	if(mqid==(mqd_t)-1)
		ERR_EXIT("mq_open");
	return 0;
}
