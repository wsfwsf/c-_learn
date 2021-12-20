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
#include<sys/wait.h>
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
	return ret; 
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
	printf("\tdelete semid\n");
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


int semid;

void print(char op_char){
	int pause_time;
	srand(getpid());
	for(int i=0;i<10;i++){
		sem_p(semid);
			printf("%c",op_char);
			fflush(stdout);
			pause_time=rand()%3;
			sleep(pause_time);
			printf("%c",op_char);
			fflush(stdout);
			pause_time=rand()%3;
		sem_v(semid);
			pause_time=rand()%2;
			sleep(pause_time);
	}
}

int main(int argc,char* argv[]){
	semid=sem_creat(IPC_PRIVATE);
	sem_setval(semid,0);
	pid_t pid;
	pid=fork();
	if(pid==-1)
		ERR_EXIT("fork");
	if(pid>0){
		sem_setval(semid,1);
		print('o');
		wait(NULL);
		sem_d(semid);
	}else{
		print('x');
	}
	return 0;
}
