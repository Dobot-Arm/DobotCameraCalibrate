#ifndef SMARTCAMERASTRUCT_H
#define SMARTCAMERASTRUCT_H

#include <cstdint>
/*
#pragma pack(1)
.......
#pragma pack()
*/

/*
*相机的数据结构体
*/
struct MaskImageData
{
    int moduleId;//渲染图对应的模块id
    int iWidth; //图像尺寸
    int iHeight; //图像尺寸
    int iImgStep;
    unsigned char* pRenderImage;//渲染图对应的数据
};
struct ImageDataSmart
{
    int iRealWidth; //图像原始尺寸
    int iRealHeight; //图像原始尺寸
    int iWidth; //图像转换后的尺寸
    int iHeight; //图像转换后的尺寸
    int iImgStep;
    unsigned char* pImageData;
    char* pResultInfo; //结果数据，是一个json字符串
    int iMaskImgLen;
    struct MaskImageData* pMaskImg; //渲染图
};

/// \~chinese 设备信息     \~english Device info
typedef struct _MV_VS_DEVICE_INFO_
{
    unsigned short  nMajorVer;                      ///< [OUT] \~chinese GigE协议主要版本  \~english GigE protocol Major Version
    unsigned short  nMinorVer;                      ///< [OUT] \~chinese GigE协议次要版本  \~english GigE protocol Minor Version
    unsigned int    nMacAddrHigh;                   ///< [OUT] \~chinese 高MAC地址         \~english High MAC Address
    unsigned int    nMacAddrLow;                    ///< [OUT] \~chinese 低MAC地址         \~english Low MAC Address

    unsigned int    nIpCfgOption;                   ///< [OUT] \~chinese 支持的IP配置选项，bit31-Static bit30-DHCP bit29-LLA  \~english Supported IP Configuration Options, bit31-Static bit30-DHCP bit29-LLA
    unsigned int    nIpCfgCurrent;                  ///< [OUT] \~chinese 当前IP配置，bit31-Static bit30-DHCP bit29-LLA \~english IP Configuration, bit31-Static bit30-DHCP bit29-LLA
    unsigned int    nCurrentIp;                     ///< [OUT] \~chinese 当前IP地址        \~english Current Ip
    unsigned int    nCurrentSubNetMask;             ///< [OUT] \~chinese 当前子网掩码     \~english Curtent Subnet Mask
    unsigned int    nDefultGateWay;                 ///< [OUT] \~chinese 当前网关         \~english Current Gateway
    unsigned char   chManufacturerName[32];         ///< [OUT] \~chinese 制造商名称       \~english Manufacturer Name
    unsigned char   chModelName[32];                ///< [OUT] \~chinese 型号名称         \~english Model Name
    unsigned char   chDeviceVersion[32];            ///< [OUT] \~chinese 设备版本         \~english Device Version
    unsigned char   chManufacturerSpecificInfo[48]; ///< [OUT] \~chinese 制造商的具体信息 \~english Manufacturer Specific Information
    unsigned char   chSerialNumber[16];             ///< [OUT] \~chinese 序列号           \~english Serial Number
    unsigned char   chUserDefinedName[16];          ///< [OUT] \~chinese 用户自定义名称   \~english User Defined Name
    unsigned int    nNetExport;                     ///< [OUT] \~chinese 与设备连接的网口IP地址   \~english IP address of the network port connected to the device

    unsigned int    nReserved[8];                   ///<       \~chinese 预留             \~english Reserved

}MV_VS_DEVICE_INFO;

#define MV_MAX_XML_SYMBOLIC_NUM     128     ///< \~chinese 最大XML符号数         \~english Maximum XML Symbolic Number

/// \~chinese String类型值     \~english String Value
typedef struct _MV_VS_STRINGVALUE_
{
    unsigned int    nMaxLength;        ///< [OUT] \~chinese 最大长度   \~english Maximum Length
    char            strValue[256];     ///< [OUT] \~chinese 当前值     \~english Current Value

    unsigned int    nReserved[4];      ///<       \~chinese 预留       \~english Reserved

}MV_VS_STRINGVALUE;

/// \~chinese Int类型值    \~english Int Value
typedef struct _MV_VS_INTVALUE_
{
    int64_t         nCurValue;      ///< [OUT] \~chinese 当前值    \~english Current Value
    int64_t         nMax;           ///< [OUT] \~chinese 最大值    \~english Max
    int64_t         nMin;           ///< [OUT] \~chinese 最小值    \~english Min
    int64_t         nInc;           ///< [OUT] \~chinese 增量      \~english Inc

    unsigned int    nReserved[16];  ///<       \~chinese 预留      \~english Reserved

}MV_VS_INTVALUE;

/// \~chinese 枚举类型值     \~english Enumeration Value
typedef struct _MV_VS_ENUMVALUE_T
{
    unsigned int        nCurValue;                              ///< [OUT] \~chinese 当前值               \~english Current Value
    unsigned int        nSupportNum;                            ///< [OUT] \~chinese 数据的有效数据个数   \~english Number of valid data
    unsigned int        nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]; ///< [OUT] \~chinese 支持的枚举值         \~english Support Value

    unsigned int        nReserved[4];                           ///<       \~chinese 预留                 \~english Reserved

}MV_VS_ENUMVALUE;

/// \~chinese Float类型值      \~english Float Value
typedef struct _MV_VS_FLOATVALUE_
{
    float               fCurValue;      ///< [OUT] \~chinese 当前值    \~english Current Value
    float               fMax;           ///< [OUT] \~chinese 最大值    \~english Max
    float               fMin;           ///< [OUT] \~chinese 最小值    \~english Min

    unsigned int        nReserved[4];   ///<       \~chinese 预留      \~english Reserved

}MV_VS_FLOATVALUE;

/// \~chinese 文件存取      \~english File Access
typedef struct _MV_VS_FILE_ACCESS_T
{
    char*           pDevFileName;       ///< [IN]      \~chinese 设备文件名    \~english Device file name
    char*           pFile;              ///< [IN]      \~chinese 文件数据缓存  \~english File Data
    unsigned int    nMaxFileSize;       ///< [IN]      \~chinese 文件缓存大小  \~english File Data Buffer Size
    unsigned int    nOffset;            ///< [IN]      \~chinese 首地址偏移量  \~english Data Offset
    unsigned int    nFileCurLen;        ///< [OUT]     \~chinese 本次写入或读取文件数据长度  \~english File Data Length For This Time
    unsigned int    nFileTotalLen;      ///< [IN][OUT] \~chinese 文件数据长度  \~english File Data Length

    unsigned int    nReserved[32];      ///<           \~chinese 预留          \~english Reserved

}MV_VS_FILE_ACCESS;

//相机设备信息
struct CameraDeviceInfoSmart
{
    char szIdentifyName[256];
    MV_VS_DEVICE_INFO info;
};

struct MyPointSmart //创建点的数据
{
    double x;
    double y;
    double z;
    double rx;
    double ry;
    double rz;
};

struct Point3DSmart //创建点的数据
{
    double x;
    double y;
    double z;
};

struct ErrorValueSmart
{
    double x;
    double y;
    double z;
    double ang0;
    double ang1;
    double ang2;
};


#endif // SMARTCAMERASTRUCT_H
