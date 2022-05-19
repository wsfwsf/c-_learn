#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;

int num;

void* consumer(void* arg){
	while(1){
		if(num!=0){
			pthread_mutex_lock(&mutex);
			num--;
			printf("consume one,and have:%d\n",num);
			pthread_mutex_unlock(&mutex);
		}else{
			printf("have no product!\n");
		}
		sleep(rand()%3);
	}
}

int main(){
	num=0;
	pthread_mutex_init(&mutex,NULL);
	pthread_t tid;
	pthread_create(&tid,NULL,consumer,NULL);
	
	while(1){
		int n=rand()%2;
		pthread_mutex_lock(&mutex);
		while(n--){
                	num += 1;
                	printf("produce one,and have:%d\n",num);
		}
                pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}	
	return 0;
}
