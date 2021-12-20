#include <stdio.h>
#include <string.h>
#define buffsize 1024

int main(){
	FILE* fp;
	char buf[buffsize];
	memset(buf,0,sizeof(buf));
	fp=fopen("1.c","r");
	if(fp==NULL) {
		printf("open error!\n");
	}
	while(fgets(buf,buffsize,fp)!=NULL){
		puts(buf);
		memset(buf,0,sizeof(buf));
	}

	puts("this is pus function\n");
	return 0;
}
