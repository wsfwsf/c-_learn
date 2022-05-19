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
	int msgid;

	if(argc !=3 ){
		fprintf(stderr,"Usage: %s <bytes> <type>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	int len = atoi(argv[1]);
	int type = atoi(argv[2]);

	msgid=msgget(123,0);

	if(msgid == -1) ERR_EXIT("msgget");

	struct msgbuf *ptr;

	ptr = (struct msgbuf*)malloc(sizeof(long)+len);

	ptr->mtype = type;

	msgsnd(msgid,ptr,len,0);

	return 0;
}
