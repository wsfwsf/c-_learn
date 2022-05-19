#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define ERR_EXIT(m) \
	do {perror(m); exit(EXIT_FAILURE);}while(0)

#define MAXSIZE 8192

struct msgbuf{
	long mtype;
	char mtext[1];
};

void echo_serv(int msgid){
	struct msgbuf msg;
	memset(&msg,0,sizeof(msg));
	int n;

	while(1){
		if((n=msgrcv(msgid,&msg,MAXSIZE,1,0))<0)
			ERR_EXIT("msgrcv");

		int pid;
		pid=*((int*)msg.mtext);

		fputs(msg.mtext,stdout);
		msg.mtype=pid;
		msgsnd(msgid,&msg,n,0);
	}
}

int main(int argc,char* argv[]){

	int msgid;
	msgid=msgget(123,IPC_CREAT | 0666);
	if(msgid==-1)
		ERR_EXIT("msgget");
	echo_serv(msgid);
	return 0;
}
