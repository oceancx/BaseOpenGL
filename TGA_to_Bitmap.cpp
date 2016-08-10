#include "bitmap.h"

int main(){
	ifstream infile("42DC698F0000.tga",ios::binary|ios::in);
	if(!infile){
		cout<<"打开文件失败"<<endl;
	}
	TGA_FILE_HEADER TgaHeader;
	infile.read((char*)&TgaHeader,sizeof(TGA_FILE_HEADER));
  

    ofstream outfile("42DC698F0000.bmp",ios::out|ios::binary);
    if(!outfile){
        
        return 0;
    }
    BITMAPFILEHEADER bithead;
    BITMAPINFOHEADER bitinfo;
    int headsize,linesize,i,j,s;
    DWORD color;
    int width = TgaHeader.ImageWidth;
    int height = TgaHeader.ImageHeight;
    linesize=(width*3+3)&0xfffffffc;
    s=linesize-width*3;
    memset(&bithead,0,sizeof(bithead));
    headsize=sizeof(bithead)+sizeof(bitinfo);
    bithead.bfType='MB';
    printf("%s\n",&bithead.bfType );
    bithead.bfSize=headsize+linesize*height;
    printf("%x\n",bithead.bfSize );
    bithead.bfOffBits=headsize;
    printf("%x\n", headsize);
    outfile.write((char*)&bithead,sizeof(bithead));
    bitinfo.biSize=sizeof(bitinfo);
    bitinfo.biWidth=width;
    bitinfo.biHeight=height;
    cout<<"height:" <<height<<endl;
    bitinfo.biPlanes=1;
   bitinfo.biBitCount=32;
    bitinfo.biCompression=0;
    bitinfo.biSizeImage=0;
   bitinfo.biXPelsPerMeter=72;
    bitinfo.biYPelsPerMeter=72;
    bitinfo.biClrUsed=0;
   bitinfo.biClrImportant=0;
   outfile.write((char*)&bitinfo,sizeof(bitinfo));
   
   DWORD* data=new DWORD[width*height];
   infile.read((char*)data,width*height*4);
  
    outfile.write((char*)data,width*height*4);
    outfile.close();
    // memset(&TgaHeader,0,18);
    // TgaHeader.IdLength=0;			// 图像信息字段(默认:0)
    // TgaHeader.ColorMapType=0;		// 颜色标的类型(默认0)
    // TgaHeader.ImageType=0x02;			// 图像类型码(支持2或10)
    // TgaHeader.ColorMapFirstIndex=0;	// 颜色表的引索(默认:0)
    // TgaHeader.ColorMapLength=0;		// 颜色表的长度(默认:0)
    // TgaHeader.ColorMapEntrySize=0;	// 颜色表表项的为数(默认:0，支持16/24/32)
    // TgaHeader.XOrigin=0;				// 图像X坐标的起始位置(默认:0)
    // TgaHeader.YOrigin=0;				// 图像Y坐标的起始位置(默认:0)
    // TgaHeader.ImageWidth=GetHeadWidth();			// 图像的宽度
    // TgaHeader.ImageHeight=GetHeadHeight();			// 图像的高度
    // TgaHeader.PixelDepth=32;			// 图像每像素存储占用位数
    // TgaHeader.ImageDescruptor=8;		// 图像描述字符字节(默认:0)

	
}

