#include <pthread.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

struct STU {
	char name[16];
	int age;
} stu;

int main(){
	int shm;
	int ret;
	int ch='a';
	int i;
	struct STU* ptr;
	shm=shm_open("/abc",O_CREAT|O_RDWR,0666);

	if(shm<0) perror("shm_open error\n");
	ret=ftruncate(shm,sizeof(stu)*5);
	if(ret<0) perror("ftruncate error\n");

	ptr=(struct STU*)mmap(NULL,sizeof(stu)*5,PROT_READ|PROT_WRITE,MAP_SHARED,shm,0);
	if(ptr==NULL) perror("mmap error\n");

	for(i=0;i<5;i++){
		printf("name:%s,age:%d\n",ptr->name,ptr->age);
		ptr++;
	}
	
	return 0;	
}
