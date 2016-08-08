#pragma once


//========= 定义数据类型 ==========
typedef long long			int64;
typedef unsigned long long	uint64;
typedef int					int32;
typedef unsigned int		uint32;
typedef short				int16;
typedef unsigned short		uint16;
typedef char				int8;
typedef unsigned char		uint8;
//=================================


namespace WDF{
	
	struct HEADER
	{
       uint32 Flag; // 包裹的标签
       uint32 Number; // 包裹中的文件数量
	   uint32 Offset; // 包裹中的文件列表偏移位置
	};

	struct FILELIST
	{
		uint32 Hash; // 文件的名字散列
		uint32 Offset; // 文件的偏移
	    uint32 Size; // 文件的大小	
		uint32 Spaces; // 文件的空间
	};

}
