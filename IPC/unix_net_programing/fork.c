#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile long count =2;

void handler(int sig){
	sigset_t mask,prev_mask;
	sigfillset(&mask);
	sigprocmask(SIG_BLOCK,&mask,&prev_mask);
	--count;
	sigprocmask(SIG_SETMASK,&prev_mask,NULL);
	_exit(0);
}

int main(){
	pid_t pid;
	sigset_t mask,prev_mask;
	printf("count=%ld\n",count);

	signal(SIGUSR1,handler);
	if(fork()==0){
		while(1);
	}

	kill(pid,SIGUSR1);
	waitpid(-1,NULL,0);

	sigfillset(&mask);
	sigprocmask(SIG_BLOCK,&mask,&prev_mask);
	printf("count=%ld\n",++count);
	sigprocmask(SIG_SETMASK,&prev_mask,NULL);

	return 0;
}
