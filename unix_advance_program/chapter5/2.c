#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static void sig_alrm(int signo){}

unsigned int sleep1(unsigned int nsecs){
	if(signal(SIGALRM,sig_alrm)==SIG_ERR)
		return nsecs;
	alarm(nsecs);
	pause();
	return alarm(0);
}

int main(){
	sleep1(5);
	return 0;
}
