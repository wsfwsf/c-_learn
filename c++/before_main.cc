#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
extern "C"{
#include <stdio.h>
}
using namespace std;

__attribute((constructor)) void before(){
	printf("before main 1\n");
}

int a = []()->int{
	printf("before main 2\n");
	return 0;
}();

int main(){
	printf("Begin main ...\n");
	printf("1+2=%d\n",[](){return 1+2;}());

	unsigned seed;
	seed=time(0);
	srand(seed);

	vector<int> vec;
	for(int i=0;i<15;i++){
		vec.push_back(rand()%100);
	}

	sort(vec.begin(),vec.end(),[](int a,int b)->bool{return a<b;});

	for(int& n:vec){
		cout<<n<<' ';
	}
	cout<<endl;
	return 0;
}
