#include <stdio.h>

int ADD(int a,int b){
	return a+b;
}

void F(int a,int b,int (*func)(int,int)){
	printf("%d+%d=%d\n",a,b,func(a,b));
}

int main(){
	F(10,20,ADD);
	return 0;
}
