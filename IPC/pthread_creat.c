#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


void* thread_routine(void* arg){
	int i;

	for(i=0;i<20;i++){
		printf("B");
		fflush(stdout);
		usleep(20);
	}
	printf("\n");
	pthread_exit("success\n");
}

int main(){
	pthread_t tid;
	int ret;

	if((ret=pthread_create(&tid,NULL,thread_routine,NULL))!=0){
		fprintf(stderr,"pthread_create:%s\n",strerror(ret));
		exit(EXIT_FAILURE);
	}

	int i;
	for(i=0;i<20;i++){
		printf("A");
		fflush(stdout);
		usleep(20);
	}
	void** rval_ptr;
	pthread_join(tid,rval_ptr);
	printf("return with: %s",(char*)*rval_ptr);
	return 0;
}
