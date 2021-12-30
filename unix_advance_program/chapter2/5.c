#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void){
	struct stat buf;
	stat("1.c",&buf);
	printf("len of 1.c: %ld\n",buf.st_size);
}
