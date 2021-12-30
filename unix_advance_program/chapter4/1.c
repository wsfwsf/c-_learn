#include<unistd.h>
#include<stdio.h>

int main(){
	printf("pid:%d\n",(int)getpid());
	printf("ppid:%d\n",(int)getppid());
	printf("uid:%d\n",(int)getuid());
	printf("euid:%d\n",(int)geteuid());
	printf("gid:%d\n",(int)getgid());
	printf("egid:%d\n",(int)getegid());
	return 0;
}
