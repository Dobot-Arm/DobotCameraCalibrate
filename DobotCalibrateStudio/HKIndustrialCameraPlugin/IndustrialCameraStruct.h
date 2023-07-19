#ifndef INDUSTRIALCAMERASTRUCT_H
#define INDUSTRIALCAMERASTRUCT_H

#include <cstdint>
/*
#pragma pack(1)
.......
#pragma pack()
*/

/*
*工业相机的数据结构体
*/
struct ImageDataIndustrial
{
    int iRealWidth; //图像原始尺寸
    int iRealHeight; //图像原始尺寸
    int iWidth;
    int iHeight;
    int iImgStep;
    unsigned char* pImageData;
};

/// \~chinese GigE设备信息              \~english GigE device info
typedef struct _MV_GIGE_DEVICE_INFO_INDUSTRIAL
{
    unsigned int        nIpCfgOption;                               ///< [OUT] \~chinese IP配置选项             \~english IP Configuration Options
    unsigned int        nIpCfgCurrent;                              ///< [OUT] \~chinese 当前IP配置             \~english IP Configuration
    unsigned int        nCurrentIp;                                 ///< [OUT] \~chinese 当前IP地址             \~english Current Ip
    unsigned int        nCurrentSubNetMask;                         ///< [OUT] \~chinese 当前子网掩码           \~english Curtent Subnet Mask
    unsigned int        nDefultGateWay;                             ///< [OUT] \~chinese 当前网关               \~english Current Gateway
    unsigned char       chManufacturerName[32];                     ///< [OUT] \~chinese 制造商名称             \~english Manufacturer Name
    unsigned char       chModelName[32];                            ///< [OUT] \~chinese 型号名称               \~english Model Name
    unsigned char       chDeviceVersion[32];                        ///< [OUT] \~chinese 设备版本               \~english Device Version
    unsigned char       chManufacturerSpecificInfo[48];             ///< [OUT] \~chinese 制造商的具体信息       \~english Manufacturer Specific Information
    unsigned char       chSerialNumber[16];                         ///< [OUT] \~chinese 序列号                 \~english Serial Number
    unsigned char       chUserDefinedName[16];                      ///< [OUT] \~chinese 用户自定义名称         \~english User Defined Name
    unsigned int        nNetExport;                                 ///< [OUT] \~chinese 网口IP地址             \~english NetWork IP Address

    unsigned int        nReserved[4];                               ///<       \~chinese 预留                   \~english Reserved

}MV_GIGE_DEVICE_INFO_INDUSTRIAL;

///< \~chinese 最大的数据信息大小       \~english Maximum data information size
#define INFO_INDUSTRIAL_MAX_BUFFER_SIZE            64

/// \~chinese USB设备信息               \~english USB device info
typedef struct _MV_USB3_DEVICE_INFO_INDUSTRIAL
{
    unsigned char       CrtlInEndPoint;                             ///< [OUT] \~chinese 控制输入端点           \~english Control input endpoint
    unsigned char       CrtlOutEndPoint;                            ///< [OUT] \~chinese 控制输出端点           \~english Control output endpoint
    unsigned char       StreamEndPoint;                             ///< [OUT] \~chinese 流端点                 \~english Flow endpoint
    unsigned char       EventEndPoint;                              ///< [OUT] \~chinese 事件端点               \~english Event endpoint
    unsigned short      idVendor;                                   ///< [OUT] \~chinese 供应商ID号             \~english Vendor ID Number
    unsigned short      idProduct;                                  ///< [OUT] \~chinese 产品ID号               \~english Device ID Number
    unsigned int        nDeviceNumber;                              ///< [OUT] \~chinese 设备索引号             \~english Device Number
    unsigned char       chDeviceGUID[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];         ///< [OUT] \~chinese 设备GUID号             \~english Device GUID Number
    unsigned char       chVendorName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];         ///< [OUT] \~chinese 供应商名字             \~english Vendor Name
    unsigned char       chModelName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];          ///< [OUT] \~chinese 型号名字               \~english Model Name
    unsigned char       chFamilyName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];         ///< [OUT] \~chinese 家族名字               \~english Family Name
    unsigned char       chDeviceVersion[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];      ///< [OUT] \~chinese 设备版本               \~english Device Version
    unsigned char       chManufacturerName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];   ///< [OUT] \~chinese 制造商名字             \~english Manufacturer Name
    unsigned char       chSerialNumber[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];       ///< [OUT] \~chinese 序列号                 \~english Serial Number
    unsigned char       chUserDefinedName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];    ///< [OUT] \~chinese 用户自定义名字         \~english User Defined Name
    unsigned int        nbcdUSB;                                    ///< [OUT] \~chinese 支持的USB协议          \~english Support USB Protocol
    unsigned int        nDeviceAddress;                             ///< [OUT] \~chinese 设备地址               \~english Device Address

    unsigned int        nReserved[2];                               ///<       \~chinese 预留                   \~english Reserved

}MV_USB3_DEVICE_INFO_INDUSTRIAL;

/// \~chinese CameraLink设备信息        \~english CameraLink device info
typedef struct _MV_CamL_DEV_INFO_INDUSTRIAL
{
    unsigned char       chPortID[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];             ///< [OUT] \~chinese 端口号                 \~english Port ID
    unsigned char       chModelName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];          ///< [OUT] \~chinese 型号名字               \~english Model Name
    unsigned char       chFamilyName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];         ///< [OUT] \~chinese 名称                   \~english Family Name
    unsigned char       chDeviceVersion[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];      ///< [OUT] \~chinese 设备版本               \~english Device Version
    unsigned char       chManufacturerName[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];   ///< [OUT] \~chinese 制造商名字             \~english Manufacturer Name
    unsigned char       chSerialNumber[INFO_INDUSTRIAL_MAX_BUFFER_SIZE];       ///< [OUT] \~chinese 序列号                 \~english Serial Number

    unsigned int        nReserved[38];                              ///<       \~chinese 预留                   \~english Reserved

}MV_CamL_DEV_INFO_INDUSTRIAL;


///< \~chinese 设备传输层协议类型       \~english Device Transport Layer Protocol Type
#define MV_UNKNOW_DEVICE_INDUSTRIAL 0x00000000 ///< \~chinese 未知设备类型，保留意义       \~english Unknown Device Type, Reserved
#define MV_GIGE_DEVICE_INDUSTRIAL 0x00000001   ///< \~chinese GigE设备                     \~english GigE Device
#define MV_1394_DEVICE_INDUSTRIAL 0x00000002   ///< \~chinese 1394-a/b 设备                \~english 1394-a/b Device
#define MV_USB_DEVICE_INDUSTRIAL 0x00000004    ///< \~chinese USB 设备                     \~english USB Device
#define MV_CAMERALINK_DEVICE_INDUSTRIAL 0x00000008  ///< \~chinese CameraLink设备               \~english CameraLink Device

/// \~chinese 设备信息                  \~english Device info
typedef struct _MV_CC_DEVICE_INFO_INDUSTRIAL
{
    unsigned short          nMajorVer; ///< [OUT] \~chinese 主要版本               \~english Major Version
    unsigned short          nMinorVer; ///< [OUT] \~chinese 次要版本               \~english Minor Version
    unsigned int            nMacAddrHigh; ///< [OUT] \~chinese 高MAC地址              \~english High MAC Address
    unsigned int            nMacAddrLow; ///< [OUT] \~chinese 低MAC地址              \~english Low MAC Address
    unsigned int            nTLayerType; ///< [OUT] \~chinese 设备传输层协议类型     \~english Device Transport Layer Protocol Type

    unsigned int            nReserved[4]; ///<       \~chinese 预留                   \~english Reserved

    union
    {
        MV_GIGE_DEVICE_INFO_INDUSTRIAL stGigEInfo; ///< [OUT] \~chinese GigE设备信息           \~english GigE Device Info
        MV_USB3_DEVICE_INFO_INDUSTRIAL stUsb3VInfo; ///< [OUT] \~chinese USB设备信息            \~english USB Device Info
        MV_CamL_DEV_INFO_INDUSTRIAL    stCamLInfo; ///< [OUT] \~chinese CameraLink设备信息     \~english CameraLink Device Info
        // more ...
    }SpecialInfo;

}MV_CC_DEVICE_INFO_INDUSTRIAL;

//相机设备信息
struct CameraDeviceInfoIndustrial
{
    char szIdentifyName[256];
    MV_CC_DEVICE_INFO_INDUSTRIAL info;
};

struct MyPointIndustrial //创建点的数据
{
    double x;
    double y;
    double z;
    double rx;
    double ry;
    double rz;
};

struct Point3DIndustrial //创建点的数据
{
    double x;
    double y;
    double z;
};

struct ErrorValueIndustrial
{
    double x;
    double y;
    double z;
    double ang0;
    double ang1;
    double ang2;
};


/// \~chinese 采集模式                  \~english Acquisition mode
typedef enum _MV_CAM_ACQUISITION_MODE_
{
    MV_ACQ_MODE_SINGLE                  = 0,                        ///< \~chinese 单帧模式                     \~english Single Mode
    MV_ACQ_MODE_MUTLI                   = 1,                        ///< \~chinese 多帧模式                     \~english Multi Mode
    MV_ACQ_MODE_CONTINUOUS              = 2,                        ///< \~chinese 持续采集模式                 \~english Continuous Mode

}MV_CAM_ACQUISITION_MODE;

/// \~chinese 增益模式                  \~english Gain Mode
typedef enum _MV_CAM_GAIN_MODE_
{
    MV_GAIN_MODE_OFF                    = 0,                        ///< \~chinese 关闭                         \~english Single Mode
    MV_GAIN_MODE_ONCE                   = 1,                        ///< \~chinese 一次                         \~english Multi Mode
    MV_GAIN_MODE_CONTINUOUS             = 2,                        ///< \~chinese 连续                         \~english Continuous Mode

}MV_CAM_GAIN_MODE;

/// \~chinese 曝光模式                  \~english Exposure Mode
typedef enum _MV_CAM_EXPOSURE_MODE_
{
    MV_EXPOSURE_MODE_TIMED              = 0,                        ///< \~chinese 时间                         \~english Timed
    MV_EXPOSURE_MODE_TRIGGER_WIDTH      = 1,                        ///< \~chinese 触发脉冲宽度                 \~english TriggerWidth
}MV_CAM_EXPOSURE_MODE;

/// \~chinese 自动曝光模式              \~english Auto Exposure Mode
typedef enum _MV_CAM_EXPOSURE_AUTO_MODE_
{
    MV_EXPOSURE_AUTO_MODE_OFF           = 0,                        ///< \~chinese 关闭                         \~english Off
    MV_EXPOSURE_AUTO_MODE_ONCE          = 1,                        ///< \~chinese 一次                         \~english Once
    MV_EXPOSURE_AUTO_MODE_CONTINUOUS    = 2,                        ///< \~chinese 连续                         \~english Continuous

}MV_CAM_EXPOSURE_AUTO_MODE;

/// \~chinese 触发模式                  \~english Trigger Mode
typedef enum _MV_CAM_TRIGGER_MODE_
{
    MV_TRIGGER_MODE_OFF                 = 0,                        ///< \~chinese 关闭                         \~english Off
    MV_TRIGGER_MODE_ON                  = 1,                        ///< \~chinese 打开                         \~english ON

}MV_CAM_TRIGGER_MODE;

/// \~chinese Gamma选择器               \~english Gamma Selector
typedef enum _MV_CAM_GAMMA_SELECTOR_
{
    MV_GAMMA_SELECTOR_USER              = 1,                        ///< \~chinese 用户                         \~english Gamma Selector User
    MV_GAMMA_SELECTOR_SRGB              = 2,                        ///< \~chinese sRGB                         \~english Gamma Selector sRGB

}MV_CAM_GAMMA_SELECTOR;

/// \~chinese 白平衡                    \~english White Balance
typedef enum _MV_CAM_BALANCEWHITE_AUTO_
{
    MV_BALANCEWHITE_AUTO_OFF            = 0,                        ///< \~chinese 关闭                         \~english Off
    MV_BALANCEWHITE_AUTO_ONCE           = 2,                        ///< \~chinese 一次                         \~english Once
    MV_BALANCEWHITE_AUTO_CONTINUOUS     = 1,                        ///< \~chinese 连续                         \~english Continuous

}MV_CAM_BALANCEWHITE_AUTO;

/// \~chinese 触发源                    \~english Trigger Source
typedef enum _MV_CAM_TRIGGER_SOURCE_
{
    MV_TRIGGER_SOURCE_LINE0             = 0,                        ///< \~chinese Line0                        \~english Line0
    MV_TRIGGER_SOURCE_LINE1             = 1,                        ///< \~chinese Line1                        \~english Line1
    MV_TRIGGER_SOURCE_LINE2             = 2,                        ///< \~chinese Line2                        \~english Line2
    MV_TRIGGER_SOURCE_LINE3             = 3,                        ///< \~chinese Line3                        \~english Line3
    MV_TRIGGER_SOURCE_COUNTER0          = 4,                        ///< \~chinese Conuter0                     \~english Conuter0

    MV_TRIGGER_SOURCE_SOFTWARE          = 7,                        ///< \~chinese 软触发                       \~english Software
    MV_TRIGGER_SOURCE_FrequencyConverter= 8,                        ///< \~chinese 变频器                       \~english Frequency Converter

}MV_CAM_TRIGGER_SOURCE;

/// \~chinese 最大XML符号数             \~english Max XML Symbolic Number
#define MV_MAX_XML_SYMBOLIC_NUM         64
/// \~chinese 枚举类型值                \~english Enumeration Value
typedef struct _MVCC_ENUMVALUE_T
{
    unsigned int        nCurValue;                                  ///< [OUT] \~chinese 当前值                 \~english Current Value
    unsigned int        nSupportedNum;                              ///< [OUT] \~chinese 数据的有效数据个数     \~english Number of valid data
    unsigned int        nSupportValue[MV_MAX_XML_SYMBOLIC_NUM];     ///< [OUT] \~chinese 支持的枚举值           \~english Support Value

    unsigned int        nReserved[4];                               ///<       \~chinese 预留                   \~english Reserved

}MVCC_ENUMVALUE;
/// \~chinese Int类型值Ex               \~english Int Value Ex
typedef struct _MVCC_INTVALUE_EX_T
{
    int64_t             nCurValue;                                  ///< [OUT] \~chinese 当前值                 \~english Current Value
    int64_t             nMax;                                       ///< [OUT] \~chinese 最大值                 \~english Max
    int64_t             nMin;                                       ///< [OUT] \~chinese 最小值                 \~english Min
    int64_t             nInc;                                       ///< [OUT] \~chinese Inc                    \~english Inc

    unsigned int        nReserved[16];                              ///<       \~chinese 预留                   \~english Reserved

}MVCC_INTVALUE_EX;
/// \~chinese Float类型值               \~english Float Value
typedef struct _MVCC_FLOATVALUE_T
{
    float               fCurValue;                                  ///< [OUT] \~chinese 当前值                 \~english Current Value
    float               fMax;                                       ///< [OUT] \~chinese 最大值                 \~english Max
    float               fMin;                                       ///< [OUT] \~chinese 最小值                 \~english Min

    unsigned int        nReserved[4];                               ///<       \~chinese 预留                   \~english Reserved

}MVCC_FLOATVALUE;

/// \~chinese String类型值              \~english String Value
typedef struct _MVCC_STRINGVALUE_T
{
    char                chCurValue[256];                            ///< [OUT] \~chinese 当前值                 \~english Current Value

    int64_t             nMaxLength;                                 ///< [OUT] \~chinese 最大长度               \~english MaxLength
    unsigned int        nReserved[2];                               ///<       \~chinese 预留                   \~english Reserved

}MVCC_STRINGVALUE;

#endif // INDUSTRIALCAMERASTRUCT_H
