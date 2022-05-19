#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/wait.h>

#define ERR_EXIT(m) \
	do{perror(m);exit(EXIT_FAILURE);}while(0)

union semun{
	int val;
	struct semid_ds* buf;
	unsigned short* arry;
	struct seminfo *_buf;
};

int sem_create(key_t key){
	int semid;
	semid=semget(key,1,IPC_CREAT|IPC_EXCL|0666);
	if(semid==-1) ERR_EXIT("semget");
	return semid;
}

int sem_open(key_t key){
	int semid;
	semid=semget(key,0,0);
	if(semid==-1) ERR_EXIT("semget");
	return semid;
}

int sem_setval(int semid,int val){
	union semun su;
	su.val=val;
	int ret;
	ret=semctl(semid,0,SETVAL,su);
	if(ret==-1) ERR_EXIT("sem_setval");
	return 0;
}

int sem_getval(int semid){
	int ret;
	ret=semctl(semid,0,GETVAL,0);
	if(ret==-1) ERR_EXIT("sem_getval");
	printf("sem_val=%d",ret);
	return ret;
}

int sem_del(int semid){
	int ret;
	ret=semctl(semid,0,IPC_RMID,0);
	if(ret ==-1) ERR_EXIT("sem_del");
	return 0;
}

int sem_p(int semid){
	struct sembuf sb={0,-1,0};
	int ret;
	ret=semop(semid,&sb,1);
	if(ret ==-1) ERR_EXIT("sem_p");
	return ret;
}

int sem_v(int semid){
	struct sembuf sb={0,1,0};
	int ret;
	ret=semop(semid,&sb,1);
	if(ret==-1) ERR_EXIT("sem_v");
	return ret;
}

int semid;
void print(char c){
	int pause_time;
	srand(getpid());
	for(int i=0;i<10;i++){
		sem_p(semid);
		printf("%c",c);
		fflush(stdout);
		pause_time = rand()%3;
		sleep(pause_time);
		printf("%c",c);
		fflush(stdout);
		sem_v(semid);
		pause_time = rand()%3;
		sleep(pause_time);
	}
}

int main(){
	semid=sem_create(IPC_PRIVATE);
	sem_setval(semid,0);
	pid_t pid;

	pid=fork();
	if(pid==-1) ERR_EXIT("fork");
	if(pid>0){
		sem_setval(semid,1);
		print('O');
		waitpid(pid,NULL,WNOHANG);
		sem_del(semid);
	}else{
		print('X');
	} 
	return 0;
}
