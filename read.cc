#include<iostream>
#include<fstream>
using namespace std;

typedef unsigned long DWORD ;


struct student{
	char name[20];
	int num;
	int age;
	char sex;
};



struct FileHeader{
	DWORD id;
	int number;
	unsigned offset;
};


int main(){

	//ifstream in;
	//in.open("shape.wd9",ios::in|ios::binary);
	student stud[3]={"Li",1001,18,
	'f',"Fun",1002,19,'m',"Wang",1004,17,'f'};

	ofstream outfile("stdu.dat",ios::binary);
	if(!outfile){
		cerr<<"open error!"<<endl;
		abort();
	}

	for(int i= 0 ;i < 3;i++)
		outfile.write((char*)&stud[i],sizeof(stud[i]));
	outfile.close();
	return 0;
	


}
