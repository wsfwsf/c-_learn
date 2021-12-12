#include "apue.h"

int main(){
	if(chdir("/home")<0)
		err_sys("chdir failed");
	printf("chdir to /home successful.\n");
	return 0;
}
