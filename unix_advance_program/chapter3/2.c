#include<stdio.h>
#include<time.h>

int main(){
	time_t rawtime;
	char* stime;
	if(time(&rawtime)==-1){
		printf("time error!\n");
		return -1;
	}
	struct tm *info;
	info=gmtime(&rawtime);
	printf("%d:%d:%d\n",info->tm_mday,info->tm_hour,info->tm_min);
	stime = asctime(info);
	printf("%s\n",stime);
	return 0;
}
