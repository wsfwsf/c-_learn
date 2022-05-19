#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void handler(int sig){
	printf("recv a sig:%d,pid=%u\n",sig,getpid());
}

int main(){
	struct sigaction old_action,new_action;
	new_action.sa_handler=handler;
	sigfillset(&new_action.sa_mask);
	new_action.sa_flags=0;

	sigaction(SIGCHLD,&new_action,&old_action);

	int i;
	pid_t pid[5];

	for(i=0;i<5;i++){
		if((pid[i]=fork())<0) perror("fork error");
		else if(pid[i]==0){
			printf("create a pid:%u\n",getpid());		
			exit(0);
		}
		sleep(1);
	}

	while(waitpid(-1,NULL,0)>0) printf("exit...\n");

	return 0;
	
}
