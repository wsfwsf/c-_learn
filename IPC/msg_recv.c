#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define ERR_EXIT(m) \
	do {perror(m); exit(EXIT_FAILURE);}while(0)

struct msgbuf{
	long mtype;
	char mtext[1];
};

int main(int argc,char* argv[]){
	
	int flag=0;
	int type=0;
	int opt;

	while(1){
		opt=getopt(argc,argv,"nt:");
		if(opt=='?')
			exit(EXIT_FAILURE);
		if(opt==-1) break;

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

	msgid=msgget(123,0);

	if(msgid == -1) ERR_EXIT("msgget");

	struct msgbuf *ptr;

	ptr = (struct msgbuf*)malloc(sizeof(long) + 8192);

	ptr->mtype = type;

	int n=0;
	if((n=msgrcv(msgid,ptr,8192,type,flag))<0)
		ERR_EXIT("msgrcv");

	printf("read %d bytes ,type = %ld\n",n,ptr->mtype);

	return 0;
}
