#include <stdlib.h>
#include <stdio.h>

int main(int argc,char* argv[]){
	int i=1;
	while(i<argc)
		//printf("%s\n",argv[i++]);
		printf("%s\n",getenv(argv[i++]));
	if(putenv("hello=wsf")!=0){
		printf("putenv error\n");
		return 0;
	}
	printf("env hello value is %s\n",getenv("hello"));
	if(unsetenv("hello")!=0){
		printf("unsetenv error\n");
	}else{
		printf("unset env hello\n");
	}
	return 0;
}
