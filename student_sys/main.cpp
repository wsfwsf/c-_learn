#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<vector>

using namespace std;

void input_message();
bool is_num(string,int&);
bool check_stored(string name);
vector<string> split(string s);
void clean_screen();
void query_all_message();
void query_message();
void delete_message();
void alter_message();

int main(){
	clean_screen();
	return 0;
}

void input_message(){
	string student_no;
	string name;
        string math_score;
	string english_score;
	string chinese_score;
	int math_int=0;
	int english_int=0;
	int chinese_int=0; 
	int sum=0; 
	fstream fout;
	fout.open("/home/wsf/test/student_sys/student_score.txt",ios::out | ios::app);
	if(!fout.is_open()){
		cout<<"can not open file student_score.txt!"<<endl;
		return;	
	}
	cout<<"input student no:"<<endl;
	cin>>student_no;
	if(check_stored(student_no)) {
		cout<<"had stored!"<<endl;
		return ;
	}
	cout<<"input student name:"<<endl;
	cin>>name;
	cout<<"input student math_score:"<<endl;
	cin>>math_score;
	while(!is_num(math_score,math_int)){
		cout<<"reinput:"<<endl;
		cin>>math_score;
	}
	cout<<"input student english_score:"<<endl;
	cin>>english_score;
	while(!is_num(english_score,english_int)){
		cout<<"reinput:"<<endl;
		cin>>english_score;
	}
	cout<<"input student chinese_score:"<<endl;
	cin>>chinese_score;
	while(!is_num(chinese_score,chinese_int)){
		cout<<"reinput:"<<endl;
		cin>>chinese_score;
	}
	fout<<student_no<<":"<<name<<":"<<math_score<<":"<<english_score<<":"<<chinese_score<<":"<<endl;
	fout.close();
	fout.clear();
}

bool is_num(string s,int& n){
        int num=0; 
	int size=s.length();
	for(int i=0;i<size;i++){
		if(s[i]<'0'||s[i]>'9') return false;
		num = num*10 +s[i]-'0';
		if(num>100) return false;
	}
	n = num;
	return true;
}

bool check_stored(string student_no){
	vector<string> svec;
        fstream fin("/home/wsf/test/student_sys/student_score.txt");
	if(!fin.is_open()){
		cout<<"sin can not open!"<<endl;
		exit(0);
	}
	string one_message;
	while(getline(fin,one_message)){
		svec=split(one_message);
		if(svec[0]==student_no) return true;	
	}
	return false;
}

vector<string> split(string s){
	vector<string> svec;
	string::size_type pos=0;
        string::size_type last_pos=0;
	while((pos=s.find(':',pos))!=string::npos){
		svec.push_back(s.substr(last_pos,pos-last_pos));
		pos++;
		last_pos=pos;
	}
        return svec;
}

void query_message(){
	cout<<"query student'no:"<<endl;
	string student_no;
	cin>>student_no;
	vector<string> svec;
        fstream fin("/home/wsf/test/student_sys/student_score.txt");
        if(!fin.is_open()){
                cout<<"sin can not open!"<<endl;
                exit(0);
        }
        string one_message;
        while(getline(fin,one_message)){
                svec=split(one_message);
                if(svec[0]==student_no) {
			cout<<"name:"<<svec[1]<<"\tmath score:"<<svec[2]<<"\tenglish score:"<<svec[3]<<"\tchinese score:"<<svec[4]<<endl;
			return;
		}
        }
	cout<<"not find!"<<endl;

}

void query_all_message(){
	vector<string> svec;
        fstream fin("/home/wsf/test/student_sys/student_score.txt");
	string one_message;
	while(getline(fin,one_message)){
                svec=split(one_message);
                cout<<"student_no:"<<svec[0]<<"name:"<<svec[1]<<"\tmath score:"<<svec[2]<<"\tenglish score:"<<svec[3]<<"\tchinese score:"<<svec[4]<<endl;
        	svec.erase(svec.begin(),svec.end());
	}

}


void delete_message(){
	string student_no;
	cout<<"input delete student no:"<<endl;
	cin>>student_no;
	fstream fin("/home/wsf/test/student_sys/student_score.txt");
	fstream fout("/home/wsf/test/student_sys/temp.txt",ios::out | ios::app);
	string one_message;
        while(getline(fin,one_message)){
		string::size_type pos=0;
		pos=one_message.find(':',pos);
		string no=one_message.substr(0,pos);
		if(no!=student_no) fout<<one_message<<endl;
	}
	remove("/home/wsf/test/student_sys/student_score.txt");
	rename(string("/home/wsf/test/student_sys/temp.txt").c_str(),string("/home/wsf/test/student_sys/student_score.txt").c_str());
	fin.close();
	fout.close();
	fin.clear();
	fout.clear();
}

void alter_message(){
	string student_no;
	cout<<"input which student to alter(input student no):"<<endl;
	cin>>student_no;
	cout<<"select 1 alter name,select 2 alter math score,select 3 alter english score,select 4 alter chinese score.."<<endl;
	int n;
	cin>>n;
	string alter_wanted;
        int seleted;
	switch(n){
		case 1:cout<<"input new name:";cin >>alter_wanted;break;
		case 2:cout<<"input new score:";cin >>alter_wanted;break;
		case 3:cout<<"input new score:";cin >>alter_wanted;break;
		case 4:cout<<"input new score:";cin >>alter_wanted;break;
		default: seleted=0;break;
	}
	if(n==0){cout<<"student no can not alter!"<<endl;return;}
	else{	
		int k=0;//no use;
		while(!is_num(alter_wanted,k)){
			cout<<"num a num! reinput num:"<<endl;
			cin>>alter_wanted;
		}
	} 
	fstream fin("/home/wsf/test/student_sys/student_score.txt");
        fstream fout("/home/wsf/test/student_sys/temp.txt",ios::out | ios::app);
        string one_message;
	vector<string> svec;
        while(getline(fin,one_message)){
		svec=split(one_message);
		svec[n]=alter_wanted;
		if(svec[0]==student_no){
			one_message="";
			for(int i=0;i<svec.size();i++){
				one_message += (svec[i]+":");
			}
		}
		fout<<one_message<<endl;
        }
        remove("/home/wsf/test/student_sys/student_score.txt");
        rename(string("/home/wsf/test/student_sys/temp.txt").c_str(),string("/home/wsf/test/student_sys/student_score.txt").c_str());
        fin.close();
        fout.close();
        fin.clear();
        fout.clear();
}
  

void clean_screen(){
	while(true){
		cout<<endl<<endl<<endl;
        	cout<<"1.input student message."<<endl;
        	cout<<"2.query message."<<endl;
        	cout<<"3.show all message."<<endl;
        	cout<<"4.delete student message."<<endl;
        	cout<<"5.alter student message."<<endl<<endl;
        	cout<<"place select num:"<<endl;
        	string selected;
        	cin>>selected;
        	int n;
        	while(selected.length()!=1||selected[0]<'1'||selected[0]>'5'){
                	cout<<"place select num(1-5)!"<<endl;
                	cout<<"place select num:"<<endl;
        	        cin>>selected;
	        }
        	n=selected[0]-'0';
        	switch(n){
                	case 1:input_message();break;
        	        case 2:query_message();break;
      	        	case 3:query_all_message();break;
	                case 4:delete_message();break;
                	case 5:alter_message();break;
        	        break;
	        }

	}

}
