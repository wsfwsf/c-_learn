#include<iostream>

extern "C"{
#include <stdio.h>
}

using namespace std;

int main(){
	int x=0x12345678;
	int* p =&x;
	printf("p[0]=%x\n",*((char*)p));

	return 0;
}
