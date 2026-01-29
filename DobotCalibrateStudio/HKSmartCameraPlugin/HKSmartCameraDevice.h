#ifndef HKSMARTCAMERADEVICE_H
#define HKSMARTCAMERADEVICE_H

#include "SmartCameraStruct.h"
#include "CameraInfo.h"

#include <QObject>
#include <QList>
#include <QImage>
#include <functional>
#include <QLibrary>
#include <mutex>
#include <QMap>
#include <QSize>

class HKSmartCameraDevice : public QObject
{
    Q_OBJECT
public:
    explicit HKSmartCameraDevice(QObject *parent = nullptr);
    ~HKSmartCameraDevice();

    void setVideoImageDataCallback(const std::function<void(const ProjectResultInfo&)>& callback);

    int getErrCode() const{return m_iErrCode;};
    QString getErrMessage() const{return m_strErrMsg;};
    bool search(QList<CameraInfo>& retInfo);
    bool setCameraIp(const QString& strConnect,const MyCameraIpInfo& info);
    bool openCamera(const QString& strConnect, const QString& strPwd);
    void closeCamera();
    bool startVideo();
    bool startTestVideo(int iModuleId);
    void stopVideo();
    bool takePhoto(ProjectResultInfo& info);
    bool takeBasePhoto(ProjectResultInfo& info, int iModuleId);
    QList<MyPointF6D> getCalibratePos(const MyPointF3D& flangleCenter, const MyPointF6D& robotPos);
    bool calcGetCalibrateResult(MyPointF6D& avgValue, MyPointF6D& maxValue);
    bool generateCalibrateFile(const QString& strSaveFileFullName);
    bool createUserCoordinate(const QString& strCalibrateFile, const MyPointF6D& robotPos,
                              const double qrCodeSquare,MyPointF6D& coordinatePos, int& iId,
                              ProjectResultInfo& picture);
    bool beginCalibrate();
    int endCalibrate();
    bool calibrateSampling(const MyPointF6D& robotPos, ProjectResultInfo& picture);
    bool updateCalibrateSampling(const MyPointF6D& robotPos, int idxUpdate, ProjectResultInfo& picture);

    /* 该接口在相机登录时调用一次即可，因为属性类型信息不会变的。
     * QMap<xml中的Name字段，也就是属性参数名
     *     MyVsXmlAttribute信息
     * >
    */
    bool getCameraXmlAttribute(QMap<QString,MyVsXmlAttribute>& attributeType);

    /*获取模块翻译的文件数据,该接口在相机登录时调用一次即可，因为名称中途没法改变。
    ** QMap<模块名称
    **      模块对应的显示名称
    **      >
    */
    bool getModuleTranslate(QMap<QString, MyModuleTranslate>& translate);

    /*
     * 判断一个点是否是显示的，记得在调用这个接口前，先
     * SetIntValue("ModuleID", _ttoi64(strModuleID));
    */
    bool getNodeIsVisible(const MyVsXmlAttribute& xmlAttribute);

    //万能通用魔法函数
    bool GetIntValue(const QString& strKey, MV_VS_INTVALUE& stIntValue);
    bool SetIntValue(const QString& strKey, int64_t nValue);
    bool GetEnumValue(const QString& strKey, MV_VS_ENUMVALUE& stEnumValue);
    bool SetEnumValue(const QString& strKey, unsigned int nValue);
    bool SetEnumValueByString(const QString& strKey, const QString& strValue);
    bool GetFloatValue(const QString& strKey, MV_VS_FLOATVALUE& stFloatValue);
    bool SetFloatValue(const QString& strKey, float fValue);
    bool GetBoolValue(const QString& strKey, bool& bValue);
    bool SetBoolValue(const QString& strKey, bool bValue);
    bool GetStringValue(const QString& strKey, MV_VS_STRINGVALUE& stStringValue);
    bool SetStringValue(const QString& strKey, const QString& strValue);
    bool SetCommandValue(const QString& strKey);
    bool FileAccessRead(QByteArray& fileData, const char* pszDevFile);
    bool FileAccessRead(QIODevice& file, const char* pszDevFile);
    bool FileAccessWrite(const QByteArray& fileData, const char* pszDevFile);
    bool FileAccessWrite(QIODevice& file, const char* pszDevFile);

    /*
     * 升级固件，获取固件当前升级进度
    */
    bool updateFirmware(const QString& strFile); //会阻塞直到升级完毕
    bool getUpdateFirmwareProgress(unsigned int& nProgress);

    /*
    **功能：将文件内容格式化为海康相机能够识别的yaml格式文件，同时也是为了校验文件格式是否合法
    **参数：strSrcFile-原文件，可以是 json格式、yml格式、xml格式
    **     strDestFile-新的文件，通常格式是yml
    **     strErrMsg-返回错误信息，
    **返回值：true表示成功，false表示失败
    */
    bool Format2Yaml(const QString& strSrcFile, const QString& strDestFile);

    /*功能：点复用算法计算相关接口
    **说明：偷个懒，函数参数要注意数组的严格控制，内部就不处理了，认为参数是对的。
    **    1. oldPoint长度为6，分别表示x,y,z,Rx,Ry,Rz
    **    2. toolRT和coordRT长度为16，分别表示4*4的矩阵
    */
    bool GetToolTransformation(const double oldPoint[6], const double newPoint[6], double outPoint[16]);
    bool GetAxisTransformation(const double oldPoint[4][6], const double newPoint[4][6],double outPoint[16]);
    bool GetReusePoint(const double oldPoint[6], const QList<double>& toolRT,
                    const QList<double>& coordRT,double outPoint[6]);

private:
    friend void HKSmartVideoCallback(const ImageDataSmart* pData, void* pArgs);

    void initLib();
    void uninitLib();
    bool IsDeviceAccessible(const QString& strIdetify); //判断设备是否可以被连接

    bool FileAccessRead(MV_VS_FILE_ACCESS& stFileAccess, int& nRetCode);
    bool FileAccessWrite(MV_VS_FILE_ACCESS& stFileAccess);
    bool GetGenICamXML(unsigned char* pBuffer, unsigned int nBufferSize, unsigned int* pRetDataSize);

private:
    std::mutex m_mtxEventVideoImage;
    std::function<void(const ProjectResultInfo&)> m_OnEventVideoImage;

    int m_iErrCode;
    QString m_strErrMsg;

    /*搜索相机时，可能会在这一刻搜索不到，但是下一刻却又能搜索到，而前端会按照搜索不到来判断相机是否掉线，为了减少这种误报，所以加个缓存。
     * 当连续超过3次搜索不到，则认为是相机掉线了
    */
    QList<CameraInfo> m_cameraCacheInfo;
    int m_iSearchFailTryTimes = 0;

    /*******************************************************/
    QLibrary m_lib;
    void* m_pHandler;

#define HKICD_FUNC_PTR_DEF(retType,funcName) typedef retType (*pfn##funcName)
#define HKICD_FUNC_PTR_MEMBER(funcName) pfn##funcName m_pfn##funcName

    HKICD_FUNC_PTR_DEF(void*,CreateCamera)(const char* pszMvDll);
    HKICD_FUNC_PTR_MEMBER(CreateCamera);

    HKICD_FUNC_PTR_DEF(void,DestroyCamera)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(DestroyCamera);

    HKICD_FUNC_PTR_DEF(int,GetErrCode)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(GetErrCode);

    HKICD_FUNC_PTR_DEF(void,GetErrMsg)(void* pHandler, char* pszMsg);
    HKICD_FUNC_PTR_MEMBER(GetErrMsg);

    HKICD_FUNC_PTR_DEF(int,SearchCamera)(void* pHandler, CameraDeviceInfoSmart info[256]);
    HKICD_FUNC_PTR_MEMBER(SearchCamera);

    HKICD_FUNC_PTR_DEF(int,IsDeviceAccessible)(void* pHandler, const char* pszIdentifyName);
    HKICD_FUNC_PTR_MEMBER(IsDeviceAccessible);

    HKICD_FUNC_PTR_DEF(int,SetDeviceIpConfig)(void* pHandler, const char* pszIdentifyName, const char* pszIp,
                                        const char* pszSubNetMask, const char* pszDefultGateWay);
    HKICD_FUNC_PTR_MEMBER(SetDeviceIpConfig);

    HKICD_FUNC_PTR_DEF(int,ConnectCamera)(void* pHandler, const char* pszIdentifyName, const char* pszPwd);
    HKICD_FUNC_PTR_MEMBER(ConnectCamera);

    HKICD_FUNC_PTR_DEF(void,DisconnectCamera)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(DisconnectCamera);

    HKICD_FUNC_PTR_DEF(int,StartCamera)(void* pHandler, void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(StartCamera);

    HKICD_FUNC_PTR_DEF(int,StartTestCamera)(void* pHandler, int iModuleId, void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(StartTestCamera);

    HKICD_FUNC_PTR_DEF(void,StopCamera)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(StopCamera);

    HKICD_FUNC_PTR_DEF(int,TakePhoto)(void* pHandler, void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(TakePhoto);

    HKICD_FUNC_PTR_DEF(int,TakeBasePhoto)(void* pHandler, int iModuleId, void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(TakeBasePhoto);

    HKICD_FUNC_PTR_DEF(void,BeginCalibrate)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(BeginCalibrate);

    HKICD_FUNC_PTR_DEF(int,EndCalibrate)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(EndCalibrate);

    HKICD_FUNC_PTR_DEF(int,GetCalibratePos)(void* pHandler,const Point3DSmart* pFlangleCenter,
                                      const MyPointSmart* pRobotPos,MyPointSmart retPos[], int iRetPosSize);
    HKICD_FUNC_PTR_MEMBER(GetCalibratePos);

    HKICD_FUNC_PTR_DEF(int,CalibrateSampling)(void* pHandler, const MyPointSmart* pRobotPos,
                                        void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(CalibrateSampling);

    HKICD_FUNC_PTR_DEF(int,UpdateCalibrateSampling)(void* pHandler, const MyPointSmart* pRobotPos,int iUpdateIndex,
                                        void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(UpdateCalibrateSampling);

    HKICD_FUNC_PTR_DEF(int,CalcGetCalibrateResult)(void* pHandler, ErrorValueSmart* pAvgValue, ErrorValueSmart* pMmaxValue);
    HKICD_FUNC_PTR_MEMBER(CalcGetCalibrateResult);

    HKICD_FUNC_PTR_DEF(int,GenerateCalibrateFile)(void* pHandler, const char* pszSaveFileFullName);
    HKICD_FUNC_PTR_MEMBER(GenerateCalibrateFile);

    HKICD_FUNC_PTR_DEF(int,CreateUserCoordinate)(void* pHandler, const char* pszFileFullName,
                                           const MyPointSmart* pRobotPos,const double qrCodeSquare,
                                           MyPointSmart* pUserCoordinate, int* pId,
                                           void(*pfnCallback)(const ImageDataSmart* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(CreateUserCoordinate);

    HKICD_FUNC_PTR_DEF(int,GetIntValue)(void* pHandler, const char* pszKey, MV_VS_INTVALUE* pstIntValue);
    HKICD_FUNC_PTR_MEMBER(GetIntValue);

    HKICD_FUNC_PTR_DEF(int,SetIntValue)(void* pHandler, const char* pszKey, int64_t nValue);
    HKICD_FUNC_PTR_MEMBER(SetIntValue);

    HKICD_FUNC_PTR_DEF(int,GetEnumValue)(void* pHandler, const char* pszKey, MV_VS_ENUMVALUE* pstEnumValue);
    HKICD_FUNC_PTR_MEMBER(GetEnumValue);

    HKICD_FUNC_PTR_DEF(int,SetEnumValue)(void* pHandler, const char* pszKey, unsigned int nValue);
    HKICD_FUNC_PTR_MEMBER(SetEnumValue);

    HKICD_FUNC_PTR_DEF(int,SetEnumValueByString)(void* pHandler, const char* pszKey, const char* pszValue);
    HKICD_FUNC_PTR_MEMBER(SetEnumValueByString);

    HKICD_FUNC_PTR_DEF(int,GetFloatValue)(void* pHandler, const char* pszKey, MV_VS_FLOATVALUE* pstFloatValue);
    HKICD_FUNC_PTR_MEMBER(GetFloatValue);

    HKICD_FUNC_PTR_DEF(int,SetFloatValue)(void* pHandler, const char* pszKey, float fValue);
    HKICD_FUNC_PTR_MEMBER(SetFloatValue);

    HKICD_FUNC_PTR_DEF(int,GetBoolValue)(void* pHandler, const char* pszKey, bool* pbValue);
    HKICD_FUNC_PTR_MEMBER(GetBoolValue);

    HKICD_FUNC_PTR_DEF(int,SetBoolValue)(void* pHandler, const char* pszKey, bool bValue);
    HKICD_FUNC_PTR_MEMBER(SetBoolValue);

    HKICD_FUNC_PTR_DEF(int,GetStringValue)(void* pHandler, const char* pszKey, MV_VS_STRINGVALUE* pstStringValue);
    HKICD_FUNC_PTR_MEMBER(GetStringValue);

    HKICD_FUNC_PTR_DEF(int,SetStringValue)(void* pHandler, const char* pszKey, const char* pszValue);
    HKICD_FUNC_PTR_MEMBER(SetStringValue);

    HKICD_FUNC_PTR_DEF(int,CommandExecute)(void* pHandler, const char* pszKey);
    HKICD_FUNC_PTR_MEMBER(CommandExecute);

    HKICD_FUNC_PTR_DEF(int,FileAccessRead)(void* pHandler, MV_VS_FILE_ACCESS* pstFileAccess);
    HKICD_FUNC_PTR_MEMBER(FileAccessRead);

    HKICD_FUNC_PTR_DEF(int,FileAccessWrite)(void* pHandler, MV_VS_FILE_ACCESS* pstFileAccess);
    HKICD_FUNC_PTR_MEMBER(FileAccessWrite);

    HKICD_FUNC_PTR_DEF(int,UpdateFirmware)(void* pHandler, const char* pszFile);
    HKICD_FUNC_PTR_MEMBER(UpdateFirmware);
    HKICD_FUNC_PTR_DEF(int,GetUpdateFirmwareProgress)(void* pHandler, unsigned int* pProgress);
    HKICD_FUNC_PTR_MEMBER(GetUpdateFirmwareProgress);

    HKICD_FUNC_PTR_DEF(int,GetGenICamXML)(void* pHandler, unsigned char* pData, unsigned int nDataSize, unsigned int* pnDataLen);
    HKICD_FUNC_PTR_MEMBER(GetGenICamXML);

    HKICD_FUNC_PTR_DEF(int,FormatToYaml)(const char* pszSrcFile, const char* pszDestFile, char* pszErrMsg,int iSize);
    HKICD_FUNC_PTR_MEMBER(FormatToYaml);


    HKICD_FUNC_PTR_DEF(void,GetToolTransformation)(const double P1_old[6], const double P1_new[6], double outPoint[16]);
    HKICD_FUNC_PTR_MEMBER(GetToolTransformation);
    HKICD_FUNC_PTR_DEF(void,GetAxisTransformation)(const double P1_old[6], const double P2_old[6],
                                                    const double P3_old[6], const double P4_old[6],
                                                    const double P1_new[6], const double P2_new[6],
                                                    const double P3_new[6], const double P4_new[6],
                                                    double outPoint[16]);
    HKICD_FUNC_PTR_MEMBER(GetAxisTransformation);
    HKICD_FUNC_PTR_DEF(void,GetReusePoint)(const double P_old[6], const double toolRT[16], int iRT1Count,
                                            const double coordRT[16], int iRT2Count, double outPoint[6]);
    HKICD_FUNC_PTR_MEMBER(GetReusePoint);
};

#endif // HKSMARTCAMERADEVICE_H
