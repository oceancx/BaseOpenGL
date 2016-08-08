#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

typedef unsigned int DWORD;

struct WDataFileIndex {
	DWORD uid;
	DWORD offset;
	DWORD size;
	DWORD space;
};

struct WDataFileHeader {
	DWORD id;
	int number;
	unsigned offset;
};



int main(){
	
	ifstream infile("shape.wd9",ios::binary);

	if(!infile){
		cout<<"文件加载失败"<<endl;
	}

	WDataFileHeader fh ;
	infile.read( (char*)&fh,sizeof(fh));
	if(fh.id !='WDFP')
		cout<<"读取文件出错！"<<endl;
	
	cout<<"file num:" << fh.number <<"\t  file offset:"<<fh.offset<<endl;
	infile.seekg(fh.offset,ios::beg);

	WDataFileIndex* fl = (WDataFileIndex*)malloc(sizeof(WDataFileIndex)*fh.number);
	
	infile.read((char*)(&fl[0]),sizeof(WDataFileIndex)*fh.number);
		

	for(int i = 0 ;i < fh.number;i++){
	//	cout<<fl[i].uid<<endl;
		printf("uid:%d\tsize:%x\toffset:%x\tspace:%d\n",
			fl[i].uid,
			fl[i].size,
			fl[i].offset,
			fl[i].space);
		printf("bytesize:%dK\n",fl[i].size/1024);
		ofstream of(to_string(fl[i].uid),ios::binary);
		
		infile.seekg(fl[i].offset,ios::beg);
	
		char* buffer = (char*)malloc(sizeof(char)*fl[i].size);		
		infile.read(buffer,sizeof(char)*fl[i].size);
		of.write((char*)buffer,sizeof(char)*fl[i].size);
		of.close();
	}

	return 0;
}
