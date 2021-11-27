#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include <sys/socket.h>
#define ERR_EXIT(m) \
	do {perror(m);exit(EXIT_FAILURE);}while(0)

#define MSGMAX 8192

struct msgbuf{
	long mtype;
	char mtext[1];
};

int main(int argc,char* argv[]){
	int flag=0;
	int type =0;
	int opt;
	while(1){
		opt=getopt(argc,argv,"nt:");
		if(opt=='?')
			exit(EXIT_FAILURE);
		if(opt==-1)
			break;
		switch(opt){
			case 'n':
				flag |= IPC_NOWAIT;
				break;
			case 't':
				type = atoi(optarg);
				break;
		}
	}
	int msgid;
	msgid=msgget(1234,0);
	if(msgid==-1)
		ERR_EXIT("msgget");
	struct msgbuf *ptr;
	ptr=(struct msgbuf*)malloc(sizeof(long)+MSGMAX);
	ptr->mtype=type;
	int nrecv=0;
	if((nrecv=msgrcv(msgid,ptr,MSGMAX,type,flag))<0)
		ERR_EXIT("msgsnd");
	printf("read=%dbytes type=%ld\n",nrecv,ptr->mtype);
	return 0;
}
