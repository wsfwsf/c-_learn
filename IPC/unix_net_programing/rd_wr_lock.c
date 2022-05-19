#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_rwlock_t rwlock;

int num;

void* Read(void* arg){
	int n= (int)arg;
	while(num<50){
		pthread_rwlock_rdlock(&rwlock);
		printf("thread %d read %d\n",n,num);
		pthread_rwlock_unlock(&rwlock);
		sleep(rand()%3);
	}

	return NULL;
}

void* Write(void* arg){
	int n=(int)arg;
	while(num<50){
		pthread_rwlock_wrlock(&rwlock);
		num++;
		printf("thread %d add num from %d to %d\n",n,num-1,num);
		pthread_rwlock_unlock(&rwlock);
		sleep(rand()%3);
	}

	return NULL;
}

int main(){
	num=0;
	pthread_rwlock_init(&rwlock,NULL);

	pthread_t tid[5];

	for(int i=0;i<5;i++){
		if(i<3){
			pthread_create(&tid[i],NULL,Write,(void*)i);
		}else{
			pthread_create(&tid[i],NULL,Read,(void*)i);
		}
	}

	for(int i=0;i<5;i++){
		pthread_join(tid[i],NULL);
		printf("pthread %d exit.\n",i);
	}
	pthread_rwlock_destroy(&rwlock);
	return 0;
}
