#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>

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
	unsigned int offset;
};


DWORD exchangeDWOD(DWORD x){
	DWORD changed ;
	cout<<x<<":";
	unsigned int a,b,c,d;
	a=0xFF<<24;
	b=0xFF<<16;
	c=0xFF<<8;
	d=0xFF;
	changed = (x&a)>>24
			+ (x&b)>>8
			+ (x&c)<<8
			+ (x&d)<<24;
	cout<<changed<<endl;
	return changed;
}

int main(){
	int a=	0x5046,b=0x4457;
	// printf("%x %x",a,b);
	// printf("%c%c %c%c",((char*)&a)[0],((char*)&a)[1],((char*)&b)[0], ((char*) &b )[1]);
	
	 a ='WDFP';
	printf("%x",a);	

}
