
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

