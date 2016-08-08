#include "ReadGameWdf.h"

using namespace WDF;
using namespace std; // 使用C++标准文件头

ReadGameWdf::ReadGameWdf()
{
	string filename("/Users/oceancx/Desktop/shape.wdf");
	cout<<"LoadWdf"<<endl;
	ifstream infile;
	infile.open((char*)filename.c_str(),
		ios::in|ios::binary);
	if(!infile){
		cerr<<"Can't open Wdf File:"<<filename<<endl;
		exit(EXIT_FAILURE);	//退出
	}
	HEADER header;
	infile.read((char*)&header,sizeof(header));
	
	HEADER *m_Header = &header;

	int m_FileType;	
	unsigned int Flag = m_Header->Flag;
	switch(Flag)
	{
        case 0x57444650: // WDFP
        m_FileType=1;
        break;
        case 0x57444658: // WDFX
        m_FileType=2;
        break;
        case 0x57444648: // WDFH
        m_FileType=3;
        break;
        default:
        m_FileType=0;
    };
    printf("fileType:%s\n",&Flag );
   
    int m_Number = m_Header->Number;
    int m_Offset = m_Header->Offset;
	
	
	FILELIST* m_FileList=new FILELIST[m_Number];
	memset(m_FileList,0,sizeof(FILELIST)*m_Number);
	infile.seekg(m_Offset);
	infile.read((char*)m_FileList,sizeof(FILELIST)*m_Number);
	infile.close();
	cout<<"m_Number:"<<m_Number<<endl;
   	for (unsigned int i=0;i<m_Number;i++)
    {
    	
    	int size=m_FileList[i].Size;
    	int offset=m_FileList[i].Offset;
    	char* Data=new char[size];
    	infile.open(filename,ios::in|ios::binary);
    	infile.seekg(offset);
    	infile.read(Data,size);
    	infile.close();

    	char *temp = new char[20];
		sprintf(temp,"%08X.was",m_FileList[i].Hash);
		string TempName="";
		TempName+=temp;
		ofstream outfile(TempName,ios::out|ios::binary);
		outfile.write(Data,size);
		outfile.close();
		delete[] temp;
		delete[] Data;
    }

}
void ReadGameWdf::ReadWas(string filename)
{
	
}
ReadGameWdf::~ReadGameWdf()
{

}