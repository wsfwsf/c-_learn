#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <string.h>

#define ERR_EXIT(m) \
        do{perror(m);exit(EXIT_FAILURE);}while(0)
typedef struct {
	char name[32];
	int age;
} stu;

int main(){
	int shmid;
	shmid=shm_open("/xyz",O_CREAT|O_RDWR,0666);

	if(shmid==-1)
		ERR_EXIT("shm_open");

	if(ftruncate(shmid,sizeof(stu))<0)
		ERR_EXIT("ftruncate");
	close(shmid);
}
