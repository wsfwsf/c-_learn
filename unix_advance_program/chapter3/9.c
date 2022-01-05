#include <unistd.h>
#include <stdio.h>

int main(){
	char* argv[]={"ls","-lh",NULL};
	if(execv("/bin/ls",argv)==-1)
		printf("execv error\n");
	return 0;
}
