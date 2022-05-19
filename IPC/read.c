#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int fd=open("1.txt",O_RDONLY);
	return 0;
}
