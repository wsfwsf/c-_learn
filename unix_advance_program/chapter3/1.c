#include<pwd.h>
#include<string.h>
#include<stdio.h>

int main(){
	struct passwd* buf;
	memset(buf,0,sizeof(buf));
	char* name="wsf";
	buf=getpwnam(name);
	if(buf==NULL){
		printf("do not exist!\n");
	}
	printf("name is:%s\n",buf->pw_name);
	printf("passwd is:%s\n",buf->pw_passwd);
	printf("user id is:%d\n",(int)buf->pw_uid);
	printf("group id is:%d\n",buf->pw_gid);
	return 0;
}
