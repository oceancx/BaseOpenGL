/*********************************************************************************************
*                                         网易公司西游系列
*      《梦幻西游》《大话西游II》《大话西游3内测版》《大话西游3正式版》《大话西游外传》
*                                        地图文件格式读取类
*---------------------------------------------------------------------------------------------
*
*                                           版本 5.0.0
*
*                                     王大理 <wdl@sina.com>
*                                            <QQ:DaliStudio@QQ.com>
*
*                                     官方网址：http://DaliStudio.net
*
*---------------------------------------------------------------------------------------------
* 授权许可：
*     这份授权条款，在使用者符合以下三个条件的情形下，授予使用者使用及再发布本软件，包括源代码
* 及二进制可执行格式的权利，无论此软件是否经修改皆然：
* 
*     1、对于本软件源代码的再发布，必须保留版权声明、包括此三个条件的内容，以及下述的免责声明。
*     2、对于本软件二进制目标可执行格式的再发布，必须附带以文本文件形式和/或发布产品包装中的其
*        他媒介形式，再现上述的版权声明、包括此三个条件的内容，以及下述的免责声明。
*     3、未获得书面许可前，不得使用大理工作室或本软件贡献者之名义，来为本软件的衍生产品做任何
*        表示支持、认可或推广、促销等行为。
*
* 免责声明：
*     本源代码可应用于网易公司的网络游戏：《梦幻西游》、《大话西游II》、《大话西游3内测版》、
*《大话西游3正式版》和《大话西游外传》等游戏的地图文件格式的读取。与此源代码相应的文件格式版权
* 可能属于网易公司和/或云风的风魂游戏引擎所有。
*     此源代码仅应用于学习和教育目的，禁止用于一切商业目的，以及禁止用于一切有可能损害他人利益
* 的地方，否则使用者后果自负。凡是使用本源代码，作者不承担一切任何的责任，请使用者慎重使用本源
* 代码。凡使用本代码者即表示同意此声明，如有任何异议请勿使用本源代码，并永久删除此源代码。
*     此源代码的原作者和贡献者不负任何明示或暗示的任何责任。对于因使用本源代码和/或目标程序而
* 产生的任何直接性、间接性、偶发性、特殊性、惩罚性或任何结果的损害（包括但不限于替代商品或使用
* 损失、资料损失、利益损失、业务中断等等），不负任何责任，即在该种使用已获事前告知可能会造成此
* 类损害的情形下亦然。
*---------------------------------------------------------------------------------------------
*                         版权所有(c) 2003-2010 王大理，保留所有权利。
*********************************************************************************************/
#pragma once
//=========== 包含文件 ============
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "basetype.h"
//=================================


//=================================

using namespace std; // 使用C++标准文件头

namespace NetEase
{
	// 地图的文件头(梦幻、大话2)
	struct MapHeader1
	{
	public:
		// 文件头结构共12字节
		uint32		Flag;		//文件标志
		uint32		Width;		//地图宽
		uint32		Height;		//地图高	

		void print(){
			cout<<"Flag:"<<Flag
			<<"\tWidth:"<<Width
			<<"\tHeight:"<<Height<<endl;
		}
	};

	// 地图的文件头(大话3)
	struct MapHeader3
	{
	public:
		// 文件头结构共40字节
		uint32		Flag;				// 文件标志 0.3M (M3.0) 0x524F4C30
		uint32		Reserved;			// 保留(未知作用,应该都为0)
		uint32		Width;				// 地图实际的宽度
		uint32		Height;				// 地图实际的高度
		uint16		PointWidth;			// 坐标的宽度(默认：20px)
		uint16		PointHeight;		// 坐标的高度(默认：20px)
		uint16		SubWidth;			// 小地图的宽度(默认：400px)
		uint16		SubHeight;			// 小地图的高度(默认：320px)
		uint32		UnitIndexOffset;	// 单元引索的位置
		uint32		UnitIndexNum;		// 单元引索的数量
		uint32		IndexOffset;		// 引索的位置(未知部分)
		uint32		IndexNum;			// 引索的数量(未知部分)
	};

	// ROL0的文件头(大话3)
	struct Rol0Header
	{
	public:
		// 文件头结构共24字节
		uint32		Flag;				// 文件标志 0LOR (ROL0) 0x524F4C30
		uint32		Reserved;			// 保留(未知作用,应该都为0)
		uint32		Width;				// 地图实际的宽度
		uint32		Height;				// 地图实际的高度
		uint16		SubWidth;			// 小地图的宽度(默认：400px)
		uint16		SubHeight;			// 小地图的高度(默认：320px)
		uint32		UnitIndexNum;		// 单元引索的数量
	};

	// 地图的单元头
	struct UnitHeader
	{
	public:
		uint32		Flag;		// 单元标志
		uint32		Size;		// 单元大小
	};

	// 地图的数据
	struct MapData
	{
	public:
		uint32		Size;		// 数据大小
		uint8		*Data;		// 数据内容
	};

	// 读取游戏地图类
	class ReadGameMap
	{
	// 公有
	public:
		ReadGameMap(void);
		~ReadGameMap(void);
		void ZeroMemory(void *p,int size);
		bool LoadMap(string filename);					// 加载地图文件
		uint32 GetMapWidth();							// 获得地图的宽度
		uint32 GetMapHeight();							// 获得地图的高度
		uint32 GetSubMapWidth();						// 获得子地图的宽度(大话3为400px，其他为320px)
		uint32 GetSubMapHeight();						// 获得子地图的高度(大话3为300px，其他为240px)
		uint32 GetPointWidth();							// 获得坐标的宽度(默认为20px)
		uint32 GetPointHeight();						// 获得坐标的高度(默认为20px)
		uint32 GetSubMapTotal();						// 获得子地图的总数
		uint32 GetMaskTotal();							// 获得子地图中Mask的总数
		uint32 GetMapSize();							// 获得地图文件的大小(字节)
		uint32 GetMapType();							// 获得地图文件的类型(1为旧的，2为新的，3为大话3内测版，4为大话3正式版)

		uint32 GetSubMapRowNum();						// 获得地图的行数
		uint32 GetSubMapColNum();						// 获得地图的列数

		bool ReadUnit(uint32 UnitNum);					// 读取地图的单元数据
		bool ReleaseUnit();								// 释放地图单元的内存空间(每调用ReadUnit()都要释放)

		MapData GetJpghData();							// 获得JPGH的数据
		MapData GetHeadData();							// 获得HEAD的数据
		MapData GetImagData();							// 获得IMAG的数据
		MapData GetJpegData();							// 获得JPEG的数据
		MapData GetMaskData(uint8 ID);					// 获得MASK的数据
		MapData GetBlokData();							// 获得BLOK的数据
		MapData GetCellData();							// 获得CELL的数据
		MapData GetBrigData();							// 获得BRIG的数据

		MapData GetRol0Data();							// 获得ROL0的数据(只应用于大话3)
		MapData GetLigtData();							// 获得LIGT的数据(只应用于大话3)

	// 私有
	private:

		bool ReadJPGH(ifstream *file);									// 读取地图JPGH的数据(只应用旧的)
		bool ReadHEAD(ifstream *file);									// 读取地图HEAD的数据(只应用新的)
		bool ReadIMAG(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图IMAG的数据(只应用旧的)
		bool ReadJPEG(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图JPEG的数据
		bool ReadMASK(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图MASK的数据(只应用旧的)
		bool ReadBLOK(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图BLOK的数据(只应用旧的)
		bool ReadCELL(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图CELL的数据
		bool ReadBRIG(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图BRIG的数据

		bool ReadROLO(ifstream *file, uint32 Size);						// 读取ROLO单元数据(只应用于大话3)
		bool ReadLIGT(ifstream *file, uint32 Flag, uint32 Size);			// 读取地图LIGT的数据(只应用于大话3)
		bool ReadEND (ifstream *file, uint32 Flag, uint32 Size);			// 读取地图END 的数据(只应用于大话3)

		uint32 m_FileFlag;								// 文件标志
		string m_FileName;								// 地图的文件名
		uint32 m_FileType;								// 地图文件类型(1为旧的，2为新的，3为大话3内测版，4为大话3正式版)

		float m_MapWidth;								// 地图的宽度
		float m_MapHeight;								// 地图的高度
		float m_SubMapWidth;							// 子地图的宽度
		float m_SubMapHeight;							// 子地图的高度
		uint32 m_PointWidth;							// 坐标的宽度
		uint32 m_PointHeight;							// 坐标的高度
		uint32 m_SubMapRowNum;							// 子地图的行数量
		uint32 m_SubMapColNum;							// 子地图的列数量
		uint32 m_SubMapTotal;							// 子地图的总数
		uint32 m_MapSize;								// 地图的大小

		uint32 m_Reserved;								// 保留
		uint32 m_UnitIndexOffset;						// 单元的引索位置
		uint32 m_UnitIndexNum;							// 单元的引索数量
		uint32 m_IndexOffset;							// 引索位置(未知部分)
		uint32 m_IndexNum;								// 引索数量(未知部分)

		uint32 *m_UnitHeadData;							// 单元的头数据
		uint32 *m_UnitOffsetList;						// 单元的偏移列表
		uint32 *m_OffsetList;							// 未知部分的偏移列表

		uint32 m_MaskNum;								// MASK 的数量
		uint32 m_MaskTemp;								// MASK 临时变量
		uint32 *m_MaskList;								// MASK 的列表

		MapData m_jpgh;									// JPGH 数据
		MapData m_head;									// HEAD 数据
		MapData m_imag;									// IMAG 数据
		MapData m_jpeg;									// JPEG 数据
		MapData m_mask[128];							// MASK 数据
		MapData m_blok;									// BLOK 数据
		MapData m_cell;									// CELL 数据
		MapData m_brig;									// BRIG 数据
		MapData m_rol0;									// ROL0 数据
		MapData m_ligt;									// LIGT 数据

		bool m_isJpgh;									// 是否有此数据，则可释放此内存空间
		bool m_isHead;									// 是否有此数据，则可释放此内存空间
		bool m_isImag;									// 是否有此数据，则可释放此内存空间
		bool m_isJpeg;									// 是否有此数据，则可释放此内存空间
		bool m_isMask;									// 是否有此数据，则可释放此内存空间
		bool m_isBlok;									// 是否有此数据，则可释放此内存空间
		bool m_isCell;									// 是否有此数据，则可释放此内存空间
		bool m_isBrig;									// 是否有此数据，则可释放此内存空间
		bool m_isRol0;									// 是否有此数据，则可释放此内存空间
		bool m_isLigt;									// 是否有此数据，则可释放此内存空间

		UnitHeader m_ErrorUnit;							// 错误单元的标志
	};
}

/************************************************************************
Map File Old Format
Dali Wang <wdl@sina.com>
2004-05-09 起稿 @Changchun
2004-05-10 修改 @Changchun
2006-02-19 修改 @Haikou

=======================MAP HEAD===============================
4字节 XPAM(MAPX)
4字节 地图的宽度
4字节 地图的高度

4*n字节 地图单元的引索 n=地图的宽度/640*2 * 地图高度/480*2
4字节 多出的一个地图单元引索，即结束引索，也就是文件的大小。

4字节 HGPJ (JPGH)
4字节 JPG头的大小
n字节 数据内容 n=JPG头的大小，不包括前面8字节。

==============================================================

4字节 地图单元引索的开始位置，也是KSAM的数量。

4字节 GAMI (IMAG)
4字节 大小(153600)，正好是320x240x2。
n字节 数据，不包括前面8字节。

4字节 GEPJ (JPEG)
4字节 JPEG单元大小，不包括这8字节。
2字节 单元地图的宽度
2字节 单元地图的高度
n字节 地图数据

4字节 KSAM (MASK)
4字节 大小(不定)
n字节 数据，不包括前面8字节。
:
4字节 KSAM (MASK)
4字节 大小(不定)
n字节 数据，不包括前面8字节。


4字节 KOLB (BLOK)
4字节 大小(9600)
n字节 数据，不包括前面8字节。

4字节 LLEC (CELL)
4字节 大小(192)
n字节 数据，不包括前面8字节。

4字节 GIRB (BRIG)
4字节 大小(不定)
n字节 数据，不包括前面8字节。

8字节 结束单元。

==============================================================

XPAM (MAPX) 地图文件头
Index       图象单元引索
HGPJ (JPGH) 图象JPEG Head

GAMI (IMAG) 只有1028.map地图含有这个单元。
GEPJ (JPEG) 图象数据
KSAM (MASK)
:
KSAM (MASK)
KOLB (BLOK) 遮掩规则，一比特代表一个地图像素。
LLEC (CELL) 地图规则，一字节代表一个游戏坐标。
GIRB (BRIG) 光亮规则
:
:
:
GAMI (IMAG) 只有1028.map地图含有这个单元。
GEPJ (JPEG) 图象数据
KSAM (MASK)
:
KSAM (MASK)
KOLB (BLOK) 遮掩规则，一比特代表一个地图像素。
LLEC (CELL) 地图规则，一字节代表一个游戏坐标。
GIRB (BRIG) 光亮规则
************************************************************************/

/************************************************************************
Map File New Format
Dali Wang <wdl@sina.com>
2004-05-09 起稿 @Changchun
2006-02-16 整理 @Haikou
2006-02-20 整理 @Haikou

======================= MAP HEAD =============================
4字节 0.1M (M1.0) 0x302E314D
4字节 地图的宽度
4字节 地图的高度

4*n字节  地图单元的引索 n=地图的宽度/640*2 * 地图高度/480*2
==============================================================

======================= Unknown ==============================
4字节 未知数据的偏移位置，包括这4字节。
n字节 未知用途，大小为：第一个单元引索值减去文件头大小。
注意：这个格式中还没有发现旧格式中的KOLB、GAMI和KSAM。
有可能和这些单元的用途相同。
==============================================================

======================= Unit Data ============================
4字节 地图单元引索的开始位置。
n*4字节 n为上面的值，n为0时不存在。

4字节 GEPJ (JPEG)
4字节 大小
n字节 数据

4字节 LLEC (CELL)
4字节 大小
n字节 数据

4字节 BRIG (GIRB)
4字节 大小
n字节 数据

4字节 结束单元(0x00 0x00 0x00 0x00)。
==============================================================

0.1M		新地图文件头	
Index		数据块引索

Unknown 	n字节，未知用途(暂称为HEAD)

GEPJ(JPEG)	图象数据
LLEC(CELL)	地图规则，一字节代表一个游戏坐标
GIRB(BRIG)	光亮规则
:
:
:
GEPJ(JPEG)	图象数据
LLEC(CELL)	地图规则，一字节代表一个游戏坐标
GIRB(BRIG)	光亮规则

************************************************************************/

/************************************************************************
大话西游3的MAP格式
Dali Wang <wdl@sina.com>
2007-05-18

=========== MAP HEAD ============
4字节 文件标志 0.3M (M3.0) 0x524F4C30
4字节 保留(未知作用,应该都为0)
4字节 地图实际的宽度
4字节 地图实际的高度
2字节 坐标的宽度(默认：20px)
2字节 坐标的高度(默认：20px)
2字节 小地图的宽度(默认：400px)
2字节 小地图的高度(默认：320px)
4字节 单元引索的位置
4字节 单元引索的数量
4字节 引索的位置(未知部分)
4字节 引索的数量(未知部分)

=========== UNIT INDEX =========
4字节*n 单元的引索       

========== 未知数据 ============
可能是地图遮掩关系等数据

========== UNIT DATA ===========
4字节 MASK(KSAM) 遮掩关系
4字节 大小
n字节 数据

4字节 JPEG(GEPJ) JPEG 图片数据
4字节 大小
n字节 数据

4字节 CELL(LLEC) 地图行走规则
4字节 大小
n字节 数据

4字节 LIGT(TGIL) 地图亮度规则
4字节 大小
n字节 数据

4字节 END ( DNE) 单元结束标志
4字节 大小

////////////////////////////////
HEADER 40字节

INDEX
......
INDEX

未知数据

MASK (KSAM) 0x4D41534B
MSK2 (2KSM) 0x4D534B32
JPEG (GEPJ) 0x4A504547
CELL (LLEC) 0x43454C4C
LIGT (TGIL) 0x4C494754
END  ( DNE) 0x454E4420
:
:
:
MASK (KSAM) 0x4D41534B
MSK2 (2KSM) 0x4D534B32
JPEG (GEPJ) 0x4A504547
CELL (LLEC) 0x43454C4C
LIGT (TGIL) 0x4C494754
END  ( DNE) 0x454E4420
************************************************************************/

/************************************************************************
大话3地图 ROL 文件格式
Dali Wang<wdl@sina.com>
2007-05-18

=========== FILE HEAD ==========
24字节
4字节 文件标志 0LOR(ROL0)
4字节 保留 (00 00 00 00)
4字节 大地图的宽度
4字节 大地图的高度
2字节 小地图的宽度
2字节 小地图的高度
4字节 引索的数量

=========== JPEG INDEX =========
n*4字节 引索列表

=========== JPEG DATA ==========
4字节 47 45 50 4A 标志 GEPJ(JPEG)
4字节 B7 20 00 00 数据大小
n字节 数据
:
:
:
4字节 47 45 50 4A 标志 GEPJ(JPEG)
4字节 数据大小
n字节 数据

************************************************************************/