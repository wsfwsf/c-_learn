#include <iostream>

using namespace std;

struct s{
	char c;
	int i;
	char c2;
	int i2;
} S;

struct s2{
	short s1;
	short s2;
	int i;
} S2;

int main(){
	
	S.c='a';
	S.c2='a';
	
	cout<<"&S="<<&S<<endl;
	cout<<"&S.c="<<&S.c<<endl;
	cout<<"&S.i="<<&S.i<<endl;
	cout<<"&S.c2="<<&S.c2<<endl;
	cout<<"&S.i2="<<&S.i2<<endl;

	cout<<"sizeof(int)="<<sizeof(int)<<endl;

	cout<<endl;

	cout<<"&S2.s1="<<&S2.s1<<endl;
	cout<<"&S2.s2="<<&S2.s2<<endl;
	cout<<"&s.i="<<&S2.i<<endl;

	struct s2* p = new s2();
	
	return 0;
}
