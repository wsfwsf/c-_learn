#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void Print(char* c){
	int n=sizeof(c)/sizeof(char);
	printf("size:%d\n",n);
	pthread_exit(c);
}

int main(){
	pthread_t pid;
	void* retval;
	char s[32]={0};
	strcpy(s,"Hello World");
	pthread_create(&pid,NULL,(void*)Print,(void*)s);
	if(pthread_join(pid,&retval)<0){
		strerror(errno);
		return -1;
	}else{
		printf("return val:%s\n",(char*)retval);
	}
	
	return 0;
}
