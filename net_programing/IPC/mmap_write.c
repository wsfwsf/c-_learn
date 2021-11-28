#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/ipc.h>
#include <sys/socket.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
#define ERR_EXIT(m) \
	do {perror(m);exit(EXIT_FAILURE);}while(0)

typedef struct stu{
	char name[4];
	int age;
}STU;

int main(int argc,char* argv[]){
	if(argc!=2){
		fprintf(stderr,"Usage:%s<file>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	int fd;
	fd =open(argv[1],O_CREAT | O_TRUNC | O_RDWR,0666);
	if(fd==-1)
		ERR_EXIT("open");
	lseek(fd,sizeof(STU)*5-1,SEEK_SET);
	write(fd,"",1);
	STU* p;
	p=(STU*)mmap(NULL,sizeof(STU)*5,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if(p==NULL)
		ERR_EXIT("mmap");
	char ch='a';
	int i;
	for(i=0;i<5;i++){
		memcpy((p+i)->name,&ch,1);
		(p+i)->age=20+i;
		ch++;
	}
	printf("initiallize finish\n");
	munmap(p,sizeof(STU)*5);
	printf("EXIT...\n");
	return 0;
}
