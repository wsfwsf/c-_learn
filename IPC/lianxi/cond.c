#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int x=0;

void* waitfortrue(void* args){
	int res;
	res=pthread_mutex_lock(&mutex);
	if(res!=0){
		printf("waitfortrue failed\n");
		return NULL;
	}

	printf("-----wait x to be 10\n");

	if(pthread_cond_wait(&cond,&mutex)==0){
		printf("x=%d\n",x);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void* donefortrue(void* args){
	int res;
	while(x!=10){
		res=pthread_mutex_lock(&mutex);
		if(res==0){
			x++;
			printf("donefortrue:x=%d\n",x);
			sleep(1);
			pthread_mutex_unlock(&mutex);
		}
	}
	res=pthread_cond_signal(&cond);
	if(res!=0){
		printf("failed to pthread_cond_signal\n");
	}
	return NULL;
}

int main(){
	int res;
	pthread_t thread1,thread2;
	res=pthread_create(&thread1,NULL,(void*)waitfortrue,NULL);
	sleep(1);
	res=pthread_create(&thread2,NULL,(void*)donefortrue,NULL);
	res=pthread_join(thread1,NULL);
	res=pthread_join(thread2,NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	return 0;
}
