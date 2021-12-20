#include<utime.h>
#include<stdio.h>

int main(char* argv){
	struct utimbuf buf;
	utime(argv,&buf);
	printf("last access time:%d\n",(int)buf.actime);
	printf("latst modify time:%d\n",(int)buf.modtime);
}
