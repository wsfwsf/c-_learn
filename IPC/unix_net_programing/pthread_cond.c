#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define nthread 3

pthread_mutex_t mutex;
pthread_cond_t cond;
int num;

void* produce(void* arg){
	int n=(int)arg;
	while(1){
		pthread_mutex_lock(&mutex);
		num++;
		printf("produce_thread %d produce one and have:%d\n",n,num);		

		if(num==1) pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}

	return NULL;
}

void* consume(void* arg){
	int n=(int)arg;
	while(1){
		pthread_mutex_lock(&mutex);
		while(num==0){
			printf("consume_thread %d waiting...\n",n);		
			pthread_cond_wait(&cond,&mutex);
			printf("consume_thread %d wake up,and consume one,have %d\n",n,num-1);
		}
		num--;
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	return NULL;
}

int main(){
	int i;
	num=0;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);

	pthread_t producer[nthread];
	pthread_t consumer[nthread];

	for(i=0;i<nthread;i++){
		pthread_create(&producer[i],NULL,produce,(void*)i);
	}
	for(i=0;i<nthread;i++){
		pthread_create(&consumer[i],NULL,consume,(void*)i);
	}

	for(i=0;i<nthread;i++){
		pthread_join(producer[i],NULL);
	}
	for(i=0;i<nthread;i++){
		pthread_join(consumer[i],NULL);
	}
	return 0;
}
