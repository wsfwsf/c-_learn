#include "apue.h"
#include <setjmp.h>

jmp_buf env;

void func(){
	printf("This is func \n");
	longjmp(env,1);
}

int main(){
	int ret=setjmp(env);
	if(ret==0){
		func();
	}
	if(ret==1){
		printf("This is not func\n");
	}
	return 0;
}


