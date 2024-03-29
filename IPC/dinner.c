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

void wait_for_forks(int);
void free_forks(int);

union semun{
	int val;
	struct semid_ds* buf;
	unsigned short* arry;
	struct seminfo *_buf;
};

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

#define DELAY ((rand()%5+1))

void philosophere(int no){
	for(;;){
		printf("%d is thinking...\n",no);
		sleep(DELAY);
		printf("%d is hungry\n",no);
		wait_for_forks(no);
		printf("%d is eating\n",no);
		sleep(DELAY);
		free_forks(no);
	}
}

void wait_for_forks(int no){
	int left=no;
	int right =(no+1)%5;

	struct sembuf buf[2]={{left,-1,0},{right,-1,0}};
	semop(semid,buf,2);
}

void free_forks(int no){
	int left=no;
        int right =(no+1)%5;

        struct sembuf buf[2]={{left,1,0},{right,1,0}};
        semop(semid,buf,2);
}

int main(){
	semid = semget(IPC_PRIVATE,5,IPC_CREAT|0666);
	if(semid==-1) ERR_EXIT("semget");

	int i;
	union semun su;
	su.val=1;
	for(int i=0;i<5;i++){
		semctl(semid,i,SETVAL,su);
	}
	int no=0;
	pid_t pid;
	for(i=1;i<5;i++){
		pid=fork();
		if(pid==-1) ERR_EXIT("fork");
		if(pid==0){
			no=i;
			break;
		}

	}

	philosophere(no);
	return 0;
}
