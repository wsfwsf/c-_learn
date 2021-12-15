#include <stdio.h>

int main(){
	FILE *fp;
	fp=fopen("1.c","r");
	while(putchar(getc(fp)));
	return 0;
}
