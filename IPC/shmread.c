#include <stddef.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TEXT_SZ 2048

struct shared_use_st{
	int written;
	char text[TEXT_SZ];
};

int main(int argc,char* argv[]){
	void* shm=NULL;
	struct shared_use_st* shared;
	int shmid;

	shmid=shmget(1234,sizeof(struct shared_use_st),0666|IPC_CREAT);

	if(shmid==-1) {
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shm=shmat(shmid,0,0);
	if(shm==(void*)-1){
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("\nMemory attached at %x\n",(int)shm);

	shared =(struct shared_use_st*)shm;
	shared->written=0;
	while(1){
		if(shared->written==1){
			printf("You wrote:%s",shared->text);
			sleep(1);

			shared->written=0;
			if(strncmp(shared->text,"end",3)==0) break;
		}else{
			sleep(1);
		}
	}

	if(shmdt(shm)==-1){
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
