#include "apue.h"
int main(){
	TELL_WAIT();
	pid_t pid;
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid==0){
		TELL_PARENT(getppid());
		WAIT_PARENT();
		exit(0);
	}
	TELL_CHILD(pid);
	WAIT_CHILD();
	exit(0);
}
