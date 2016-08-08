#include"bitmap.h"

int Load_Bitmap_File(BITMAP_FILE_PTR bitmap,char* filename){
	
	string name(filename);
	ifstream fi(name,ios::binary);

	fi.read((char*)&(bitmap->bitmapfileheader),sizeof(BITMAPFILEHEADER));
	if(bitmap->bitmapfileheader.bfType != 0x4d42){
		cout<<"打开失败"<<endl;
	}
	
	printf("bfType:%x\n",bitmap->bitmapfileheader.bfType);
	printf("bfSize:%x\n",bitmap->bitmapfileheader.bfSize);
	printf("bfReserved1:%x\n",bitmap->bitmapfileheader.bfReserved1);
	printf("bfReserved2:%x\n",bitmap->bitmapfileheader.bfReserved2);
	printf("bfOffBits:%x\n",bitmap->bitmapfileheader.bfOffBits);


	fi.read((char*)&bitmap->bitmapinfoheader,sizeof(BITMAPINFOHEADER));

	printf("biSize:%d\n",bitmap->bitmapinfoheader.biSize ); 
	printf("biWidth:%d\n",bitmap->bitmapinfoheader.biWidth ); 
	printf("biHeight:%d\n",bitmap->bitmapinfoheader.biHeight ); printf("biPlanes:%d\n",bitmap->bitmapinfoheader.biPlanes ); printf("biBitCount:%d\n",bitmap->bitmapinfoheader.biBitCount ); 
	printf("biCompression:%d\n",bitmap->bitmapinfoheader.biCompression ); 
	printf("biSizeImage:%d\n",bitmap->bitmapinfoheader.biSizeImage ); 
	printf("biXPelsPerMeter:%d\n",bitmap->bitmapinfoheader.biXPelsPerMeter ); 
	printf("biYPelsPerMeter:%d\n",bitmap->bitmapinfoheader.biYPelsPerMeter ); 
	printf("biClrUsed:%d\n",bitmap->bitmapinfoheader.biClrUsed ); 
	printf("biClrImportant:%d\n",bitmap->bitmapinfoheader.biClrImportant ); 

	cout<<"biBitCount:"<<bitmap->bitmapinfoheader.biBitCount<<endl;
	cout<<"biSizeImage:"<<bitmap->bitmapinfoheader.biSizeImage<<endl;	
	
	if(bitmap->bitmapinfoheader.biBitCount == 8){
		fi.read((char*) &bitmap->palette ,256*sizeof(RGBQUAD));
	}

	fi.seekg(-(int)(bitmap->bitmapinfoheader.biSizeImage),ios::end);

	
	if(bitmap->buffer)
		free(bitmap->buffer);

	if(!(bitmap->buffer = (BYTE*)malloc(bitmap->bitmapinfoheader.biSizeImage))){
			cout<<"图片元数据读取失败"<<endl;
	}
	cout<<"size:"<<bitmap->bitmapinfoheader.biSizeImage<<endl;
	
	fi.read((char*)bitmap->buffer,bitmap->bitmapinfoheader.biSizeImage);
	for(int i = 0 ;i < 10;i++){
		printf("%x",bitmap->buffer[i] );
	}
	printf("\n");

	fi.close();


	return 0;
}

int main(){
	BITMAP_FILE_PTR bitmap = (BITMAP_FILE_PTR)malloc(sizeof(BITMAP_FILE));
	string filename("Smiley.bmp");
	Load_Bitmap_File(bitmap,"Smiley.bmp");
}
