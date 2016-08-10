#ifndef __BITMAPHEADER
#define __BITMAPHEADER
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<string>
#include "basetype.h"
using namespace std;

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3
#define BI_JPEG 4
#define BI_PNG 5


typedef unsigned  char BYTE;
typedef unsigned  short WORD;
typedef unsigned  int DWORD;
#pragma pack(2)
typedef struct tagBITMAPFILEHEADER{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;
	int biWidth;
	int biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}BITMAPINFOHEADER;

typedef struct tagRGBQUAD{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
}RGBQUAD;

typedef struct tagBITMAPINFO{
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[1];
}BITMAPINFO;

typedef struct BITMAP_FILE_TAG{
	BITMAPFILEHEADER bitmapfileheader;
	BITMAPINFOHEADER bitmapinfoheader;
	RGBQUAD palette[256];
	BYTE *buffer;
}BITMAP_FILE,*BITMAP_FILE_PTR;
#pragma pack()


#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为4字节对齐
    // TGA 文件头
    struct TGA_FILE_HEADER
    {
        uint8 IdLength;				// 图像信息字段(默认:0)
        uint8 ColorMapType;			// 颜色标的类型(默认0)
        uint8 ImageType;			// 图像类型码(支持2或10)
        uint16 ColorMapFirstIndex;	// 颜色表的引索(默认:0)
        uint16 ColorMapLength;		// 颜色表的长度(默认:0)
        uint8 ColorMapEntrySize;	// 颜色表表项的为数(默认:0，支持16/24/32)
        uint16 XOrigin;				// 图像X坐标的起始位置(默认:0)
        uint16 YOrigin;				// 图像Y坐标的起始位置(默认:0)
        uint16 ImageWidth;			// 图像的宽度
        uint16 ImageHeight;			// 图像的高度
        uint8 PixelDepth;			// 图像每像素存储占用位数
        uint8 ImageDescruptor;		// 图像描述字符字节(默认:0，不支持16bit 565格式)
    };
#pragma pack(pop)//恢复对齐状态
#endif
    
//int Load_Bitmap_File(BITMAP_FILE_PTR bitmap,char * filename);
