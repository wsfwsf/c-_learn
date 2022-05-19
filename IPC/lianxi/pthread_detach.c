#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void* thr_fn(void* arg){
	return (void*)3;
}

int main(){
	pthread_t tid;
	void* ret;
	pthread_create(&tid,NULL,thr_fn,NULL);
	pthread_detach(tid);

	int err;
	pthread_detach(tid);
	while(1){
		err=pthread_join(tid,&ret);
		if(err!=0){
			fprintf(stderr,"thread %s\n",strerror(err));
		}else{
			fprintf(stderr,"thread exit code %d\n",(int)ret);
		}
		sleep(1);
	}

	return 0;
}
