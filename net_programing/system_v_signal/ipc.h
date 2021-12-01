#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>


#define ERR_EXIT(m) \
        do {perror(m);exit(EXIT_FAILURE);}while(0)


union semun{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
        struct seminfo *__buf;
};

int sem_create(key_t key){
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

