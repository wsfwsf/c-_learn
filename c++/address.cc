#include <iostream>

using namespace std;

int main(){
	int a=10;
	int* p1 = new int(10);
	int* p2 = new int(20);
	int* p3 = &a;
	cout<<"p1="<<p1<<endl;
	cout<<"p2="<<p2<<endl;
	cout<<"p3="<<p3<<endl;
}
