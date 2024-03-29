#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXNITEMS 1000000
#define MAXNTHREADS   100

int nitems;

struct {
	pthread_mutex_t mutex;
	int buff[MAXNITEMS];
	int nput;
	int nval;
}shared={
	PTHREAD_MUTEX_INITIALIZER
};

void* produce(void*);
void* consume(void*);

int main(int argc,char* argv[]){
	int i,nthreads,count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS],tid_consume;
	
	if(argc !=3)
		perror("Usage: prodcons2 <#items> <#threads>");
	nitems=atoi(argv[1])>MAXNITEMS?MAXNITEMS:atoi(argv[1]);
	nthreads=atoi(argv[2])>MAXNTHREADS?MAXNTHREADS:atoi(argv[2]);

	for(i=0;i<nthreads;i++){
		count[i]++;
		pthread_create(&tid_produce[i],NULL,produce,&count[i]);
	}

	for(i=0;i<nthreads;i++){
		pthread_join(tid_produce[i],NULL);
		printf("count[%d]=%d\n",i,count[i]);
	}

	pthread_create(&tid_consume,NULL,consume,NULL);
	pthread_join(tid_consume,NULL);

	return 0;
}

void* produce(void* arg){
	for(;;){
		pthread_mutex_lock(&shared.mutex);
		if(shared.nput >= nitems){
			pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}
		shared.buff[shared.nput]=shared.nval;
		shared.nput++;
		shared.nval++;
		pthread_mutex_unlock(&shared.mutex);
		*((int*)arg) += 1;
	}
}

void* consume(void* arg){
	int i;
	for(i=0;i<nitems;i++){
		if(shared.buff[i]!=i)
			printf("buff[%d]=%d\n",i,shared.buff[i]);
	}
	
	return NULL;
}
