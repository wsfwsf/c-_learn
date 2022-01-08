#include <signal.h>
#include <unistd.h>

int loop;

static void sig_alrm(int signo){
	loop=0;
}

unsigned int sleep1(unsigned int nsecs){
	loop=1;
	if(signal(SIGALRM,sig_alrm)==SIG_ERR)
		return nsecs;
	alarm(nsecs);
	while(loop);
	return alarm(0);
}

int main(){
	return sleep1(5);
}
