//#pragma once
//#import <msxml3.dll>
//using namespace MSXML2;
//
//class CWDF
//{
//public:
//    CWDF(void);
//    ~CWDF(void);
//    
//    typedef unsigned int uint32;
//    struct HEADER
//    {
//        uint32 Flag; // 包裹的标签
//        uint32 Number; // 包裹中的文件数量
//        uint32 Offset; // 包裹中的文件列表偏移位置
//    };
//    
//    struct FILELIST
//    {
//        uint32 Hash; // 文件的名字散列
//        uint32 Offset; // 文件的偏移
//        uint32 Size; // 文件的大小
//        uint32 Spaces; // 文件的空间
//    };
//    
//    struct HEADER_XML
//    {
//        HEADER Header; // WDF文件头指针
//        
//        uint32 Type; // 包裹的类型
//        uint32 Size; // 包裹大小
//        char Hash[16]; // 包裹的散列
//        char Name[20]; // 包裹的名字
//        char Desc[512]; // 包裹的描述
//    };
//    
//    struct FILELIST_XML
//    {
//        FILELIST FileList; // 文件列表的指针
//        
//        unsigned char Key; // WDFH 文件解码Key
//        char Name[20]; // 中文名字
//        char Path[260]; // 路径
//        char Desc[512]; // 描述
//    };
//    
//    struct HEADER_DAT
//    {
//        uint32 Flag; // 文件标签
//        uint32 Type; // 游戏类型 0:无、1:梦幻、 2:大话2、 3:大话3、 4:大话外传
//        uint32 Number; // 文件数量
//        uint32 Finish; // 已完成数量
//        uint32 Offset; // 偏移值
//        char Name[20]; // 包裹名字
//    };
//    
//    struct FILELIST_DAT
//    {
//        uint32 Type; // 完成类型
//        uint32 Hash; // 散列
//        char Path[260]; // 路径名
//    };
//    
//    CString m_GameName; // 游戏名称
//    uint32 m_GameType; // 游戏类型
//    uint32 m_FileType; // 文件类型
//    HEADER *m_Header; // WDF文件头
//    uint32 m_Flag;
//    uint32 m_Number;
//    uint32 m_Offset;
//    
//    FILELIST *m_FileList; // WDF文件列表
//    BOOL isWriteXml; // 是否要写XML文件
//    BOOL isUnpack; // 是否解包文件
//    BOOL isFileExist; // 文件是否存在
//    BOOL isLstFile; // 是否使用LST文件
//    BOOL isDefFile; // 是否使用默认LST文件
//    BOOL isWriteDat; // 是否要写DAT文件
//    
//    HEADER_XML *m_HeaderXml; // XML的文件头
//    FILELIST_XML *m_FileListXml; // XML的文件列表
//    
//    uint32 GetGameType(CString path); // 获得游戏的类型
//    CStringList* GetWdfList(CString path); // 获得WDF文件的列表
//    CStringList* m_WdfFileList;
//    CStringList* GetFileName(); // 获得文件名
//    CString m_WdfFileName; // WDF的文件名
//    CString m_XmlFileName; // XML的文件名
//    CString m_OutFileName; // 输出的文件名
//    CString m_FileName; // 仅含文件名字
//    
//    void SetIsUnPack(BOOL b);
//    void SetIsXmlFile(BOOL b);
//    void SetIsFileExist(BOOL b);
//    void SetIsDefFile(BOOL b);
//    void SetIsDatFile(BOOL b);
//    
//    void OpenWdf(CString path, CString filename, CString DstPath); // 打开WDF文件
//    void GetHeader(CFile* file); // 获得WDF文件头数据
//    void GetFileList(CFile* file); // 获得WDF文件列表的数据
//    void SaveXml(); // 保存成XML文件
//    
//    void DecodeList(char *Data, int Size);
//    unsigned char DecodeData(char *Data, int Size);
//    unsigned long string_id(const char *str);
//    char *string_adjust(char *p);
//    
//    BOOL BrowseFile(CString strFile, CString strFilter, CStringList *pFileList, CStringList *pFileNameList, CStringList *pShowNameList);//查找文件函数
//    bool FileExist(CString strFileName); // 判断文件是否存在
//    bool FolderExists(CString s); // 判断目录是否存在
//    bool SuperMkDir(CString P); // 创建多层目录
//    
//    MSXML2::IXMLDOMDocumentPtr pDoc; 
//    MSXML2::IXMLDOMElementPtr  xmlRoot;
//    MSXML2::IXMLDOMProcessingInstructionPtr pIInstruction ;
//};
