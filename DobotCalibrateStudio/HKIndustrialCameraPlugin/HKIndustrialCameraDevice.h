#ifndef HKINDUSTRIALCAMERADEVICE_H
#define HKINDUSTRIALCAMERADEVICE_H

#include "ICameraDevice.h"
#include "IndustrialCameraStruct.h"

#include <functional>
#include <QLibrary>
#include <mutex>

class HKIndustrialCameraDevice : public ICameraDevice
{
    Q_OBJECT
public:
    explicit HKIndustrialCameraDevice(QObject *parent = nullptr);
    ~HKIndustrialCameraDevice() Q_DECL_OVERRIDE;

    void setVideoImageDataCallback(const std::function<void(const QImage&)>& callback);

    QList<CameraInfo> search() Q_DECL_OVERRIDE;
    bool setCameraIp(const QString& strConnect,const MyCameraIpInfo& info) Q_DECL_OVERRIDE;
    bool openCamera(const QString& strConnect) Q_DECL_OVERRIDE;
    void closeCamera() Q_DECL_OVERRIDE;
    bool isConnected() Q_DECL_OVERRIDE;
    bool startVideo() Q_DECL_OVERRIDE;
    void stopVideo() Q_DECL_OVERRIDE;
    QImage takePhoto() Q_DECL_OVERRIDE;
    QList<MyPointF6D> getCalibratePos(const MyPointF3D& flangleCenter, const MyPointF6D& robotPos) Q_DECL_OVERRIDE;
    bool calcGetCalibrateResult(MyPointF6D& avgValue, MyPointF6D& maxValue) Q_DECL_OVERRIDE;
    bool generateCalibrateFile(const QString& strSaveFileFullName) Q_DECL_OVERRIDE;
    bool createUserCoordinate(const QString& strCalibrateFile, const MyPointF6D& robotPos,
                              MyPointF6D& coordinatePos, int& iId, QImage& retImg) Q_DECL_OVERRIDE;
    bool beginCalibrate() Q_DECL_OVERRIDE;
    int endCalibrate() Q_DECL_OVERRIDE;
    bool calibrateSampling(const MyPointF6D& robotPos, QImage& retImg) Q_DECL_OVERRIDE;
    bool updateCalibrateSampling(const MyPointF6D& robotPos, int idxUpdate, QImage& retImg) Q_DECL_OVERRIDE;
    bool getCameraParam(const QJsonObject& property, QJsonObject& result) Q_DECL_OVERRIDE;
    bool setCameraParam(const QJsonObject& property, QJsonObject& result) Q_DECL_OVERRIDE;

private:
    friend void HKIndustrialVideoCallback(const ImageDataIndustrial* pData, void* pArgs);

    void initLib();
    void uninitLib();
    bool IsDeviceAccessible(const QString& strIdetify); //判断设备是否可以被连接

    //万能通用魔法函数
    bool GetIntValueEx(const QString& strKey, MVCC_INTVALUE_EX& stIntValue);
    bool SetIntValueEx(const QString& strKey, int64_t nValue);
    bool GetEnumValue(const QString& strKey, MVCC_ENUMVALUE& stEnumValue);
    bool SetEnumValue(const QString& strKey, unsigned int nValue);
    bool SetEnumValueByString(const QString& strKey, const QString& strValue);
    bool GetFloatValue(const QString& strKey, MVCC_FLOATVALUE& stFloatValue);
    bool SetFloatValue(const QString& strKey, float fValue);
    bool GetBoolValue(const QString& strKey, bool& bValue);
    bool SetBoolValue(const QString& strKey, bool bValue);
    bool GetStringValue(const QString& strKey, MVCC_STRINGVALUE& stStringValue);
    bool SetStringValue(const QString& strKey, const QString& strValue);
    bool CommandExecute(const QString& strKey);

private:
    std::mutex m_mtxEventVideoImage;
    std::function<void(const QImage&)> m_OnEventVideoImage;

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

    HKICD_FUNC_PTR_DEF(int,SearchCamera)(void* pHandler, CameraDeviceInfoIndustrial info[256]);
    HKICD_FUNC_PTR_MEMBER(SearchCamera);

    HKICD_FUNC_PTR_DEF(int,IsDeviceAccessible)(void* pHandler, const char* pszIdentifyName);
    HKICD_FUNC_PTR_MEMBER(IsDeviceAccessible);

    HKICD_FUNC_PTR_DEF(int,SetDeviceIpConfig)(void* pHandler, const char* pszIdentifyName, const char* pszIp,
                                        const char* pszSubNetMask, const char* pszDefultGateWay);
    HKICD_FUNC_PTR_MEMBER(SetDeviceIpConfig);

    HKICD_FUNC_PTR_DEF(int,ConnectCamera)(void* pHandler, const char* pszIdentifyName);
    HKICD_FUNC_PTR_MEMBER(ConnectCamera);

    HKICD_FUNC_PTR_DEF(void,DisconnectCamera)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(DisconnectCamera);

    HKICD_FUNC_PTR_DEF(int,IsDeviceConnected)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(IsDeviceConnected);

    HKICD_FUNC_PTR_DEF(int,StartCamera)(void* pHandler, void(*pfnCallback)(const ImageDataIndustrial* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(StartCamera);

    HKICD_FUNC_PTR_DEF(void,StopCamera)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(StopCamera);

    HKICD_FUNC_PTR_DEF(int,TakePhoto)(void* pHandler, void(*pfnCallback)(const ImageDataIndustrial* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(TakePhoto);

    HKICD_FUNC_PTR_DEF(void,BeginCalibrate)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(BeginCalibrate);

    HKICD_FUNC_PTR_DEF(int,EndCalibrate)(void* pHandler);
    HKICD_FUNC_PTR_MEMBER(EndCalibrate);

    HKICD_FUNC_PTR_DEF(int,GetCalibratePos)(void* pHandler,const Point3DIndustrial* pFlangleCenter,
                                      const MyPointIndustrial* pRobotPos,MyPointIndustrial retPos[], int iRetPosSize);
    HKICD_FUNC_PTR_MEMBER(GetCalibratePos);

    HKICD_FUNC_PTR_DEF(int,CalibrateSampling)(void* pHandler, const MyPointIndustrial* pRobotPos,
                                        void(*pfnCallback)(const ImageDataIndustrial* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(CalibrateSampling);

    HKICD_FUNC_PTR_DEF(int,UpdateCalibrateSampling)(void* pHandler, const MyPointIndustrial* pRobotPos,int iUpdateIndex,
                                        void(*pfnCallback)(const ImageDataIndustrial* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(UpdateCalibrateSampling);

    HKICD_FUNC_PTR_DEF(int,CalcGetCalibrateResult)(void* pHandler, ErrorValueIndustrial* pAvgValue, ErrorValueIndustrial* pMmaxValue);
    HKICD_FUNC_PTR_MEMBER(CalcGetCalibrateResult);

    HKICD_FUNC_PTR_DEF(int,GenerateCalibrateFile)(void* pHandler, const char* pszSaveFileFullName);
    HKICD_FUNC_PTR_MEMBER(GenerateCalibrateFile);

    HKICD_FUNC_PTR_DEF(int,CreateUserCoordinate)(void* pHandler, const char* pszFileFullName,
                                           const MyPointIndustrial* pRobotPos,
                                           MyPointIndustrial* pUserCoordinate, int* pId,
                                           void(*pfnCallback)(const ImageDataIndustrial* pData, void* pArgs), void* pArgs);
    HKICD_FUNC_PTR_MEMBER(CreateUserCoordinate);

    HKICD_FUNC_PTR_DEF(int,GetIntValueEx)(void* pHandler, const char* pszKey, MVCC_INTVALUE_EX* pstIntValue);
    HKICD_FUNC_PTR_MEMBER(GetIntValueEx);

    HKICD_FUNC_PTR_DEF(int,SetIntValueEx)(void* pHandler, const char* pszKey, int64_t nValue);
    HKICD_FUNC_PTR_MEMBER(SetIntValueEx);

    HKICD_FUNC_PTR_DEF(int,GetEnumValue)(void* pHandler, const char* pszKey, MVCC_ENUMVALUE* pstEnumValue);
    HKICD_FUNC_PTR_MEMBER(GetEnumValue);

    HKICD_FUNC_PTR_DEF(int,SetEnumValue)(void* pHandler, const char* pszKey, unsigned int nValue);
    HKICD_FUNC_PTR_MEMBER(SetEnumValue);

    HKICD_FUNC_PTR_DEF(int,SetEnumValueByString)(void* pHandler, const char* pszKey, const char* pszValue);
    HKICD_FUNC_PTR_MEMBER(SetEnumValueByString);

    HKICD_FUNC_PTR_DEF(int,GetFloatValue)(void* pHandler, const char* pszKey, MVCC_FLOATVALUE* pstFloatValue);
    HKICD_FUNC_PTR_MEMBER(GetFloatValue);

    HKICD_FUNC_PTR_DEF(int,SetFloatValue)(void* pHandler, const char* pszKey, float fValue);
    HKICD_FUNC_PTR_MEMBER(SetFloatValue);

    HKICD_FUNC_PTR_DEF(int,GetBoolValue)(void* pHandler, const char* pszKey, bool* pbValue);
    HKICD_FUNC_PTR_MEMBER(GetBoolValue);

    HKICD_FUNC_PTR_DEF(int,SetBoolValue)(void* pHandler, const char* pszKey, bool bValue);
    HKICD_FUNC_PTR_MEMBER(SetBoolValue);

    HKICD_FUNC_PTR_DEF(int,GetStringValue)(void* pHandler, const char* pszKey, MVCC_STRINGVALUE* pstStringValue);
    HKICD_FUNC_PTR_MEMBER(GetStringValue);

    HKICD_FUNC_PTR_DEF(int,SetStringValue)(void* pHandler, const char* pszKey, const char* pszValue);
    HKICD_FUNC_PTR_MEMBER(SetStringValue);

    HKICD_FUNC_PTR_DEF(int,CommandExecute)(void* pHandler, const char* pszKey);
    HKICD_FUNC_PTR_MEMBER(CommandExecute);
};

#endif // HKINDUSTRIALCAMERADEVICE_H
