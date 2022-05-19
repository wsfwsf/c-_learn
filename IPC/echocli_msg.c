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
	char mtext[MAXSIZE];
};

void echo_cli(int msgid){
	int n;
	int pid;
	pid = getpid();

	struct msgbuf msg;
	memset(&msg,0,sizeof(msg));
	*((int*)msg.mtext)=pid;
	msg.mtype=1;
	while(fgets(msg.mtext+4,MAXSIZE,stdin)!=NULL){
		if(msgsnd(msgid,&msg,4+strlen(msg.mtext+4),0)<0)
			ERR_EXIT("msgsnd");
		memset(msg.mtext+4,0,MAXSIZE-4);
		if((n=msgrcv(msgid,&msg,MAXSIZE,pid,0))<0)
			ERR_EXIT("msgrcv");
		fputs(msg.mtext+4,stdout);
		memset(msg.mtext+4,0,MAXSIZE-4);
	}
}

int main(int argc,char* argv[]){

	int msgid;
	msgid=msgget(123,0);
	if(msgid==-1)
		ERR_EXIT("msgget");
	echo_cli(msgid);
	return 0;
}
