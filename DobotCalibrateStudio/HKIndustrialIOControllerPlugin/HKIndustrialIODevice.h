#ifndef HKINDUSTRIALIODEVICE_H
#define HKINDUSTRIALIODEVICE_H

#include "IndustrialIODeviceStruct.h"

#include <functional>
#include <QLibrary>
#include <mutex>
#include <QTimer>
#include <QHash>

class HKIndustrialIODevice : public QObject
{
    Q_OBJECT
public:
    explicit HKIndustrialIODevice(QObject *parent = nullptr);
    ~HKIndustrialIODevice();

    int getErrCode() const{return m_iErrCode;};
    QString getErrMessage() const{return m_strErrMsg;};
    bool openDevice(int iPort);
    void closeDevice();
    bool getDeviceVersion(MV_IO_VERSION& stVersion);
    bool getLightBoardParam(int iChannel, MV_IO_LIGHT_PARAM& stLightParam);
    bool turnOnLight(int iChannel, int iDurationMS, int iLightValue);
    bool turnOffLight(int iChannel);

private:
    void initLib();
    void uninitLib();

private:
    int m_iErrCode;
    QString m_strErrMsg;
    /*******************************************************/
    QLibrary m_lib;
    void* m_pHandler;

    QHash<int,QTimer*> m_channelTimer;

#define HKIODEVICE_FUNC_PTR_DEF(retType,funcName) typedef retType (*pfn##funcName)
#define HKIODEVICE_FUNC_PTR_MEMBER(funcName) pfn##funcName m_pfn##funcName

    HKIODEVICE_FUNC_PTR_DEF(void*,CreateDevice)();
    HKIODEVICE_FUNC_PTR_MEMBER(CreateDevice);

    HKIODEVICE_FUNC_PTR_DEF(void,DestroyDevice)(void* pHandler);
    HKIODEVICE_FUNC_PTR_MEMBER(DestroyDevice);

    HKIODEVICE_FUNC_PTR_DEF(int,GetErrCode)(void* pHandler);
    HKIODEVICE_FUNC_PTR_MEMBER(GetErrCode);

    HKIODEVICE_FUNC_PTR_DEF(void,GetErrMsg)(void* pHandler, char* pszMsg);
    HKIODEVICE_FUNC_PTR_MEMBER(GetErrMsg);

    HKIODEVICE_FUNC_PTR_DEF(int,OpenDevice)(void* pHandler, int iPort);
    HKIODEVICE_FUNC_PTR_MEMBER(OpenDevice);

    HKIODEVICE_FUNC_PTR_DEF(void,CloseDevice)(void* pHandler);
    HKIODEVICE_FUNC_PTR_MEMBER(CloseDevice);

    HKIODEVICE_FUNC_PTR_DEF(int,GetDeviceVersion)(void* pHandler, MV_IO_VERSION* pstVersion);
    HKIODEVICE_FUNC_PTR_MEMBER(GetDeviceVersion);

    HKIODEVICE_FUNC_PTR_DEF(int,GetLightBoardParam)(void* pHandler, int iChannel, MV_IO_LIGHT_PARAM* pstLightParam);
    HKIODEVICE_FUNC_PTR_MEMBER(GetLightBoardParam);

    HKIODEVICE_FUNC_PTR_DEF(int,TurnOnLight)(void* pHandler, int iChannel, int iDurationMS, int iLightValue);
    HKIODEVICE_FUNC_PTR_MEMBER(TurnOnLight);

    HKIODEVICE_FUNC_PTR_DEF(int,TurnOffLight)(void* pHandler, int iChannel, int iDurationMS, int iLightValue);
    HKIODEVICE_FUNC_PTR_MEMBER(TurnOffLight);
};

#endif // HKINDUSTRIALCAMERADEVICE_H
