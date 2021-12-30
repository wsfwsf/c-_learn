#ifndef _SHM_FIFO_H_
#define _SHM_FIFO_H_

#include "ipc.h"

typedef struct Shmfifo shmfifo_t;
typedef struct Shmhead shmhead_t;

struct Shmhead{
	unsigned int blksize;
	unsigned int blocks;
	unsigned int rd_index;
	unsigned int wr_index;
};

struct Shmfifo{
	shmhead_t* p_shm;
	char* p_payload;
	
	int shmid;
	int sem_mutex;
	int sem_full;
	int sem_empty;
};

shmfifo_t* shminfo_init(int key,int blksize,int blocks);
void shmfifo_put(shmfifo_t* fifo,const void *buf);
void shmfifo_get(shmfifo_t* fifo,char* buf);
void shmfifo_destroy(shmfifo_t* fifo);

#endif
