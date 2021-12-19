#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char *argv[]={"ls","-lh",NULL};
	pid_t pid;
	if((pid=vfork())<0){
		printf("vfork error\n");
	}else if(pid==0){
		execv("/bin/ls",argv);
	}
	exit(0);
}
