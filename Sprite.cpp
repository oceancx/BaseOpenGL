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
#include "Sprite.h"

Sprite::Sprite(void)
{
    m_HeadLen = 0;
    m_HeadGroup = 0;
    m_HeadFrame = 0;
    m_HeadWidth = 0;
    m_HeadHeight = 0;
    m_HeadKey_X = 0;
    m_HeadKey_Y = 0;
    
    m_FrameKey_X = 0;
    m_FrameKey_Y = 0;
    m_FrameWidth = 0;
    m_FrameHeight = 0;
}

Sprite::~Sprite(void)
{
}

// 16bit 565Type Alpha 混合
uint16 Sprite::Alpha565(uint16 Src, uint16 Des, uint8 Alpha)
{
    uint16 Result;
    // 混合后的颜色=( ( A-B ) * Alpha ) >> 5 + B
    // 混合后的颜色 = ( A * Alpha + B * ( 32-Alpha ) ) / 32
    
    unsigned short R_Src,G_Src,B_Src;
    R_Src=G_Src=B_Src=0;
    
    R_Src = Src & 0xF800;
    G_Src = Src & 0x07E0;
    B_Src = Src & 0x001F;
    
    R_Src = R_Src >> 11;
    G_Src = G_Src >> 5;
    
    unsigned short R_Des,G_Des,B_Des;
    R_Des=G_Des=B_Des=0;
    
    R_Des = Des & 0xF800;
    G_Des = Des & 0x07E0;
    B_Des = Des & 0x001F;
    
    R_Des = R_Des >> 11;
    G_Des = G_Des >> 5;
    
    unsigned short R_Res,G_Res,B_Res;
    R_Res=G_Res=B_Res=0;
    
    R_Res = ((R_Src-R_Des)*Alpha)>>5+R_Des;
    G_Res = ((G_Src-G_Des)*Alpha)>>5+G_Des;
    B_Res = ((B_Src-B_Des)*Alpha)>>5+B_Des;
    
    //	R_Res = (R_Src*Alpha + R_Des*(32-Alpha)) >> 5;
    //	G_Res = (G_Src*Alpha + G_Des*(32-Alpha)) >> 5;
    //	B_Res = (B_Src*Alpha + B_Des*(32-Alpha)) >> 5;
    
    R_Res = R_Res << 11;
    G_Res = G_Res << 5;
    
    Result = R_Res|G_Res|B_Res;
    
    return Result;
}

void Sprite::OpenSpriteFile(const string &filename)
{
    HEADER header;
    
    // 打开精灵动画文件
    ifstream file(filename.c_str(), ios::in|ios::binary);
    
    // 判断文件是否打开
    if(!file)
    {
        cerr << "Can't open Sprite File \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }
    
    // 读取精灵动画的文件头数据
    file.read((char*)&header,sizeof(header));
    m_HeadLen = header.HeadLen;
    m_HeadGroup = header.Group;
    m_HeadFrame = header.Frame;
    m_HeadWidth = header.Width;
    m_HeadHeight = header.Height;
    m_HeadKey_X = header.Key_X;
    m_HeadKey_Y = header.Key_Y;
    
    // 判断精灵文件标志是否为"SP"
    if(header.Flag!=0x5053)
    {
        cerr << "Sprite File Flag Error!" << endl;
        exit(EXIT_FAILURE);
    }
    
    // 判断精灵文件头长度是否为12
    if (header.HeadLen!=12)
    {
        // 读取附加文件头数据
        int AddonHeadLen = header.HeadLen - 12 ;
        m_AddonHead = new uint8[AddonHeadLen]; // 分配附加文件头的空间
        file.read((char*)m_AddonHead,AddonHeadLen); // 读取附加文件头
        //cout << "AddonHeadLen= " << AddonHeadLen << endl;
        //cout << "m_AddonHead= " ;
        //PrintHex(m_AddonHead,AddonHeadLen);
    }
    
    // 读取调色板数据
    m_Palette = new uint16[256]; // 分配16bit调色板的空间
    m_Palette32 = new PIXEL[256]; // 分配32bit调色板的空间
    file.read((char*)&m_Palette[1],256*2); // Palette[0]不使用
    for (int k = 1; k <= 256; k++)
    {
        m_Palette32[k]=RGB565to888(m_Palette[k],0xff); // 16to32调色板转换
        /*
         cout << "m_Palette16["<< k <<"]=";
         PrintHex((void*)&m_Palette[k],2);
         cout << "m_Palette32["<< k <<"]=";
         PrintHex((void*)&m_Palette32[k],4);
         */
        
    }
    
    // 读取帧引索列表
    int Frames = header.Group*header.Frame;
    m_FrameIndex = new uint32[Frames]; // 分配帧引索列表的空间
    file.read((char*)&m_FrameIndex[1],Frames*4); // 读取帧引索列表
    // 	cout << "Frames:" << Frames << endl;
    // 	for (int k=1; k<= Frames; k++)
    // 	{
    // 		cout << "m_FrameIndex[" << k << "]:" << m_FrameIndex[k] << endl;
    // 	}
    // 	cout << endl;
    //
    
    //
    // 循环帧处理
    //
    uint32 pixels = header.Width * header.Height; // 计算总像素值
    m_BmpBuffer = new PIXEL[pixels]; // 分配位图空间
    m_pBmpBuffer = m_BmpBuffer;
    memset(m_BmpBuffer,0,pixels*4);
    m_Offset = 2+2+header.HeadLen; // 相对偏移值
    
    m_FrameLine = new uint32[header.Height]; // 分配行引索列表的空间
    m_LineData = new uint8[header.Width*4]; // 分配行数据的空间
    
    int x = 0; // 动作组号
    int z = 0; // 动作帧数
    int index = 0; // 文件名结束偏移值
    string strName = ""; // 文件名
    index = filename.find_last_of('.');
    strName = filename.substr(0,index);
    
    FRAME frame;
    for (int i=1; i<= Frames; i++)
    {
        // 跳转到帧的开始位置
        m_BmpBuffer = (PIXEL*)m_pBmpBuffer;
        memset(m_BmpBuffer,0,pixels*4);
        file.seekg(m_FrameIndex[i] + m_Offset); // 跳转到帧开始的位置
        
        // 读取帧的头数据
        file.read((char*)&frame,sizeof(FRAME));
        m_FrameKey_X = frame.Key_X;
        m_FrameKey_Y = frame.Key_Y;
        m_FrameWidth = frame.Width;
        m_FrameHeight = frame.Height;
        
        // 			cout << "frame.Key_X: " << frame.Key_X << endl;
        // 			cout << "frame.Key_Y: " << frame.Key_Y << endl;
        // 			cout << "frame.Width: " << frame.Width << endl;
        // 			cout << "frame.Height: " << frame.Height << endl;
        
        uint32 FrameSize = GetHeadWidth() * GetHeadHeight(); // 计算精灵的总像素
        m_BmpBuffer += FrameSize; // 跳转到图片缓冲的最后位置
        PIXEL *bmp_temp=m_BmpBuffer; // 定义一个临时变量，用来保存图片的最后位置
        
        // 读取帧数据块的引索
        file.read((char*)&m_FrameLine[1],frame.Height*4);
        // 			cout << "frame= " << i << endl;
        // 			for(int k=1; k<= frame.Height; k++)
        // 			{
        // 				cout << "m_FrameLine["<< k <<"]: " << m_FrameLine[k] << endl;
        // 			}
        
        
        //
        // 循环处理行的数据
        //
        for (int j=1; j <= frame.Height; j++)
        {
            m_BmpBuffer = bmp_temp - (GetHeadWidth() * j); // 将行的像素按顺序来存
            int LineDataLen=0;
            if(j < frame.Height)
            {
                LineDataLen = m_FrameLine[j+1] - m_FrameLine[j]; // 得到行数据的大小
            }
            else
            {
                LineDataLen = m_FrameIndex[i+1] - (m_FrameIndex[i]+m_FrameLine[j]);
            }
            
            file.seekg(m_FrameIndex[i]+m_Offset+m_FrameLine[j]);
            //cout << "Offset: " << m_FrameIndex[i]+m_Offset+m_FrameLine[j] << endl;
            //memset(m_LineData,0,frame.Width);
            file.read((char*)m_LineData,LineDataLen);
            //cout << "[" << j << ":" << LineDataLen << "] ";
            //PrintHex(m_LineData,LineDataLen);
            DataHandler((char*)m_LineData);
        }
        
        char *temp = new char[256];
        sprintf(temp,"%s%0.1d%0.3d.tga",strName.c_str(),x,z); // 设置输出文件名字
        
        // 修改组号和帧数的值
        if (i < (x+1) * header.Frame)
        {
            z++;
        }
        else
        {
            z = 0;
            x++;
        }
        
        outfilename = (string)temp;
        //printf("%s\nX=%d\tY=%d\n\n",temp,m_FrameKey_X,m_FrameKey_Y);
        SaveImageFile(outfilename);
        delete(temp);
    }
    file.close();
    //cout << "Test succeed!!!" << endl;
}

void Sprite::SaveImageFile(const string &filename)
{
    TGA_FILE_HEADER TgaHeader;
    memset(&TgaHeader,0,18);
    TgaHeader.IdLength=0;			// 图像信息字段(默认:0)
    TgaHeader.ColorMapType=0;		// 颜色标的类型(默认0)
    TgaHeader.ImageType=0x02;			// 图像类型码(支持2或10)
    TgaHeader.ColorMapFirstIndex=0;	// 颜色表的引索(默认:0)
    TgaHeader.ColorMapLength=0;		// 颜色表的长度(默认:0)
    TgaHeader.ColorMapEntrySize=0;	// 颜色表表项的为数(默认:0，支持16/24/32)
    TgaHeader.XOrigin=0;				// 图像X坐标的起始位置(默认:0)
    TgaHeader.YOrigin=0;				// 图像Y坐标的起始位置(默认:0)
    TgaHeader.ImageWidth=GetHeadWidth();			// 图像的宽度
    TgaHeader.ImageHeight=GetHeadHeight();			// 图像的高度
    TgaHeader.PixelDepth=32;			// 图像每像素存储占用位数
    TgaHeader.ImageDescruptor=8;		// 图像描述字符字节(默认:0)
    
    ofstream ofile;
    ofile.open(filename.c_str(), ios::out|ios::trunc|ios::binary);
    //cout << "写TGA图像文件头" << endl;
    ofile.write((char*)(&TgaHeader),sizeof(TGA_FILE_HEADER)); // 写TGA的文件头
    //cout << "图像文件头写完成，开始写图像数据。" << endl;
    ofile.write((char*)m_pBmpBuffer,GetHeadWidth()*GetHeadHeight()*4);
    cout << "完成 " << filename << " 帧图片输出~" << endl;
    ofile.close();
}

void Sprite::DataHandler(char *pData)
{
    PIXEL temp_pixel;
    temp_pixel.A=0;
    temp_pixel.R=0;
    temp_pixel.G=0;
    temp_pixel.B=0;
    
    uint32 Pixels = 0;
    uint32 PixelLen = GetHeadWidth();
    uint16 AlphaPixel = 0;
    
    Pixels = GetHeadKey_X() - GetFrameKey_X(); // 确定列的位置
    m_BmpBuffer+=Pixels;
    m_BmpBuffer-=(GetHeadKey_Y()-GetFrameKey_Y())*GetHeadWidth(); // 确定行的位置
    while (*pData != 0) // {00000000} 表示像素行结束，如有剩余像素用透明色代替
    {
        uint8 style=0;
        uint8 Level=0; // Alpha层数
        uint8 Repeat=0; // 重复次数
        style = (*pData & 0xc0) >> 6; // 取字节的前两个比特
        switch(style)
        {
            case 0: // {00******}
                if(*pData & 0x20) // {001*****} 表示带有Alpha通道的单个像素
                {
                    // {001 +5bit Alpha}+{1Byte Index}, 表示带有Alpha通道的单个像素。
                    // {001 +0~31层Alpha通道}+{1~255个调色板引索}
                    Level = (*pData) & 0x1f; // 0x1f=(11111) 获得Alpha通道的值
                    pData++; // 下一个字节
                    if(Pixels <= PixelLen)
                    {
                        AlphaPixel = Alpha565(m_Palette[(uint8)*pData+1],0,Level); // 混合
                        *m_BmpBuffer = RGB565to888(AlphaPixel,Level*8);
                        //*m_BmpBuffer = RGB565to888(m_Palette[(uint8)*pData+1],Level*8);
                        //m_Palette32[(unsigned char)*pData].A = Level<<2;
                        //*m_BmpBuffer = m_Palette32[(unsigned char)*pData+1];
                        m_BmpBuffer++;
                        Pixels++;
                        pData++;
                    }
                }
                else // {000*****} 表示重复n次带有Alpha通道的像素
                {
                    // {000 +5bit Times}+{1Byte Alpha}+{1Byte Index}, 表示重复n次带有Alpha通道的像素。
                    // {000 +重复1~31次}+{0~255层Alpha通道}+{1~255个调色板引索}
                    // 注: 这里的{00000000} 保留给像素行结束使用，所以只可以重复1~31次。
                    Repeat = (*pData) & 0x1f; // 获得重复的次数
                    pData++;
                    Level=*pData; // 获得Alpha通道值
                    pData++;
                    for(int i = 1; i <= Repeat; i++)
                    {
                        if(Pixels <= PixelLen)
                        {
                            AlphaPixel = Alpha565(m_Palette[(uint8)*pData+1],0,Level); // 混合
                            *m_BmpBuffer = RGB565to888(AlphaPixel,Level*8);
                            //*m_BmpBuffer = RGB565to888(m_Palette[(uint8)*pData+1],Level*8);
                            //m_Palette32[(unsigned char)*pData].A = Level<<2;
                            //*m_BmpBuffer = m_Palette32[(unsigned char)*pData];
                            m_BmpBuffer++;
                            Pixels++;
                        }
                    }
                    pData++;
                }
                break;
            case 1: // {01******} 表示不带Alpha通道不重复的n个像素组成的数据段
                // {01  +6bit Times}+{nByte Datas},表示不带Alpha通道不重复的n个像素组成的数据段。
                // {01  +1~63个长度}+{n个字节的数据},{01000000}保留。
                Repeat = (*pData) & 0x3f; // 获得数据组中的长度
                pData++;
                for(int i = 1; i <= Repeat; i++)
                {
                    if(Pixels <= PixelLen)
                    {
                        //m_Palette32[(unsigned char)*pData].A = 0xFF; // 设置为不透明
                        *m_BmpBuffer = m_Palette32[(uint8)*pData+1];
                        m_BmpBuffer++;
                        Pixels++;
                        pData++;
                    }
                }
                break;
            case 2: // {10******} 表示重复n次像素
                // {10  +6bit Times}+{1Byte Index}, 表示重复n次像素。
                // {10  +重复1~63次}+{0~255个调色板引索},{10000000}保留。
                Repeat = (*pData) & 0x3f; // 获得重复的次数
                pData++;
                for(int i = 1; i <= Repeat; i++)
                {
                    if(Pixels <= PixelLen)
                    {
                        //m_Palette32[(unsigned char)*pData].A = 0xFF; // 设置为不透明
                        *m_BmpBuffer = m_Palette32[(uint8)*pData+1];
                        m_BmpBuffer++;
                        Pixels++;
                    }
                }
                pData++;
                break;
            case 3: // {11******} 表示跳过n个像素，跳过的像素用透明色代替
                // {11  +6bit Times}, 表示跳过n个像素，跳过的像素用透明色代替。
                // {11  +跳过1~63个像素},{11000000}保留。
                Repeat = (*pData) & 0x3f; // 获得重复次数
                for (int i=1; i <= Repeat; i++)
                {
                    if(Pixels <= PixelLen)
                    {
                        *m_BmpBuffer = temp_pixel; // 假设默认透明色为0x0000
                        m_BmpBuffer++;
                        Pixels++;
                    }
                }
                pData++;
                break;
            default: // 一般不存在这种情况
                cerr << "Error!" << endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
    if (*pData == 0)
    {
        uint8 Repeat=0;
        Repeat = PixelLen - Pixels;
        for (int i=0; i < Repeat; i++)
        {
            if(Pixels <= PixelLen)
            {
                *m_BmpBuffer = temp_pixel; // 假设默认透明色为0x0000
                m_BmpBuffer++;
                Pixels++;
            }
        }
    }
}

void Sprite::PrintHex(void *ptr, int count)
{
    for(int i=0; i<count; i++)
    {
        printf("%.2X ", *((unsigned char*)ptr+i));
    }
    printf("\n");
}

Sprite::PIXEL Sprite::RGB565to888(unsigned short color, uint8 Alpha)
{
    PIXEL pixel;
    
    unsigned int r = (color >> 11) & 0x1f;
    unsigned int g = (color >>  5) & 0x3f;
    unsigned int b = (color      ) & 0x1f;
    
    pixel.A = Alpha;
    pixel.R = (r << 3) | (r >> 2);    
    pixel.G = (g << 2) | (g >> 4);
    pixel.B = (b << 3) | (b >> 2);
    
    
    /*
     uint16 R,G,B;
     R=G=B=0;
     
     R = color & 0xF800;
     G = color & 0x07E0;
     B = color & 0x001F;
     
     R = R >> 11;
     G = G >> 5;
     
     pixel.A = Alpha;
     pixel.R = R*8; // R*8    
     pixel.G = G*4; // G*4
     pixel.B = B*8; // B*8
     */
    
    return pixel;
}

uint16 Sprite::GetHeadLen()
{
    return m_HeadLen;
}

uint16 Sprite::GetHeadGroup()
{
    return m_HeadGroup;
}

uint16 Sprite::GetHeadFrame()
{
    return m_HeadFrame;
}

uint16 Sprite::GetHeadWidth()
{
    return m_HeadWidth;
}

uint16 Sprite::GetHeadHeight()
{
    return m_HeadHeight;
}

uint16 Sprite::GetHeadKey_X()
{
    return m_HeadKey_X;
}

uint16 Sprite::GetHeadKey_Y()
{
    return m_HeadKey_Y;
}

uint16 Sprite::GetFrameKey_X()
{
    return m_FrameKey_X;
}

uint16 Sprite::GetFrameKey_Y()
{
    return m_FrameKey_Y;
}

uint16 Sprite::GetFrameWidth()
{
    return m_FrameWidth;
}

uint16 Sprite::GetFrameHeight()
{
    return m_FrameHeight;
}