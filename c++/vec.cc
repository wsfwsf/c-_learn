#include <vector>
#include <iostream>

using namespace std;

int main(){
	vector<int*> pvec;
	int* p1 = new int();
	int* p2 = new int();
	int* p3 = new int();
	pvec.push_back(p1);
	pvec.push_back(p2);
	pvec.push_back(p3);
	
	cout<<endl;
}
