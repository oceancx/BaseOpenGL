///*********************************************************************************************
//*                                         网易公司西游系列
//*      《梦幻西游》《大话西游II》《大话西游3内测版》《大话西游3正式版》《大话西游外传》
//*                                        地图文件格式读取类
//*---------------------------------------------------------------------------------------------
//*
//*                                           版本 5.0.0
//*
//*                                     王大理 <wdl@sina.com>
//*                                            <QQ:DaliStudio@QQ.com>
//*
//*                                     官方网址：http://DaliStudio.net
//*
//*---------------------------------------------------------------------------------------------
//* 授权许可：
//*     这份授权条款，在使用者符合以下三个条件的情形下，授予使用者使用及再发布本软件，包括源代码
//* 及二进制可执行格式的权利，无论此软件是否经修改皆然：
//* 
//*     1、对于本软件源代码的再发布，必须保留版权声明、包括此三个条件的内容，以及下述的免责声明。
//*     2、对于本软件二进制目标可执行格式的再发布，必须附带以文本文件形式和/或发布产品包装中的其
//*        他媒介形式，再现上述的版权声明、包括此三个条件的内容，以及下述的免责声明。
//*     3、未获得书面许可前，不得使用大理工作室或本软件贡献者之名义，来为本软件的衍生产品做任何
//*        表示支持、认可或推广、促销等行为。
//*
//* 免责声明：
//*     本源代码可应用于网易公司的网络游戏：《梦幻西游》、《大话西游II》、《大话西游3内测版》、
//*《大话西游3正式版》和《大话西游外传》等游戏的地图文件格式的读取。与此源代码相应的文件格式版权
//* 可能属于网易公司和/或云风的风魂游戏引擎所有。
//*     此源代码仅应用于学习和教育目的，禁止用于一切商业目的，以及禁止用于一切有可能损害他人利益
//* 的地方，否则使用者后果自负。凡是使用本源代码，作者不承担一切任何的责任，请使用者慎重使用本源
//* 代码。凡使用本代码者即表示同意此声明，如有任何异议请勿使用本源代码，并永久删除此源代码。
//*     此源代码的原作者和贡献者不负任何明示或暗示的任何责任。对于因使用本源代码和/或目标程序而
//* 产生的任何直接性、间接性、偶发性、特殊性、惩罚性或任何结果的损害（包括但不限于替代商品或使用
//* 损失、资料损失、利益损失、业务中断等等），不负任何责任，即在该种使用已获事前告知可能会造成此
//* 类损害的情形下亦然。
//*---------------------------------------------------------------------------------------------
//*                         版权所有(c) 2003-2010 王大理，保留所有权利。
//*********************************************************************************************/
//#include "ReadGameMap.h"
//using namespace NetEase; // 使用NetEase命名空间
//
//ReadGameMap::ReadGameMap(void)
//{
//}
//
//ReadGameMap::~ReadGameMap(void)
//{
//}
//
//void ReadGameMap::ZeroMemory(void *p,int size)
//{
//	memset(p,0,sizeof(size));
//}
//
//// 加载地图文件
//bool ReadGameMap::LoadMap(string filename)
//{
//	cout<<"LoadMap"<<endl;
//	ifstream infile;
//	m_FileName = filename; // 地图文件名
//	cout<<filename<<endl;
//	// 打开地图文件
//	locale::global(locale(""));//将全局区域设为操作系统默认区域
//	infile.open((char*)filename.c_str(), ios::in|ios::binary);
//	locale::global(locale("C"));//还原全局区域设定
//	// 判断文件是否存在
//	if(!infile)
//	{
//		cerr << "Can't open Map File :" << filename << endl;
//		exit(EXIT_FAILURE); // 退出
//	}
//
//	uint32 TempFlag; // 临时文件标志
//	infile.read((char*)&TempFlag,sizeof(uint32));
//	//infile.seekg(-4); // 往回跳4个字节
//	infile.seekg(0,ios::beg);
//
//	// 文件标志
//	// 0x4D415058 (MAPX) 大话2旧地图
//	// 0x4D312E30 (M1.0) 大话2新地图 梦幻地图
//	// 0x4D322E35 (M2.5) 大话3内测版
//	// 0x4D332E30 (M3.0) 大话3正式版
//	// 0x524F4C30 (ROL0) 大话3地图背景文件
//	cout<<TempFlag<<endl;
//	if ((TempFlag == 0x4D415058) | (TempFlag == 0x4D312E30) | (TempFlag == 0x4D322E35) | (TempFlag == 0x4D332E30) | (TempFlag == 0x524F4C30))
//	{
//		switch(TempFlag)
//		{
//		case 0x4D415058:
//			m_FileType = 1; // 大话2旧地图格式
//			break;
//		case 0x4D312E30:
//			m_FileType = 2; // 大话2新地图、梦幻地图格式
//			break;
//		case 0x4D322E35:
//			m_FileType = 3; // 大话3内测版地图格式
//			break;
//		case 0x4D332E30:
//			m_FileType = 4; // 大话3正式版地图格式
//			break;
//		case 0x524F4C30:
//			m_FileType = 5; // 大话3地图背景文件格式
//			break;
//		}
//
//		if ((m_FileType == 1) | (m_FileType == 2))
//		{
//			m_SubMapWidth = 320;
//			m_SubMapHeight = 240;
//			MapHeader1 *header = new MapHeader1[1];
//			ZeroMemory(header,sizeof(MapHeader1));
//			infile.read((char*)header,sizeof(MapHeader1));
//			m_FileFlag=header->Flag;		// 文件标志
//			m_MapWidth = (float)header->Width;	// 地图的宽度
//			m_MapHeight= (float)header->Height;	// 地图的高度
//			// header->print();
//			delete [] header;
//		}
//
//		if ((m_FileType == 3) | (m_FileType == 4))
//		{
//			m_SubMapWidth = 400;
//			m_SubMapHeight = 320;
//			MapHeader3 *header = new MapHeader3[1];
//			ZeroMemory(header,sizeof(MapHeader3));
//			infile.read((char*)header,sizeof(MapHeader3));
//			m_FileFlag=header->Flag;						// 文件标志
//			m_MapWidth = (float)header->Width;					// 地图的宽度
//			m_MapHeight= (float)header->Height;					// 地图的高度
//			m_SubMapWidth = header->SubWidth;			// 子地图的宽度
//			m_SubMapHeight = header->SubHeight;			// 子地图的高度
//			m_PointWidth = header->PointWidth;			// 坐标的宽度
//			m_PointHeight = header->PointHeight;			// 坐标的高度
//
//			m_Reserved=header->Reserved;					// 保留
//			m_UnitIndexOffset=header->UnitIndexOffset;	// 单元的引索位置
//			m_UnitIndexNum=header->UnitIndexNum;			// 单元的引索数量
//			m_IndexOffset=header->IndexOffset;			// 引索位置(未知部分)
//			m_IndexNum=header->IndexNum;					// 引索数量(未知部分)
//			delete [] header;
//		}
//
//		if (m_FileType == 5)
//		{
//			m_SubMapWidth = 400;
//			m_SubMapHeight = 320;
//			Rol0Header *header = new Rol0Header[1];
//			ZeroMemory(header,sizeof(Rol0Header));
//			infile.read((char*)header,sizeof(Rol0Header));
//			m_FileFlag=header->Flag;						// 文件标志
//			m_Reserved=header->Reserved;					// 保留
//			m_MapWidth = (float)header->Width;					// 地图的宽度
//			m_MapHeight= (float)header->Height;					// 地图的高度
//			m_SubMapWidth = header->SubWidth;			// 子地图的宽度
//			m_SubMapHeight = header->SubHeight;			// 子地图的高度
//			m_UnitIndexNum=header->UnitIndexNum;			// 单元的引索数量
//		}
//
//		// 注：因为有些地图的尺寸并一定可以被小地图尺寸整除，所以需要趋向最大取整
//		m_SubMapRowNum=(uint32)ceil((float)(m_MapHeight/m_SubMapHeight)); // 计算子地图中的行数量
//		m_SubMapColNum=(uint32)ceil((float)(m_MapWidth/m_SubMapWidth)); // 计算子地图中的列数量
//		m_SubMapTotal=m_SubMapRowNum*m_SubMapColNum; // 计算地图中总的子地图数量
//		m_UnitIndexNum = m_SubMapTotal;
//
//		// 读取单元偏移值列表
//		m_UnitOffsetList=new uint32[m_UnitIndexNum]; // 自动分配列表空间
//		infile.read((char*)m_UnitOffsetList, sizeof(uint32) * m_SubMapTotal); // 读取列表
//
//		// 仅大话3地图使用
//		if ((m_FileType == 3) | (m_FileType == 4))
//		{
//			// 读取未知部分偏移值列表
//			m_OffsetList=new uint32[m_IndexNum]; // 分配(未知部分)的列表空间
//			infile.read((char*)m_OffsetList, sizeof(uint32) * m_IndexNum); // 读取列表(未知部分)
//		}
//	}
//	else
//	{
//		cerr << filename << ": Map File Format Error!" << endl;
//		exit(EXIT_FAILURE); // 退出
//	}
//
//	if (m_FileType == 1)
//	{
//		//ReadJPGH(&infile); // 读取JPGH的数据
//	}
//
//	if ((m_FileType == 2) | (m_FileType == 3) | (m_FileType == 4))
//	{
//		//ReadHEAD(&infile); // 读取新地图的数据
//	}
//
//	if (m_FileType == 5)
//	{
//		// 此格式无需处理
//	}
//	infile.close(); // 关闭文件
//	return true;
//}
//
//// 读取旧地图JPGH的数据
//bool ReadGameMap::ReadJPGH(ifstream *file)
//{	
//	UnitHeader JpegHead;
//	uint32 FileSize = 0; // 文件大小
//	file->read((char*)&FileSize,sizeof(uint32));
//	file->read((char *)&JpegHead,sizeof(JpegHead)); // 读取单元头的数据
//
//	// 判断标志是否正确(HGPJ)
//	if (JpegHead.Flag!=0x4A504748)
//	{
//		printf("JPEG HEADER 标志错误。\n");
//		return false;
//	}
//	m_jpgh.Data = new uint8[JpegHead.Size]; // 分配单元数据的内存空间
//	m_jpgh.Size=JpegHead.Size;
//	file->read((char*)m_jpgh.Data,JpegHead.Size);
//	return true;
//}
//
//// 读取新地图HEAD的数据
//bool ReadGameMap::ReadHEAD(ifstream *file)
//{	
//	uint32 HeadOffset = 0; // HEAD的偏移位置值
//	file->read((char*)&HeadOffset,sizeof(uint32));
//	uint32 HeaderSize;
//
//	HeaderSize=m_UnitOffsetList[0]-HeadOffset; // 计算地图头数据的大小
//
//	m_head.Size=HeaderSize;
//	m_head.Data = new uint8[HeaderSize];
//	file->read((char*)m_head.Data,sizeof(uint8)); // 读取地图头数据
//	return true;
//}
//
//// 读取地图的单元数据
//bool ReadGameMap::ReadUnit(uint32 UnitNum)
//{
//	ifstream file;
//	locale::global(locale(""));//将全局区域设为操作系统默认区域
//	file.open(m_FileName.c_str(), ios::in|ios::binary);
//	locale::global(locale("C"));//还原全局区域设定
//	long seek;			// 跳转地址
//	bool Result = true;		// 结果
//	bool loop=true;		// 是否循环
//	m_MaskTemp=1;
//
//	m_isImag=false;
//	m_isMask=false;
//	m_isJpeg=false;
//	m_isBlok=false;
//	m_isCell=false;
//	m_isBrig=false;
//	m_isLigt=false;
//
//	seek=m_UnitOffsetList[UnitNum];
//	file.seekg(seek); // 跳转到单元开始的位置
//	
//	if ((m_FileType == 1) | (m_FileType == 2))
//	{
//		uint32 Num = 0; // 单元开始的头4个字节
//		file.read((char*)&Num,sizeof(uint32));
//		m_UnitHeadData = new uint32[Num];
//		for (int i=0;i<Num;i++)
//		{
//			file.read((char*)&m_UnitHeadData[i],sizeof(uint32));
//		}
//	}
//
//
//	UnitHeader *unit = new UnitHeader[1];
//	ZeroMemory(unit,sizeof(UnitHeader));
//
//	while(loop)
//	{
//		file.read((char*)unit,sizeof(UnitHeader));
//		printf("unit->Flag: %x\n",unit->Flag );
//		switch(unit->Flag)
//		{
//			// GAMI "47 414D 49"
//		case 0x494D4147:
//			Result=ReadIMAG(&file,unit->Flag,unit->Size);
//			break;
//
//			// 2KSM "32 4B 53 4D"
//		case 0x4D534B32:
//			Result=ReadMASK(&file,unit->Flag,unit->Size);
//			break;
//			// KSAM "4B 53 41 4D"
//		case 0x4D41534B:
//			Result=ReadMASK(&file,unit->Flag,unit->Size);
//			break;
//
//			// GEPJ "47 45 50 4A"
//		case 0x4A504547:
//			Result=ReadJPEG(&file,unit->Flag,unit->Size);
//
//			if (m_FileFlag==0x524F4C30) // 是否为ROL文件
//			{
//				loop=false;
//			}
//
//			break;
//
//			// KOLB "4B 4F 4C 42"
//		case 0x424C4F4B:
//			Result=ReadBLOK(&file,unit->Flag,unit->Size);
//			break;
//
//			// LLEC "4C 4C 45 43"
//		case 0x43454C4C:
//			Result=ReadCELL(&file,unit->Flag,unit->Size);
//			break;
//
//			// GIRB "47 49 52 42"
//		case 0x42524947:
//			Result=ReadBRIG(&file,unit->Flag,unit->Size);
//			break;
//
//			// TGIL "54 47 49 4C"
//		case 0x4C494754:
//			Result=ReadLIGT(&file,unit->Flag,unit->Size);
//			break;
//
//			//  DNE "20 44 4E 45"
//		case 0x454E4420:
//			Result=ReadEND(&file,unit->Flag,unit->Size);
//			loop=false;
//			break;
//
//			// 默认处理
//		default:
//			// 错误标志
//			m_ErrorUnit.Flag=unit->Flag;
//			m_ErrorUnit.Size=unit->Size;
//			loop=false;
//			break;
//		}
//	}
//
//	file.close(); // 关闭MAP文件
//	return Result;
//}
//
//// 释放地图单元的内存空间
//bool ReadGameMap::ReleaseUnit()
//{
//	if (m_isImag)
//	{
//		m_imag.Data = NULL;
//		delete[] ((uint8*)m_imag.Data);
//	}
//	if (m_isJpeg)
//	{
//		m_jpeg.Data = NULL;
//		delete[] ((uint8*)m_jpeg.Data); // 释放JPEG的内存空间
//	}
//	if (m_isCell)
//	{
//		m_cell.Data = NULL;
//		delete[] ((uint8*)m_cell.Data); // 释放CELL的内存空间
//	}
//	if (m_isMask)
//	{
//		//mask处理麻烦些
//		delete[] m_mask[0].Data;
//	}
//	if (m_isBlok)
//	{
//		m_blok.Data = NULL;
//		delete[] ((uint8*)m_blok.Data);
//	}
//	if (m_isBrig)
//	{
//		m_brig.Data = NULL;
//		delete[] ((uint8*)m_brig.Data);
//	}
//	if (m_isLigt)
//	{
//		m_ligt.Data = NULL;
//		delete[] ((uint8*)m_ligt.Data); // 释放LIGT的内存空间
//	}
//
//	return true;
//}
//
//// 获得地图宽度
//uint32 ReadGameMap::GetMapWidth()
//{
//	return (uint32)m_MapWidth;
//}
//
//// 获得地图高度
//uint32 ReadGameMap::GetMapHeight()
//{
//	return (uint32)m_MapHeight;
//}
//
//// 获得子地图的宽度
//uint32 ReadGameMap::GetSubMapWidth()
//{
//	return (uint32)m_SubMapWidth;
//}
//
//// 获得子地图的高度
//uint32 ReadGameMap::GetSubMapHeight()
//{
//	return (uint32)m_SubMapHeight;
//}
//
//// 获得坐标的宽度
//uint32 ReadGameMap::GetPointWidth()
//{
//	return m_PointWidth;
//}
//
//// 获得坐标的高度
//uint32 ReadGameMap::GetPointHeight()
//{
//	return m_PointHeight;
//}
//
//// 获得地图的行数
//uint32 ReadGameMap::GetSubMapRowNum()
//{
//	return m_SubMapRowNum;
//}
//
//// 获得地图的列数
//uint32 ReadGameMap::GetSubMapColNum()
//{
//	return m_SubMapColNum;
//}
//
//// 获得子地图的总数量
//uint32 ReadGameMap::GetSubMapTotal()
//{
//	return m_SubMapTotal;
//}
//
//// 获得子地图中Mask的总数
//uint32 ReadGameMap::GetMaskTotal()
//{
//	return m_MaskNum;
//}
//
//// 获得ROL0单元数据
//bool ReadGameMap::ReadROLO(ifstream *file, uint32 Size)
//{
//	if (m_FileFlag==0x524F4C30) // 是否为ROL文件
//	{
//		m_isJpeg = true;
//		m_jpeg.Data = new uint8[Size]; // 分配单元数据的内存空间
//		//fread(m_jpeg.Data,Size,1,fp); // 读取单元JPEG的数据
//		m_jpeg.Size = Size;
//		return true;
//	}
//	return false;
//}
//
//// 读取地图IMAG的数据
//bool ReadGameMap::ReadIMAG(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x494D4147)
//	{
//		m_isImag = true;
//		m_imag.Data = new uint8[Size]; // 分配单元数据的内存空间
//		file->read((char*)m_imag.Data,Size);// 读取单元IMAG的数据
//		m_imag.Size=Size;
//	}
//	else
//	{
//		printf("IMAG标志错误！\n");
//		m_isImag = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图MASK的数据
//bool ReadGameMap::ReadMASK(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x4D41534B || Flag==0x4D534B32)
//	{
//		// 这个处理可能存在问题,缺少循环标志
//		m_isMask = true;
//		if ((m_FileType == 1) | (m_FileType == 2))
//		{
//			m_mask[0].Data = new uint8[Size]; // 分配单元数据的内存空间
//			file->read((char*)m_mask[0].Data,Size);// 读取单元IMAG的数据
//			m_mask[0].Size=Size;
//		}
//		if ((m_FileType == 3) | (m_FileType == 4))
//		{
//			for (int i=0;i<Size;i++)
//			{
//				m_mask[i].Data = new uint8[4];
//				file->read((char*)m_mask[i].Data,4);
//			}
//		}
//		
//	}
//	else
//	{
//		printf("MASK标志错误！\n");
//		m_isMask = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图JPEG的数据
//bool ReadGameMap::ReadJPEG(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x4A504547)
//	{
//		m_isJpeg = true;
//		m_jpeg.Data = new uint8[Size]; // 分配单元数据的内存空间
//		file->read((char*)m_jpeg.Data,Size);// 读取单元JPEG的数据
//		m_jpeg.Size=Size;
//	}
//	else
//	{
//		printf("JPEG标志错误！\n");
//		m_isJpeg = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图BLOK的数据
//bool ReadGameMap::ReadBLOK(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x424C4F4B)
//	{
//		m_isBlok = true;
//		m_blok.Data = new uint8[Size]; // 分配单元数据的内存空间
//		file->read((char*)m_blok.Data,Size); // 读取单元BLOK的数据
//		m_blok.Size=Size;
//	}
//	else
//	{
//		printf("BLOK标志错误！\n");
//		m_isBlok = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图CELL的数据
//bool ReadGameMap::ReadCELL(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x43454C4C)
//	{
//		m_isCell = true;
//		m_cell.Data = new uint8[Size]; // 分配单元数据的内存空间
//		file->read((char*)m_cell.Data,Size); // 读取单元CELL的数据
//		m_cell.Size=Size;
//	}
//	else
//	{
//		printf("CELL标志错误！\n");
//		m_isCell = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图BRIG的数据
//bool ReadGameMap::ReadBRIG(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x42524947)
//	{
//		m_isBrig = true;
//		m_brig.Data = new uint8[Size]; // 分配单元数据的内存空间
//		file->read((char*)m_brig.Data,Size);
//		m_brig.Size=Size;
//	}
//	else
//	{
//		printf("BRIG标志错误！\n");
//		m_isCell = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图LIGT的数据
//bool ReadGameMap::ReadLIGT(ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x4C494754)
//	{
//		m_isLigt = true;
//		m_ligt.Data = new uint8[Size]; // 分配单元数据的内存空间
//		file->read((char*)m_ligt.Data,Size); // 读取单元JPEG的数据
//		m_ligt.Size=Size;
//	}
//	else
//	{
//		printf("LIGT标志错误！\n");
//		m_isLigt = false;
//		return false;
//	}
//	return true;
//}
//
//// 读取地图END 的数据
//bool ReadGameMap::ReadEND (ifstream *file, uint32 Flag, uint32 Size)
//{
//	if (Flag==0x454E4420)
//	{
//		// 不需要处理数据
//	}
//	else
//	{
//		printf("END 标志错误！\n");
//		return false;
//	}
//	return true;
//}
//
//
//// 读取HEAD的数据
//MapData ReadGameMap::GetHeadData()
//{
//	return m_head;
//}
//
//// 读取JPEG的数据
//MapData ReadGameMap::GetJpegData()
//{
//	return m_jpeg;
//}
//
//
//// 读取MASK的数据
//MapData ReadGameMap::GetMaskData(uint8 ID)
//{
//	return m_mask[ID];
//}
//
//// 读取CELL的数据
//MapData ReadGameMap::GetCellData()
//{
//	return m_cell;
//}
//
//// 读取BRIG的数据
//MapData ReadGameMap::GetBrigData()
//{
//	return m_brig;
//}
//
//// 2字节高低位调换
//void ByteSwap(uint16& value)
//{
//	uint16 tempvalue = value >> 8;
//	value = (value << 8) | tempvalue;
//}
//
//
//// 地图的JPEG数据处理器
//uint8* MapHandler(uint8* Buffer, uint32 inSize, uint32* outSize)
//{
//	// JPEG数据处理原理
//	// 1、复制D8到D9的数据到缓冲区中
//	// 2、删除第3、4个字节 FFA0
//	// 3、修改FFDA的长度00 09 为 00 0C
//	// 4、在FFDA数据的最后添加00 3F 00
//	// 5、替换FFDA到FF D9之间的FF数据为FF 00
//
//	uint32 TempNum = 0;						// 临时变量，表示已读取的长度
//	uint8* outBuffer;
//	uint8* TempBuffer = new uint8[inSize*2];		// 临时变量，表示处理后的数据
//	memset(TempBuffer,0,inSize*2);
//	outBuffer = TempBuffer;					// 已处理数据的开始地址
//	uint16 TempTimes = 0;					// 临时变量，表示循环的次数
//	uint32 Temp = 0;
//
//	// 当已读取数据的长度小于总长度时继续
//	while(TempNum < inSize && *Buffer++==0xFF)
//	{
//		*TempBuffer++=0xFF;
//		TempNum++;
//		switch(*Buffer)
//		{
//		case 0xD8:
//			*TempBuffer++=0xD8;
//			*Buffer++;
//			TempNum++;
//			break;
//		case 0xA0:
//			*Buffer++;
//			TempBuffer--;
//			TempNum++;
//			break;
//		case 0xC0:
//			*TempBuffer++=0xC0;
//			*Buffer++;
//			TempNum++;
//
//			memcpy(&TempTimes,Buffer,sizeof(uint16)); // 读取长度
//			ByteSwap(TempTimes); // 将长度转换为Intel顺序
//
//
//			for(int i=0;i< TempTimes;i++)
//			{
//				*TempBuffer++=*Buffer++;
//				TempNum++;
//			}
//
//			break;
//		case 0xC4:
//			*TempBuffer++=0xC4;
//			*Buffer++;
//			TempNum++;
//
//			memcpy(&TempTimes,Buffer,sizeof(uint16)); // 读取长度
//			ByteSwap(TempTimes); // 将长度转换为Intel顺序
//
//			for(int i=0;i< TempTimes;i++)
//			{
//				*TempBuffer++=*Buffer++;
//				TempNum++;
//			}
//			break;
//		case 0xDB:
//			*TempBuffer++=0xDB;
//			*Buffer++;
//			TempNum++;
//
//			memcpy(&TempTimes,Buffer,sizeof(uint16)); // 读取长度
//			ByteSwap(TempTimes); // 将长度转换为Intel顺序
//
//			for(int i=0;i< TempTimes;i++)
//			{
//				*TempBuffer++=*Buffer++;
//				TempNum++;
//			}
//			break;
//		case 0xDA:
//			*TempBuffer++=0xDA;
//			*TempBuffer++=0x00;
//			*TempBuffer++=0x0C;
//			*Buffer++;
//			TempNum++;
//
//			memcpy(&TempTimes,Buffer,sizeof(uint16)); // 读取长度
//			ByteSwap(TempTimes); // 将长度转换为Intel顺序
//			*Buffer++;
//			TempNum++;
//			*Buffer++;
//
//			for(int i=2;i< TempTimes;i++)
//			{
//				*TempBuffer++=*Buffer++;
//				TempNum++;
//			}
//			*TempBuffer++=0x00;
//			*TempBuffer++=0x3F;
//			*TempBuffer++=0x00;
//			Temp += 1; // 这里应该是+3的，因为前面的0xFFA0没有-2，所以这里只+1。
//
//			// 循环处理0xFFDA到0xFFD9之间所有的0xFF替换为0xFF00
//			for (;TempNum < inSize-2;)
//			{
//				if (*Buffer==0xFF)
//				{
//					*TempBuffer++=0xFF;
//					*TempBuffer++=0x00;
//					*Buffer++;
//					TempNum++;	
//					Temp ++;
//				}
//				else
//				{
//					*TempBuffer++=*Buffer++;
//					TempNum++;
//				}
//			}
//			// 直接在这里写上了0xFFD9结束Jpeg图片.
//			Temp--; // 这里多了一个字节，所以减去。
//			*TempBuffer--;
//			*TempBuffer--=0xD9;
//			break;
//		case 0xD9:
//			// 算法问题，这里不会被执行，但结果一样。
//			*TempBuffer++=0xD9;
//			TempNum++;
//			break;
//		default:
//			break;
//		}
//	}
//	Temp+=inSize;
//	*outSize=Temp;
//	return outBuffer;
//}
//
//
//int main(){
//	ReadGameMap *map = new ReadGameMap();
//	string filename ="1001.map";
//	cout<<filename<<endl;
//	map->LoadMap(filename);
//	uint32 UnitTotal=map->GetSubMapTotal();				// 地图的单元总数
//	uint32 m_MapWidth=map->GetMapWidth();				// 地图的宽度
//	uint32 m_MapHeight=map->GetMapHeight();				// 地图的高度
//	uint32 m_SubMapWidth=map->GetSubMapWidth();			// 子地图的宽度
//	uint32 m_SubMapHeight=map->GetSubMapHeight();		// 子地图的高度
//	uint32 m_SubMapRowNum=map->GetSubMapRowNum();		// 子地图的行数量
//	uint32 m_SubMapColNum=map->GetSubMapColNum();		// 子地图的列数量
//	uint32 m_SubMapTotal=map->GetSubMapTotal();			// 子地图的总数
//
//	uint32 bmpsize = m_SubMapWidth*m_SubMapHeight*m_SubMapTotal; // 得到大地图的像素大小
//	uint16 *m_BmpData = new uint16[bmpsize];
//	
//	// 循环处理所有的地图单元
//	for (uint32 i=0; i< UnitTotal%37; i++)
//	{	
//		MapData jd;
//		map->ReadUnit(i); // 读取i单元的数据到内存
//		jd=map->GetJpegData(); // 从内存中读取JPEG的数据
//
//		uint32 TempSize = 0;
//		uint8* jpgdata;
//
//
//		// 处理地图JPEG数据为标准的JPEG数据
//		jpgdata	= MapHandler(jd.Data,jd.Size,&TempSize);
//		
//		int ss=i;
//	    char temp[64];
//		sprintf(temp, "filename%d.jpg", ss);
//		string jpgname(temp);
//
//		ofstream of(jpgname,ios::out|ios::binary);
//		of.write((char*)jpgdata,TempSize);
//		 cout<<TempSize<<endl;
//		of.close();
//		
//
//	}
//	
//	return 0;
//}