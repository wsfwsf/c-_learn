#include "apue.h"

int sig_user_flag=0;

void sig_user(int signo);

int main(){
	if(signal(SIGUSR1,sig_user)==SIG_ERR)
		err_sys("signal err");
	while(sig_user_flag==0)
		pause();
	printf("receive USR1\n");
	return 0;
}

void sig_user(int signo){
	sig_user_flag=1;	
}
