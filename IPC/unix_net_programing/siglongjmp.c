#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

sigjmp_buf buf;

void handler(int sig){
	siglongjmp(buf,1);
}

int main(){
	if(!sigsetjmp(buf,1)){
		signal(SIGINT,handler);
		printf("Starting\n");
	}else
		printf("Restarting");

	while(1){
		sleep(1);
		printf("Proccessing...\n");
	}

	return 0;
}
