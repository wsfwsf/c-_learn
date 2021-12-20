#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd;
	fd=open("1.c",O_RDONLY);
	FILE *fp;
	fp=fopen("1.c","r");
	printf("fd:%d\n",fd);
	printf("fileno(FILE *fp):%d\n",fileno(fp));
	return 0;
}
