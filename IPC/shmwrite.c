#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define TEXT_SZ 2048
 
struct shared_use_st
{
    int written; // 作为一个标志，非0：表示可读，0：表示可写
    char text[TEXT_SZ]; // 记录写入 和 读取 的文本
};

int main(int argc,char* argv[]){
	void *shm=NULL;
	struct shared_use_st* shared=NULL;
	char buff[TEXT_SZ]={0};
	int shmid;

	shmid=shmget(1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
	if(shmid==-1){
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shm=shmat(shmid,NULL,0);

	if(shm==(void*)-1){
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Memory attchde at %x\n",(int)shm);

	shared=(struct shared_use_st*)shm;

	while(1){
		while(shared->written==1){
			sleep(1);
			printf("Waiting...\n");
		}
		printf("Enter some Text:\n");
		fgets(buff,TEXT_SZ,stdin);
		strncpy(shared->text,buff,TEXT_SZ);

		shared->written =1;

		if(strncpy(buff,"end",3)==0) break;
	}

	if(shmdt(shm)==-1){
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	sleep(2);
	return 0;
}
