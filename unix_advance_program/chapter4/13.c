#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	char *buf = getlogin();
	printf("getlogin:%s\n",buf);
	exit(0);
}
