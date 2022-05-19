#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class A{
public:
	A(int num=0):num_(num){}
	int operator+(int k){return num_+k;}
	int operator()(){return num_;}
private:
	int num_;
};

class SORT{
public:
	bool operator()(int m,int n){
		return m<=n;
	}
};

int main(){
	A a(20);
	cout<<a+10<<endl;
	cout<<a()<<endl;

	cout<<endl;
	vector<int> vec;
	for(int i=-2;i<=4;i++){
		vec.push_back(i*i);
	}
	sort(vec.begin(),vec.end(),SORT());
	for(int i=0;i<vec.size();i++){
		cout<<vec[i]<<' ';
	}
	cout<<endl;
	return 0;
}
