#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define ERR_EXIT(m) \
	do {perror(m); exit(EXIT_FAILURE);}while(0)

int main(){
	int msgid;
	msgid=msgget(123,0);

	if(msgid == -1) ERR_EXIT("msgget");

	printf("msgget success\n");

	msgctl(msgid,IPC_RMID,NULL);

	return 0;
}
