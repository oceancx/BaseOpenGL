#pragma once

#include <string>
#include <cstdio>

#include "basetype.h"

class CWDF
{
public:
    CWDF(void);
    ~CWDF(void);
    
    typedef  char* CString;
    typedef char** CStringList;
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
    
    struct HEADER_XML
    {
        HEADER Header; // WDF文件头指针
        
        uint32 Type; // 包裹的类型
        uint32 Size; // 包裹大小
        char Hash[16]; // 包裹的散列
        char Name[20]; // 包裹的名字
        char Desc[512]; // 包裹的描述
    };
    
    struct FILELIST_XML
    {
        FILELIST FileList; // 文件列表的指针
        
        unsigned char Key; // WDFH 文件解码Key
        char Name[20]; // 中文名字
        char Path[260]; // 路径
        char Desc[512]; // 描述
    };
    
    struct HEADER_DAT
    {
        uint32 Flag; // 文件标签
        uint32 Type; // 游戏类型 0:无、1:梦幻、 2:大话2、 3:大话3、 4:大话外传
        uint32 Number; // 文件数量
        uint32 Finish; // 已完成数量
        uint32 Offset; // 偏移值
        char Name[20]; // 包裹名字
    };
    
    struct FILELIST_DAT
    {
        uint32 Type; // 完成类型
        uint32 Hash; // 散列
        char Path[260]; // 路径名
    };
    
    char* m_GameName; // 游戏名称
    uint32 m_GameType; // 游戏类型
    uint32 m_FileType; // 文件类型
    HEADER *m_Header; // WDF文件头
    uint32 m_Flag;
    uint32 m_Number;
    uint32 m_Offset;
    
    FILELIST *m_FileList; // WDF文件列表
    bool isWriteXml; // 是否要写XML文件
    bool isUnpack; // 是否解包文件
    bool isFileExist; // 文件是否存在
    bool isLstFile; // 是否使用LST文件
    bool isDefFile; // 是否使用默认LST文件
    bool isWriteDat; // 是否要写DAT文件
    
    //HEADER_XML *m_HeaderXml; // XML的文件头
    //FILELIST_XML *m_FileListXml; // XML的文件列表
    
    uint32 GetGameType(char* path); // 获得游戏的
    CStringList* GetWdfList(char* path); // 获得WDF文件的列表
    CStringList* m_WdfFileList;
    CString GetFileName(); // 获得文件名
    char m_WdfFileName[256]; // WDF的文件
    //char[] m_XmlFileName; // XML的文件名
    char m_OutFileName[256]; // 输出的文件名
    char m_FileName[256]; // 仅含文件名字
    
    void SetIsUnPack(bool b);
    void SetIsXmlFile(bool b);
    void SetIsFileExist(bool b);
    void SetIsDefFile(bool b);
    void SetIsDatFile(bool b);
    
    void OpenWdf(char* path,char* filename, char* DstPath); // 打开WDF文件
    void GetHeader(FILE * file); // 获得WDF文件头数据
    void GetFileList(FILE* file); // 获得WDF文件列表的数据
    void SaveXml(); // 保存成XML文件
    
    void DecodeList(char* Data, int Size);
    unsigned char DecodeData(char* Data, int Size);
    unsigned long string_id(char *str);
    char *string_adjust(char *p);
    
    bool BrowseFile(char* strFile, char* strFilter,CStringList *pFileList, CStringList *pFileNameList, CStringList *pShowNameList);//查找文件函数
    bool FileExist(char* strFileName); // 判断文件是否存在
    bool FolderExists(char* s); // 判断目录是否存在
    bool SuperMkDir(char* P); // 创建多层目录
    
};
