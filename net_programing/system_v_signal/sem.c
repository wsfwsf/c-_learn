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
#include<sys/sem.h>
#define ERR_EXIT(m) \
	do {perror(m);exit(EXIT_FAILURE);}while(0)

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int sem_creat(key_t key){
	int semid;
	semid = semget(key,1,IPC_CREAT | IPC_EXCL |0666);
	if(semid==-1)
		ERR_EXIT("semget");
	return semid;
}

int sem_open(key_t key){
	int semid;
	semid=semget(key,0,0);
	if(semid==-1)
		ERR_EXIT("semget");
	return semid;
}

int sem_setval(int semid,int val){
	union semun su;
	su.val=val;
	int ret;
	ret = semctl(semid,0,SETVAL,su);
	if(ret==-1)
		ERR_EXIT("semctl"); 
}

int sem_getval(int semid){
        int ret;
        ret = semctl(semid,0,GETVAL,0);
        if(ret==-1)
                ERR_EXIT("semctl");
	printf("create semid\n");
	return ret;
}

int sem_d(int semid){
	int ret;
	ret = semctl(semid,0,IPC_RMID,0);
	if(ret==-1)
		ERR_EXIT("semctl");
	printf("delete semid\n");
	return 0;
}

int sem_p(int semid){
	struct sembuf sb={0,-1,0};
	int ret;
	ret = semop(semid,&sb,1);
	if(ret==-1)
		ERR_EXIT("semop");
	return ret;
}

int sem_v(int semid){
        struct sembuf sb={0,+1,0};
        int ret;
        ret = semop(semid,&sb,1);
        if(ret==-1)
                ERR_EXIT("semop");
        return ret;
}


int main(int argc,char* argv[]){
	int semid;
	semid=sem_creat(1234);
	sleep(5);
	sem_d(semid);
	return 0;
}
