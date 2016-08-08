/*********************************************************************************************
 *                            《大话西游II》《梦幻西游》《大话西游3》
 *                                        精灵动画文件格式
 *---------------------------------------------------------------------------------------------
 *                                        版本 1.0.0 release
 *
 *                                  王大理 <e-mail:wdl@sina.com>
 *                                         <QQ:DaliStudio@QQ.com>
 *
 *                                      2004年05月11日 创建
 *                                      2010年02月02日 更新
 *---------------------------------------------------------------------------------------------
 * 声明：
 *     本源代码应用于网易公司的网络游戏《大话西游II》《梦幻西游》《大话西游3》等游戏精灵动画文
 * 件格式的读写。与此源代码相应的文件格式版权可能属于云风工作室或网易公司所有。
 *     此源代码应用于教育目的，禁止用于商业目的，以及其他任何损害他人利益的地方，否则后果自负，
 * 本源代码作者不承担任何责任。如有异议请勿使用本源代码，并永久删除此源代码。
 *---------------------------------------------------------------------------------------------
 *                         版权所有(c) 2003-2010 王大理 ， 保留所有权利。
 *********************************************************************************************/
#pragma once


#include <string>
#include <iostream>
#include <fstream>
#include "basetype.h"
#include <vector>
using namespace std; // 使用标准命名空间



class Sprite
{
public:
    Sprite(void);
public:
    ~Sprite(void);
    
private:
    
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
    
    // 精灵动画的文件头
    struct HEADER
    {
        uint16 Flag;		// 精灵文件标志 SP 0x5053
        uint16 HeadLen;		// 文件头的长度 默认为 12
        uint16 Group;		// 精灵图片的组数，即方向数
        uint16 Frame;		// 每组的图片数，即帧数
        uint16 Width;		// 精灵动画的宽度，单位像素
        uint16 Height;		// 精灵动画的高度，单位像素
        uint16 Key_X;		// 精灵动画的关键位X
        uint16 Key_Y;		// 精灵动画的关键位Y
    };
    
    // 帧的文件头
    struct FRAME
    {
        uint32 Key_X;			// 图片的关键位X
        uint32 Key_Y;			// 图片的关键位Y
        uint32 Width;			// 图片的宽度，单位像素
        uint32 Height;		// 图片的高度，单位像素
    };
    
    // 像素
    struct PIXEL
    {
        uint8 B; // 蓝色
        uint8 G; // 绿色
        uint8 R; // 红色
        uint8 A; // 通道
    };
    
    uint16 m_HeadLen; // 文件头的长度
    uint16 m_HeadGroup; // 精灵方向的数量
    uint16 m_HeadFrame; // 每方向的帧数量
    uint16 m_HeadWidth; // 精灵的宽度
    uint16 m_HeadHeight; // 精灵的高度
    uint16 m_HeadKey_X; // 精灵的关键位X
    uint16 m_HeadKey_Y; // 精灵的关键位Y
    
    uint16 m_FrameWidth; // 帧的宽度
    uint16 m_FrameHeight; // 帧的高度
    uint16 m_FrameKey_X; // 帧的关键位X
    uint16 m_FrameKey_Y; // 帧的关键位Y
    
    uint32 m_Offset; // 偏移值
    uint8 *m_AddonHead; // 附加头
    uint16 *m_Palette;	// 256色调色板(16bit)
    PIXEL *m_Palette32; // 256色调色板(32bit)
    uint32 *m_FrameIndex; // 每帧的位置索引
    uint32 *m_FrameLine; // 图片每行的数据块位置索引
    uint8 *m_LineData; // 行的数据内容
    PIXEL *m_BmpBuffer; // 位图缓冲区
    void *m_pBmpBuffer; // 位图缓冲区开始位置指针
    string outfilename ; // 位图输出的文件名
    
public:
    void PrintHex(void *ptr, int count); // 输出十六进制值
    void OpenSpriteFile(const string &filename); // 打开精灵动画文件
    void SaveImageFile(const string &filename); // 保存到图像文件
    void DataHandler(char *pData); // 行数据的处理
    
    PIXEL RGB565to888(unsigned short color, uint8 Alpha); // 565转888
    uint16 Alpha565(uint16 Src, uint16 Des, uint8 Alpha); // 16bit 565Type Alpha 混合
    uint16 GetHeadLen(); // 获得文件头的长度
    uint16 GetHeadGroup(); // 获得方向数
    uint16 GetHeadFrame(); // 获得帧数
    uint16 GetHeadWidth(); // 获得宽度
    uint16 GetHeadHeight(); // 获得高度
    uint16 GetHeadKey_X(); // 获得关键位X
    uint16 GetHeadKey_Y(); // 获得关键位Y
    
    uint16 GetFrameWidth(); // 获得帧的宽度
    uint16 GetFrameHeight(); // 获得帧的高度
    uint16 GetFrameKey_X(); // 获得帧的关键位X
    uint16 GetFrameKey_Y(); // 获得帧的关键位Y
};
