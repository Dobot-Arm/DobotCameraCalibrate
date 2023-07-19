#include "HKIndustrialIODevice.h"
#include "Logger.h"
#include "DError.h"

HKIndustrialIODevice::HKIndustrialIODevice(QObject *parent):QObject(parent)
{
    uninitLib();
    initLib();

    m_iErrCode = DT_NO_ERROR;
    m_pHandler = nullptr;
    if (m_pfnCreateDevice)
    {
        m_pHandler = m_pfnCreateDevice();
    }
}

HKIndustrialIODevice::~HKIndustrialIODevice()
{
    if (m_pHandler && m_pfnDestroyDevice)
    {
        m_pfnDestroyDevice(m_pHandler);
    }
    m_pHandler = nullptr;

    for(auto itr=m_channelTimer.begin();itr!=m_channelTimer.end();++itr)
    {
        itr.value()->deleteLater();
    }

    uninitLib();
}

void HKIndustrialIODevice::initLib()
{
    if (!m_lib.isLoaded())
    {
        m_lib.setFileName("HKIndustrialIOControllerLibrary");
        if (!m_lib.load())
        {
            qDebug()<<"load library fail:"<<m_lib.fileName()<<",err msg:"<<m_lib.errorString();
            return ;
        }
    }
#define HKIODEVICE_FUNC_LOAD(funcName) m_pfn##funcName = (pfn##funcName)m_lib.resolve(#funcName); \
    if (!m_pfn##funcName) qDebug()<<"\'"#funcName"\' load error:"<<m_lib.errorString()

    HKIODEVICE_FUNC_LOAD(CreateDevice);
    HKIODEVICE_FUNC_LOAD(DestroyDevice);
    HKIODEVICE_FUNC_LOAD(GetErrCode);
    HKIODEVICE_FUNC_LOAD(GetErrMsg);
    HKIODEVICE_FUNC_LOAD(OpenDevice);
    HKIODEVICE_FUNC_LOAD(CloseDevice);
    HKIODEVICE_FUNC_LOAD(GetDeviceVersion);
    HKIODEVICE_FUNC_LOAD(GetLightBoardParam);
    HKIODEVICE_FUNC_LOAD(TurnOnLight);
    HKIODEVICE_FUNC_LOAD(TurnOffLight);
}

void HKIndustrialIODevice::uninitLib()
{
    if (m_lib.isLoaded())
    {
        m_lib.unload();
    }
#define HKIODEVICE_FUNC_PTR_MEM_NULL(funcName) m_pfn##funcName = nullptr
    HKIODEVICE_FUNC_PTR_MEM_NULL(CreateDevice);
    HKIODEVICE_FUNC_PTR_MEM_NULL(DestroyDevice);
    HKIODEVICE_FUNC_PTR_MEM_NULL(GetErrCode);
    HKIODEVICE_FUNC_PTR_MEM_NULL(GetErrMsg);
    HKIODEVICE_FUNC_PTR_MEM_NULL(OpenDevice);
    HKIODEVICE_FUNC_PTR_MEM_NULL(CloseDevice);
    HKIODEVICE_FUNC_PTR_MEM_NULL(GetDeviceVersion);
    HKIODEVICE_FUNC_PTR_MEM_NULL(GetLightBoardParam);
    HKIODEVICE_FUNC_PTR_MEM_NULL(TurnOnLight);
    HKIODEVICE_FUNC_PTR_MEM_NULL(TurnOffLight);
}

bool HKIndustrialIODevice::openDevice(int iPort)
{
    if (!m_pfnOpenDevice || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve OpenDevice function";
        return false;
    }
    int nRet = m_pfnOpenDevice(m_pHandler, iPort);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_IODEVICE_OPEN;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to open device,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

void HKIndustrialIODevice::closeDevice()
{
    if (!m_pfnCloseDevice || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve CloseDevice function";
        return ;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    m_pfnCloseDevice(m_pHandler);
}

bool HKIndustrialIODevice::getDeviceVersion(MV_IO_VERSION& stVersion)
{
    if (!m_pfnGetDeviceVersion || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve GetDeviceVersion function";
        return false;
    }
    int nRet = m_pfnGetDeviceVersion(m_pHandler, &stVersion);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_IODEVICE_GETVERSION;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to get device version,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

bool HKIndustrialIODevice::getLightBoardParam(int iChannel, MV_IO_LIGHT_PARAM& stLightParam)
{
    if (!m_pfnGetLightBoardParam || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve GetLightBoardParam function";
        return false;
    }
    int nRet = m_pfnGetLightBoardParam(m_pHandler, iChannel, &stLightParam);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_START_VIDEO;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to get light param,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

bool HKIndustrialIODevice::turnOnLight(int iChannel, int iDurationMS, int iLightValue)
{
    if (!m_pfnTurnOnLight || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve StopCamera function";
        return false;
    }

    int nRet = m_pfnTurnOnLight(m_pHandler, iChannel, iDurationMS, iLightValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_IODEVICE_TURNLIGHTON;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to turn light on,%s",szMsg);
    }
    else
    {
        if (iDurationMS > 0)
        {
            QTimer* pTimer = m_channelTimer.value(iChannel, nullptr);
            if (!pTimer)
            {
                pTimer = new QTimer(this);
                pTimer->setSingleShot(true);
                connect(pTimer, &QTimer::timeout, this, [this,iChannel]{
                    turnOffLight(iChannel);
                });
            }
            pTimer->start(iDurationMS);
        }
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

bool HKIndustrialIODevice::turnOffLight(int iChannel)
{
    QTimer* pTimer = m_channelTimer.value(iChannel, nullptr);
    if (pTimer)
    {
        pTimer->stop();
    }

    if (!m_pfnTurnOffLight || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve StopCamera function";
        return false;
    }

    MV_IO_LIGHT_PARAM stLightParam;
    memset(&stLightParam, 0, sizeof(MV_IO_LIGHT_PARAM));
    getLightBoardParam(iChannel, stLightParam);
    int nRet = m_pfnTurnOffLight(m_pHandler, iChannel, stLightParam.nDurationTime, stLightParam.nLightValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_IODEVICE_TURNLIGHTOFF;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to turn light off,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}
