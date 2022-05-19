#include <iostream>

using namespace std;

class A{
public:
	A(){cout<<"构造函数被调用"<<endl;}
	A(const A& a){cout<<"拷贝构造函数被调用"<<endl;}
	//A(A&& a){cout<<"移动构造函数被调用"<<endl;}
	A& operator=(A& a){cout<<"赋值运算符被调用"<<endl;}
	//A& operator=(A&& a){cout<<"移动赋值运算符被调用"<<endl;}
	A& operator=(const A& a){cout<<"赋值运算符被调用"<<endl;}
	
};

A func(A a){
	return a;
}

int main(){
	A a;
	cout<<endl;

	A b(a);
	cout<<endl;

	A c = func(a);
	cout<<endl;

	A d;
	d=func(a);

	return 0;
}
