#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include <sys/socket.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
#define ERR_EXIT(m) \
	do {perror(m);exit(EXIT_FAILURE);}while(0)

typedef struct stu{
	char name[32];
	int age;
}STU;

int main(int argc,char* argv[]){
	int shmid;
	shmid=shmget(1234,0,0);
	if(shmid==-1)
		ERR_EXIT("shmget");
	STU* p;
	p=shmat(shmid,NULL,0);
	if(p==(void*)-1)
		ERR_EXIT("shmat");
	printf("name=%s,age=%d\n",p->name,p->age);
	memcpy(p,"quit",4);
	shmdt(p);
	return 0;
}
