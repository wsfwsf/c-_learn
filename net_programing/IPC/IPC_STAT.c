#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#define ERR_EXIT(m) \
	do {perror(m);exit(EXIT_FAILURE);}while(0)

int main(void){
	int msgid;
	msgid=msgget(1234,IPC_CREAT|0666);
	if(msgid==-1)
		ERR_EXIT("msgget");
	printf("msgget successful\n");
	printf("msgid=%d\n",msgid);
	
	struct msqid_ds buf;
	msgctl(msgid,IPC_STAT,&buf);
	printf("mode=%o\n",buf.msg_perm.mode);
	printf("bytes=%ld\n",buf.__msg_cbytes);
	printf("number=%d\n",(int)buf.msg_qnum);
	printf("msgmnb=%d\n",(int)buf.msg_qbytes);
	return 0;
}
