#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
#include<string>
#include"bitmap2.h"
using namespace std;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

// was/wap tcp/tca 开头描述
#pragma pack(2)
struct WasHeader{
	WORD	 flag;  //SP 文件标记
	WORD	 len;   //文件头长度，不包括开头四字节
	WORD	 dir;   //方向数
	WORD	 dir_image; //方向图片数量
	WORD	 width; //总宽度
	WORD	 height;//总高度
	WORD	 pivot_x; //中心x
	WORD	 pivot_y; //中心y	
};

struct Palette{
	WORD colors[256];
};

struct ImageHeader{
	DWORD pivotX;
	DWORD pivotY;
	int width;
	int height;
};

#pragma pack()

int main(){
	ifstream fi("00C8DD73.was",ios::binary);

	WasHeader head;
	fi.read((char*)&head,sizeof(head));
	cout<<"文件标记:\t"<<head.flag<<endl;
	cout<<"文件头长度:\t"<<head.len<<endl;
	cout<<"方向数:\t"<<head.dir<<endl;
	cout<<"方向图片数量:\t"<<head.dir_image<<endl;
	cout<<"总宽度:\t"<<head.width<<endl;
	cout<<"总高度:\t"<<head.height<<endl;
	cout<<"中心x:\t"<<head.pivot_x<<endl;
	cout<<"中心y:\t"<<head.pivot_y<<endl;
	
	if(head.flag == 0x5053){
		Palette palette;
		fi.read((char*)&palette,sizeof(palette) );
		cout<<sizeof( palette.colors) <<endl;
		 //for(int  i = 0 ;i < 256;i++){
		 //	printf("0x%8x\n",(int)palette.colors[i]);		
		 //}	
		int img_list_size = 4 * head.dir * head.dir_image;
		int offset[ head.dir * head.dir_image ];
		cout<< head.dir*head.dir_image<<endl;
	
		cout<<sizeof(offset)<<endl;
		
		fi.read((char*)offset,sizeof(offset));
		
		for(int i = 0 ;i< sizeof(offset[0]);i++){
			cout<<"offset:"<<offset[i]<<endl;
			fi.seekg(offset[i]+16);
			ImageHeader ih;
			fi.read((char*)&ih,sizeof(ih));
			cout<<"w:"<<ih.width<<"\th:"<<ih.height<<endl;
			int hl[ih.height];
			fi.read((char*)hl,sizeof(hl));
			cout<<"tellg():"<<fi.tellg()<<endl;
			for(int j= 0 ;j < ih.height;j++){
				printf("%d\n",hl[j]);
				int off = offset[i]+16+hl[j];
				fi.seekg(off);
				
				BYTE type;
				fi.read((char*)&type,sizeof(BYTE));
				printf("%x\t\n",type);
				int pxNum;
				RGBQUAD color;
				if(type==0){
					//读取结束
					cout<<"读取结束"<<endl;
				}
				if(type&0xc0==0){
					//alpha像素
					if(type & 0x20 == 1){
						pxNum = type&0x1f;

					}else if(type & 0x20 ==0){
						pxNum = type &0x1f;
					}
				}
			}
			
		}

	}else{
		cout<<"读取失败"<<endl;
	}
	
}
//512字节 高彩调色板内容

//图片偏移量

// 列表大小 方向数 * 图片数量 * 4字节
// 偏移量的计算是从调色板的开始处计算 即从文件的
// 第17个字节开始计算

//接下来是图片的数据，格式如下：
/**
	4字节 图片的关键点X
	4字节 图片的关键点Y
	4字节 图片的宽度
	4字节 图片的高度
	接下来是行偏移量列表，列表大小为：
	图片的高度*4字节
	接下来是图片段数据信息
	段数据 = 类型（8比特）+数据
	类型格式如下，
	00 表示alpha像素 剩下的6比特也是0 数据段结束
		如果第三个bit是1，剩下的5比特为alpha层。并且以后的字节是像素索引
		否则，剩下的5比特(0~31)是alpha像素重复次数。(后的字节为alpha，
		再后的字节为索引）
	01 表示像素组 剩下的6比特（0~63）为数据段的长度
	10 表示重复像素n次 ， n为剩下的6比特0~63表示
	11 表述跳过像素n个 n为剩下的6比特 0~63表示
*/
