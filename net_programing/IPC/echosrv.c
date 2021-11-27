#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/ipc.h>
#include <sys/socket.h>
#define ERR_EXIT(m) \
	do {perror(m);exit(EXIT_FAILURE);}while(0)

#define MSGMAX 8192

struct msgbuf{
	long mtype;
	char mtext[MSGMAX];
};

void echo_srv(int msgid){
	int nrecv=0;
	struct msgbuf msg;
	memset(&msg,0,sizeof(msg));
	while(1){
		if((nrecv=msgrcv(msgid,&msg,MSGMAX,1,0))<0)
			ERR_EXIT("msgsnd");
		int pid;
		pid=*((int*)msg.mtext);
		fputs(msg.mtext+4,stdout);
		msg.mtype=pid;
		msgsnd(msgid,&msg,nrecv,0);

	}
	struct msgbuf *ptr;
	ptr=(struct msgbuf*)malloc(sizeof(long)+MSGMAX);
}

int main(int argc,char* argv[]){
	int msgid;
	msgid=msgget(1234,IPC_CREAT | 0666);
	if(msgid==-1)
		ERR_EXIT("msgget");
	echo_srv(msgid);
	return 0;
}
