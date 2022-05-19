#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

int main(int argc,char* argv[]){
	sem_t* sem;
	int val;

	if(argc != 2) perror("Usage: <name>");

	sem=sem_open(argv[1],O_CREAT,0666,1);
	sem_wait(sem);
	sem_getvalue(sem,&val);
	printf("%d\n",val);

	return 0;
}
