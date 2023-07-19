#include "HKSmartCameraDevice.h"

#include <QCoreApplication>
#include <QDomElement>
#include <QDomDocument>
#include <QDataStream>
#include <memory>
#include "Logger.h"
#include "DError.h"

static void copyValueFrom(const ErrorValueSmart& src, MyPointF6D& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.rx = src.ang0; dest.ry = src.ang1; dest.rz = src.ang2;
}
/*
static void copyValueFrom(const MyPointF6D& src, ErrorValueSmart& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.ang0 = src.rx; dest.ang1 = src.ry; dest.ang2 = src.rz;
}
*/
static void copyValueFrom(const MyPointSmart& src, MyPointF6D& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.rx = src.rx; dest.ry = src.ry; dest.rz = src.rz;
}
static void copyValueFrom(const MyPointF6D& src, MyPointSmart& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.rx = src.rx; dest.ry = src.ry; dest.rz = src.rz;
}
/*
static void copyValueFrom(const Point3DSmart& src, MyPointF3D& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
}
*/
static void copyValueFrom(const MyPointF3D& src, Point3DSmart& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
}

HKSmartCameraDevice::HKSmartCameraDevice(QObject *parent) : QObject(parent)
{
    uninitLib();
    initLib();

    m_OnEventVideoImage = nullptr;

    m_pHandler = nullptr;
    if (m_pfnCreateCamera)
    {
#ifdef Q_OS_WIN
        QString strDll = QCoreApplication::applicationDirPath()+QDir::separator()+"MvVisionSensorControl.dll";
        strDll = QDir::toNativeSeparators(strDll);
#else
        QString strDll = "/opt/MVS/lib/armhf/libMvCameraControl.so.3.1.3.0";
#endif
        m_pHandler = m_pfnCreateCamera(strDll.toStdString().c_str());
    }
}

HKSmartCameraDevice::~HKSmartCameraDevice()
{
    if (m_pHandler && m_pfnDestroyCamera)
    {
        m_pfnDestroyCamera(m_pHandler);
    }
    m_pHandler = nullptr;

    uninitLib();
}

void HKSmartCameraDevice::setVideoImageDataCallback(const std::function<void(const ProjectResultInfo&)> &callback)
{
    std::lock_guard<std::mutex> guard(m_mtxEventVideoImage);
    m_OnEventVideoImage = callback;
}

void HKSmartCameraDevice::initLib()
{
    if (!m_lib.isLoaded())
    {
        m_lib.setFileName("HKSmartCameraLibrary");
        if (!m_lib.load())
        {
            qDebug()<<"load library fail:"<<m_lib.fileName()<<",err msg:"<<m_lib.errorString();
            return ;
        }
    }
#define HKICD_FUNC_LOAD(funcName) m_pfn##funcName = (pfn##funcName)m_lib.resolve(#funcName); \
    if (!m_pfn##funcName) qDebug()<<"\'"#funcName"\' load error:"<<m_lib.errorString()

    HKICD_FUNC_LOAD(CreateCamera);
    HKICD_FUNC_LOAD(DestroyCamera);
    HKICD_FUNC_LOAD(GetErrCode);
    HKICD_FUNC_LOAD(GetErrMsg);
    HKICD_FUNC_LOAD(SearchCamera);
    HKICD_FUNC_LOAD(SetDeviceIpConfig);
    HKICD_FUNC_LOAD(IsDeviceAccessible);
    HKICD_FUNC_LOAD(ConnectCamera);
    HKICD_FUNC_LOAD(DisconnectCamera);
    HKICD_FUNC_LOAD(StartCamera);
    HKICD_FUNC_LOAD(StartTestCamera);
    HKICD_FUNC_LOAD(StopCamera);
    HKICD_FUNC_LOAD(TakePhoto);
    HKICD_FUNC_LOAD(TakeBasePhoto);
    HKICD_FUNC_LOAD(BeginCalibrate);
    HKICD_FUNC_LOAD(EndCalibrate);
    HKICD_FUNC_LOAD(GetCalibratePos);
    HKICD_FUNC_LOAD(CalibrateSampling);
    HKICD_FUNC_LOAD(UpdateCalibrateSampling);
    HKICD_FUNC_LOAD(CalcGetCalibrateResult);
    HKICD_FUNC_LOAD(GenerateCalibrateFile);
    HKICD_FUNC_LOAD(CreateUserCoordinate);
    HKICD_FUNC_LOAD(GetIntValue);
    HKICD_FUNC_LOAD(SetIntValue);
    HKICD_FUNC_LOAD(GetEnumValue);
    HKICD_FUNC_LOAD(SetEnumValue);
    HKICD_FUNC_LOAD(SetEnumValueByString);
    HKICD_FUNC_LOAD(GetFloatValue);
    HKICD_FUNC_LOAD(SetFloatValue);
    HKICD_FUNC_LOAD(GetBoolValue);
    HKICD_FUNC_LOAD(SetBoolValue);
    HKICD_FUNC_LOAD(GetStringValue);
    HKICD_FUNC_LOAD(SetStringValue);
    HKICD_FUNC_LOAD(CommandExecute);
    HKICD_FUNC_LOAD(FileAccessRead);
    HKICD_FUNC_LOAD(FileAccessWrite);
    HKICD_FUNC_LOAD(GetGenICamXML);
}

void HKSmartCameraDevice::uninitLib()
{
    if (m_lib.isLoaded())
    {
        m_lib.unload();
    }
#define HKICM_FUNC_PTR_MEM_NULL(funcName) m_pfn##funcName = nullptr
    HKICM_FUNC_PTR_MEM_NULL(CreateCamera);
    HKICM_FUNC_PTR_MEM_NULL(DestroyCamera);
    HKICM_FUNC_PTR_MEM_NULL(GetErrCode);
    HKICM_FUNC_PTR_MEM_NULL(GetErrMsg);
    HKICM_FUNC_PTR_MEM_NULL(SearchCamera);
    HKICM_FUNC_PTR_MEM_NULL(SetDeviceIpConfig);
    HKICM_FUNC_PTR_MEM_NULL(IsDeviceAccessible);
    HKICM_FUNC_PTR_MEM_NULL(ConnectCamera);
    HKICM_FUNC_PTR_MEM_NULL(DisconnectCamera);
    HKICM_FUNC_PTR_MEM_NULL(StartCamera);
    HKICM_FUNC_PTR_MEM_NULL(StartTestCamera);
    HKICM_FUNC_PTR_MEM_NULL(StopCamera);
    HKICM_FUNC_PTR_MEM_NULL(TakePhoto);
    HKICM_FUNC_PTR_MEM_NULL(TakeBasePhoto);
    HKICM_FUNC_PTR_MEM_NULL(BeginCalibrate);
    HKICM_FUNC_PTR_MEM_NULL(EndCalibrate);
    HKICM_FUNC_PTR_MEM_NULL(GetCalibratePos);
    HKICM_FUNC_PTR_MEM_NULL(CalibrateSampling);
    HKICM_FUNC_PTR_MEM_NULL(UpdateCalibrateSampling);
    HKICM_FUNC_PTR_MEM_NULL(CalcGetCalibrateResult);
    HKICM_FUNC_PTR_MEM_NULL(GenerateCalibrateFile);
    HKICM_FUNC_PTR_MEM_NULL(CreateUserCoordinate);
    HKICM_FUNC_PTR_MEM_NULL(GetIntValue);
    HKICM_FUNC_PTR_MEM_NULL(SetIntValue);
    HKICM_FUNC_PTR_MEM_NULL(GetEnumValue);
    HKICM_FUNC_PTR_MEM_NULL(SetEnumValue);
    HKICM_FUNC_PTR_MEM_NULL(SetEnumValueByString);
    HKICM_FUNC_PTR_MEM_NULL(GetFloatValue);
    HKICM_FUNC_PTR_MEM_NULL(SetFloatValue);
    HKICM_FUNC_PTR_MEM_NULL(GetBoolValue);
    HKICM_FUNC_PTR_MEM_NULL(SetBoolValue);
    HKICM_FUNC_PTR_MEM_NULL(GetStringValue);
    HKICM_FUNC_PTR_MEM_NULL(SetStringValue);
    HKICM_FUNC_PTR_MEM_NULL(CommandExecute);
    HKICM_FUNC_PTR_MEM_NULL(FileAccessRead);
    HKICM_FUNC_PTR_MEM_NULL(FileAccessWrite);
    HKICM_FUNC_PTR_MEM_NULL(GetGenICamXML);
}

bool HKSmartCameraDevice::IsDeviceAccessible(const QString& strIdetify)
{
    if (m_pfnIsDeviceAccessible && m_pHandler)
    {
        return m_pfnIsDeviceAccessible(m_pHandler, strIdetify.toStdString().c_str())==0;
    }
    else
    {
        qDebug()<<"IsDeviceAccessible->load fail";
    }
    return false;
}

bool HKSmartCameraDevice::search(QList<CameraInfo>& retInfo)
{
    if (!m_pfnSearchCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve SearchCamera function";
        return false;
    }

    CameraDeviceInfoSmart info[256];
    memset(info, 0, sizeof(CameraDeviceInfoSmart)*256);
    int iCount = m_pfnSearchCamera(m_pHandler, info);
    if (iCount < 0)
    {
        m_iErrCode = DT_ERR_SEARCH_CAMERA;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to search camera,%s",szMsg);
        return false;
    }
    for (int i=0; i<iCount; ++i)
    {
        CameraInfo ci;
        ci.strIdentify = info[i].szIdentifyName;
        ci.bDeviceAccessible = IsDeviceAccessible(ci.strIdentify);

        MV_VS_DEVICE_INFO* pDeviceInfo = &(info[i].info);

        int nMac1 = ((pDeviceInfo->nMacAddrHigh & 0x0000ff00) >> 8);
        int nMac2 = (pDeviceInfo->nMacAddrHigh & 0x000000ff);
        int nMac3 = ((pDeviceInfo->nMacAddrLow & 0xff000000) >> 24);
        int nMac4 = ((pDeviceInfo->nMacAddrLow & 0x00ff0000) >> 16);
        int nMac5 = ((pDeviceInfo->nMacAddrLow & 0x0000ff00) >> 8);
        int nMac6 = (pDeviceInfo->nMacAddrLow & 0x000000ff);
        ci.strMacAddress = QString::asprintf("%02X:%02X:%02X:%02X:%02X:%02X",nMac1, nMac2, nMac3, nMac4, nMac5, nMac6);

        int nIp1 = ((pDeviceInfo->nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pDeviceInfo->nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pDeviceInfo->nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pDeviceInfo->nCurrentIp & 0x000000ff);
        ci.strIpAddress = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

        nIp1 = ((pDeviceInfo->nCurrentSubNetMask & 0xff000000) >> 24);
        nIp2 = ((pDeviceInfo->nCurrentSubNetMask & 0x00ff0000) >> 16);
        nIp3 = ((pDeviceInfo->nCurrentSubNetMask & 0x0000ff00) >> 8);
        nIp4 = (pDeviceInfo->nCurrentSubNetMask & 0x000000ff);
        ci.strSubNetMask = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

        nIp1 = ((pDeviceInfo->nDefultGateWay & 0xff000000) >> 24);
        nIp2 = ((pDeviceInfo->nDefultGateWay & 0x00ff0000) >> 16);
        nIp3 = ((pDeviceInfo->nDefultGateWay & 0x0000ff00) >> 8);
        nIp4 = (pDeviceInfo->nDefultGateWay & 0x000000ff);
        ci.strGateWay = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

        nIp1 = ((pDeviceInfo->nNetExport & 0xff000000) >> 24);
        nIp2 = ((pDeviceInfo->nNetExport & 0x00ff0000) >> 16);
        nIp3 = ((pDeviceInfo->nNetExport & 0x0000ff00) >> 8);
        nIp4 = (pDeviceInfo->nNetExport & 0x000000ff);
        ci.strNetExportAddress = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

        ci.strSerialNumber = (const char*)(pDeviceInfo->chSerialNumber);
        ci.strManufacturerName = (const char*)(pDeviceInfo->chManufacturerName);
        ci.strVersion = (const char*)(pDeviceInfo->chDeviceVersion);
        ci.strModelName = (const char*)(pDeviceInfo->chModelName);

        retInfo.push_back(ci);
    }
    m_iErrCode = DT_NO_ERROR;
    m_strErrMsg = "";

    return true;
}

bool HKSmartCameraDevice::setCameraIp(const QString& strConnect,const MyCameraIpInfo &info)
{
    if (!m_pfnSetDeviceIpConfig || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve SetDeviceIpConfig function";
        return false;
    }
    int nRet = m_pfnSetDeviceIpConfig(m_pHandler, strConnect.toStdString().c_str(), info.strIpAddress.toStdString().c_str()
                                      , info.strSubNetMask.toStdString().c_str(), info.strGateWay.toStdString().c_str());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_SET_CAMERA_IP;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to set ip,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

bool HKSmartCameraDevice::openCamera(const QString &strConnect, const QString& strPwd)
{
    if (!m_pfnConnectCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve ConnectCamera function";
        return false;
    }
    int nRet = m_pfnConnectCamera(m_pHandler, strConnect.toStdString().c_str(), strPwd.toStdString().c_str());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_CONNECT_CAMERA;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("fail to connect camera,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

void HKSmartCameraDevice::closeCamera()
{
    if (!m_pfnDisconnectCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve DisconnectCamera function";
        return ;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    m_pfnDisconnectCamera(m_pHandler);
}

void HKSmartVideoCallback(const ImageDataSmart* pData, void* pArgs)
{
    HKSmartCameraDevice* pCamera = (HKSmartCameraDevice*)pArgs;
    if (pData->pImageData)
    {
        QImage picture(pData->pImageData, pData->iWidth, pData->iHeight, pData->iImgStep, QImage::Format_RGB888);
        if(!picture.isNull())
        {
            ProjectResultInfo picInfo;
            picInfo.img = picture;
            picInfo.sz.setWidth(pData->iRealWidth);
            picInfo.sz.setHeight(pData->iRealHeight);
            if (pData->pResultInfo != nullptr)
            {
                picInfo.strResultData = pData->pResultInfo;
            }
            for (int i=0; i<pData->iMaskImgLen; ++i)
            {
                QImage maskPic(pData->pMaskImg[i].pRenderImage, pData->pMaskImg[i].iWidth,
                               pData->pMaskImg[i].iHeight, pData->iImgStep, QImage::Format_RGB888);
                if (!maskPic.isNull())
                {
                    picInfo.renderImg.insert(pData->pMaskImg[i].moduleId, maskPic);
                }
            }
            std::lock_guard<std::mutex> guard(pCamera->m_mtxEventVideoImage);
            if (pCamera->m_OnEventVideoImage)
            {
                pCamera->m_OnEventVideoImage(picInfo);
            }
        }
        else
        {
            qDebug()<<"HKSmartVideoCallback-->load image data fail";
        }
    }
}

bool HKSmartCameraDevice::startVideo()
{
    if (!m_pfnStartCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve StartCamera function";
        return false;
    }
    int nRet = m_pfnStartCamera(m_pHandler, &HKSmartVideoCallback, this);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_START_VIDEO;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("start video fail,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

bool HKSmartCameraDevice::startTestVideo()
{
    if (!m_pfnStartTestCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve StartTestCamera function";
        return false;
    }
    int nRet = m_pfnStartTestCamera(m_pHandler, &HKSmartVideoCallback, this);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_START_VIDEO;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("start test video fail,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return 0 == nRet;
}

void HKSmartCameraDevice::stopVideo()
{
    if (!m_pfnStopCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve StopCamera function";
        return ;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    m_pfnStopCamera(m_pHandler);
}

static void HKSmartTakePictureCallback(const ImageDataSmart* pData, void* pArgs)
{
    ProjectResultInfo* pImage = (ProjectResultInfo*)pArgs;
    if (pData->pImageData)
    {
        QImage img(pData->pImageData, pData->iWidth, pData->iHeight, pData->iImgStep, QImage::Format_RGB888);
        pImage->img = img.copy();
        pImage->sz.setWidth(pData->iRealWidth);
        pImage->sz.setHeight(pData->iRealHeight);
        if (pData->pResultInfo != nullptr)
        {
            pImage->strResultData = pData->pResultInfo;
        }
        for (int i=0; i<pData->iMaskImgLen; ++i)
        {
            QImage maskPic(pData->pMaskImg[i].pRenderImage, pData->pMaskImg[i].iWidth,
                           pData->pMaskImg[i].iHeight,pData->iImgStep, QImage::Format_RGB888);
            if (!maskPic.isNull())
            {
                pImage->renderImg.insert(pData->pMaskImg[i].moduleId, maskPic.copy());
            }
        }
    }
}
bool HKSmartCameraDevice::takePhoto(ProjectResultInfo& info)
{
    if (!m_pfnTakePhoto || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve TakePhoto function";
        return false;
    }

    int nRet = m_pfnTakePhoto(m_pHandler, &HKSmartTakePictureCallback, &info);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_TAKE_PHOTO;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("take photo fail,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
        return true;
    }
    return false;
}
bool HKSmartCameraDevice::takeBasePhoto(ProjectResultInfo& info, int iModuleId)
{
    if (!m_pfnTakeBasePhoto || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve TakeBasePhoto function";
        return false;
    }

    int nRet = m_pfnTakeBasePhoto(m_pHandler,iModuleId, &HKSmartTakePictureCallback, &info);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_TAKE_PHOTO;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("take base photo fail,%s",szMsg);
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
        return true;
    }
    return false;
}

QList<MyPointF6D> HKSmartCameraDevice::getCalibratePos(const MyPointF3D &flangleCenter, const MyPointF6D &robotPos)
{
    QList<MyPointF6D> retPoint;
    if (!m_pfnGetCalibratePos || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve GetCalibratePos function";
        return retPoint;
    }

    Point3DSmart flangle;
    copyValueFrom(flangleCenter, flangle);

    MyPointSmart robot;
    copyValueFrom(robotPos, robot);

    MyPointSmart outPos[256];
    const int iCount = m_pfnGetCalibratePos(m_pHandler, &flangle, &robot, outPos, 256);
    for (int i=0 ;i<iCount;++i)
    {
        MyPointF6D pt;
        copyValueFrom(outPos[i], pt);
        retPoint.push_back(pt);
    }

    m_iErrCode = DT_NO_ERROR;
    m_strErrMsg = "";
    return retPoint;
}

bool HKSmartCameraDevice::calcGetCalibrateResult(MyPointF6D &avgValue, MyPointF6D &maxValue)
{
    if (!m_pfnCalcGetCalibrateResult || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve CalcGetCalibrateResult function";
        return false;
    }
    ErrorValueSmart avgErr;
    ErrorValueSmart maxErr;
    int nRet = m_pfnCalcGetCalibrateResult(m_pHandler, &avgErr, &maxErr);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_CALIBRATE_RESULT;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("calculate calibrate result fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    copyValueFrom(avgErr, avgValue);
    copyValueFrom(maxErr, maxValue);

    return true;
}

bool HKSmartCameraDevice::generateCalibrateFile(const QString &strSaveFileFullName)
{
    if (!m_pfnGenerateCalibrateFile || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve GenerateCalibrateFile function";
        return false;
    }
    QByteArray arrName = strSaveFileFullName.toLocal8Bit();
    int nRet = m_pfnGenerateCalibrateFile(m_pHandler, arrName.constData());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_CALIBRATE_FILE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("save calibrate file fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return true;
}

bool HKSmartCameraDevice::createUserCoordinate(const QString &strCalibrateFile, const MyPointF6D &robotPos,
                                              MyPointF6D& coordinatePos, int& iId, ProjectResultInfo& picture)
{
    if (!m_pfnCreateUserCoordinate || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve CreateUserCoordinate function";
        return false;
    }

    MyPointSmart robot,coordinate;
    copyValueFrom(robotPos, robot);
    QByteArray arrName = strCalibrateFile.toLocal8Bit();

    int nRet = m_pfnCreateUserCoordinate(m_pHandler, arrName.constData(), &robot, &coordinate,&iId,
                                         &HKSmartTakePictureCallback, &picture);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_USER_COORDINATE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("create user coordinate fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    copyValueFrom(coordinate, coordinatePos);

    return true;
}

bool HKSmartCameraDevice::beginCalibrate()
{
    if (!m_pfnBeginCalibrate || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve BeginCalibrate function";
        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    m_pfnBeginCalibrate(m_pHandler);
    return true;
}

int HKSmartCameraDevice::endCalibrate()
{
    if (!m_pfnEndCalibrate || !m_pHandler)
    {
        m_iErrCode = DT_ERR_CALIBRATE_END;
        m_strErrMsg = "can not resolve EndCalibrate function";
        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return m_pfnEndCalibrate(m_pHandler);
}

bool HKSmartCameraDevice::calibrateSampling(const MyPointF6D &robotPos, ProjectResultInfo& picture)
{
    if (!m_pfnCalibrateSampling || !m_pHandler)
    {
        m_iErrCode = DT_ERR_CALIBRATE_SAMPLING;
        m_strErrMsg = "can not resolve CalibrateSampling function";
        return false;
    }

    MyPointSmart robot;
    copyValueFrom(robotPos, robot);

    int nRet = m_pfnCalibrateSampling(m_pHandler, &robot, &HKSmartTakePictureCallback, &picture);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_CALIBRATE_SAMPLING;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("calibrate sampling fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::updateCalibrateSampling(const MyPointF6D &robotPos, int idxUpdate, ProjectResultInfo &picture)
{
    if (!m_pfnUpdateCalibrateSampling || !m_pHandler)
    {
        m_iErrCode = DT_ERR_UPDATE_CALIBRATE_SAMPLING;
        m_strErrMsg = "can not resolve CalibrateSampling function";
        return false;
    }

    MyPointSmart robot;
    copyValueFrom(robotPos, robot);

    int nRet = m_pfnUpdateCalibrateSampling(m_pHandler, &robot, idxUpdate, &HKSmartTakePictureCallback, &picture);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_UPDATE_CALIBRATE_SAMPLING;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("update calibrate sampling fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

static void ParseFileContent(QDomElement* pElement, QMap<QString, MyVsXmlAttribute> &attributeType)
{
    for(QDomElement currentElement = pElement->firstChildElement();!currentElement.isNull();currentElement=currentElement.nextSiblingElement())
    {
        QDomElement* pTmpEle = &currentElement;
        if (currentElement.toText().nodeValue().isEmpty())
        {
            if (currentElement.attribute("Name").isEmpty())
            {
                ParseFileContent(pTmpEle, attributeType);
                continue;
            }

            QString strAttrName = currentElement.attribute("Name");

            MyVsXmlAttribute pstXMLAttribute;
            pstXMLAttribute.strDataType = currentElement.nodeName();

            QDomElement pIsAvailable = currentElement.firstChildElement("pIsAvailable");
            if (!pIsAvailable.isNull())
            {
                pstXMLAttribute.strIsAvailable = pIsAvailable.text();
            }

            QDomElement pIsImplemented = currentElement.firstChildElement("pIsImplemented");
            if (!pIsImplemented.isNull())
            {
                pstXMLAttribute.strIsImplemented = pIsImplemented.text();
            }

            attributeType[strAttrName] = pstXMLAttribute;
        }
    }
}
bool HKSmartCameraDevice::getCameraXmlAttribute(QMap<QString, MyVsXmlAttribute> &attributeType)
{
    unsigned int nFileLen = 0;
    unsigned int nBufferSize = 1024 * 1024 * 5;
    std::unique_ptr<unsigned char> pGenICamXML(new unsigned char[nBufferSize]);
    if (nullptr == pGenICamXML.get())
    {
        m_iErrCode = DT_ERR_ALLOCATE_MEMORY;
        m_strErrMsg = "The resource allocate memory fail";
        return false;
    }
    if (!GetGenICamXML(pGenICamXML.get(), nBufferSize, &nFileLen))
    {
        return false;
    }

    const char* pData = reinterpret_cast<const char*>(pGenICamXML.get());
    //保存到文件方便查询吧
    QFile file("CameraXmlAttribute.xml");
    if (file.open(QFile::WriteOnly|QFile::Truncate))
    {
        file.write(pData,nFileLen);
        file.close();
    }

    QDomDocument doc;
    if (!doc.setContent(QByteArray(pData,nFileLen)))
    {
        return false;
    }
    QDomElement root = doc.documentElement();
    ParseFileContent(&root, attributeType);

    return true;
}

bool HKSmartCameraDevice::getModuleTranslate(QMap<QString, MyModuleTranslate> &translate)
{
    QByteArray xmlData;
    if (!SetEnumValueByString("FileSelector", "Translate") || !FileAccessRead(xmlData,"Translate"))
    {
        return false;
    }

    //保存到文件方便查询吧
    QFile file("CameraTranslate.json");
    if (file.open(QFile::WriteOnly|QFile::Truncate))
    {
        file.write(xmlData);
        file.close();
    }

    QDomDocument doc;
    if (!doc.setContent(xmlData))
    {
        m_iErrCode = DT_ERR_CONTENT;
        m_strErrMsg = "The resource content is not xml format string";
        return false;
    }
    QDomElement ele = doc.documentElement();
    QDomElement next = ele.firstChildElement("Feature");
    while (!next.isNull())
    {
        QString strName = next.attribute("Name");
        if (!strName.isEmpty())
        {
            MyModuleTranslate mtl;
            QDomElement displayNameEn = next.firstChildElement("DisplayName::en");
            if (!displayNameEn.isNull())
            {
                mtl.strDisplayNameEN = displayNameEn.text();
            }
            QDomElement displayNameCn = next.firstChildElement("DisplayName::cn");
            if (!displayNameCn.isNull())
            {
                mtl.strDisplayNameCN = displayNameCn.text();
            }
            translate.insert(strName, mtl);
        }

        next = next.nextSiblingElement();
    }

    return true;
}

bool HKSmartCameraDevice::getNodeIsVisible(const MyVsXmlAttribute& xmlMLAttribute)
{
    if (xmlMLAttribute.strIsAvailable.isEmpty() || xmlMLAttribute.strIsImplemented.isEmpty())
    {
        return true;
    }

    MV_VS_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MV_VS_INTVALUE));
    if (!GetIntValue(xmlMLAttribute.strIsImplemented, stParam))
    {
        return false;
    }
    if (0 != stParam.nCurValue)
    {
        return true;
    }

    memset(&stParam, 0, sizeof(MV_VS_INTVALUE));
    if (!GetIntValue(xmlMLAttribute.strIsAvailable, stParam))
    {
        return false;
    }
    if (0 != stParam.nCurValue)
    {
        return true;
    }
    return false;
}

bool HKSmartCameraDevice::GetIntValue(const QString& strKey, MV_VS_INTVALUE& stIntValue)
{
    if (!m_pfnGetIntValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetIntValue function";
        return false;
    }

    memset(&stIntValue, 0, sizeof(MV_VS_INTVALUE));
    int nRet = m_pfnGetIntValue(m_pHandler, strKey.toStdString().c_str(), &stIntValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetIntValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return true;
}

bool HKSmartCameraDevice::SetIntValue(const QString& strKey, int64_t nValue)
{
    if (!m_pfnSetIntValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetIntValue function";
        return false;
    }

    int nRet = m_pfnSetIntValue(m_pHandler, strKey.toStdString().c_str(), nValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetIntValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::GetEnumValue(const QString& strKey, MV_VS_ENUMVALUE& stEnumValue)
{
    if (!m_pfnGetEnumValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetEnumValue function";
        return false;
    }

    memset(&stEnumValue, 0, sizeof(MV_VS_ENUMVALUE));
    int nRet = m_pfnGetEnumValue(m_pHandler, strKey.toStdString().c_str(), &stEnumValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetEnumValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::SetEnumValue(const QString& strKey, unsigned int nValue)
{
    if (!m_pfnSetEnumValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetEnumValue function";
        return false;
    }

    int nRet = m_pfnSetEnumValue(m_pHandler, strKey.toStdString().c_str(), nValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetEnumValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::SetEnumValueByString(const QString& strKey, const QString& strValue)
{
    if (!m_pfnSetEnumValueByString || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetEnumValueByString function";
        return false;
    }

    int nRet = m_pfnSetEnumValueByString(m_pHandler, strKey.toStdString().c_str(), strValue.toStdString().c_str());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetEnumValueByString(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::GetFloatValue(const QString& strKey, MV_VS_FLOATVALUE& stFloatValue)
{
    if (!m_pfnGetFloatValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetFloatValue function";
        return false;
    }

    memset(&stFloatValue, 0, sizeof(MV_VS_FLOATVALUE));
    int nRet = m_pfnGetFloatValue(m_pHandler, strKey.toStdString().c_str(), &stFloatValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetFloatValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::SetFloatValue(const QString& strKey, float fValue)
{
    if (!m_pfnSetFloatValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetFloatValue function";
        return false;
    }

    int nRet = m_pfnSetFloatValue(m_pHandler, strKey.toStdString().c_str(), fValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetFloatValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::GetBoolValue(const QString& strKey, bool& bValue)
{
    if (!m_pfnGetBoolValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetBoolValue function";
        return false;
    }

    int nRet = m_pfnGetBoolValue(m_pHandler, strKey.toStdString().c_str(), &bValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetBoolValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::SetBoolValue(const QString& strKey, bool bValue)
{
    if (!m_pfnSetBoolValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetBoolValue function";
        return false;
    }

    int nRet = m_pfnSetBoolValue(m_pHandler, strKey.toStdString().c_str(), bValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetBoolValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::GetStringValue(const QString& strKey, MV_VS_STRINGVALUE& stStringValue)
{
    if (!m_pfnGetStringValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetStringValue function";
        return false;
    }

    memset(&stStringValue, 0, sizeof(MV_VS_STRINGVALUE));
    int nRet = m_pfnGetStringValue(m_pHandler, strKey.toStdString().c_str(), &stStringValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetStringValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::SetStringValue(const QString& strKey, const QString& strValue)
{
    if (!m_pfnSetStringValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetStringValue function";
        return false;
    }

    int nRet = m_pfnSetStringValue(m_pHandler, strKey.toStdString().c_str(), strValue.toStdString().c_str());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetStringValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::SetCommandValue(const QString& strKey)
{
    if (!m_pfnCommandExecute || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetCommandValue function";
        return false;
    }

    int nRet = m_pfnCommandExecute(m_pHandler, strKey.toStdString().c_str());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetCommandValue(%s) fail,%s", strKey.toStdString().c_str(),szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::FileAccessRead(QByteArray& fileData, const char* pszDevFile)
{
    std::string strDevFile(pszDevFile);
    bool bRet = true;
    unsigned int nMaxFileSize = 102400;
    MV_VS_FILE_ACCESS mvsfa;
    memset(&mvsfa, 0, sizeof(MV_VS_FILE_ACCESS));
    mvsfa.pDevFileName = const_cast<char*>(strDevFile.c_str());
    mvsfa.nMaxFileSize = nMaxFileSize;
    mvsfa.pFile = (char*)malloc(mvsfa.nMaxFileSize + 1);
    memset(mvsfa.pFile, 0, mvsfa.nMaxFileSize + 1);
    mvsfa.nOffset = 0;

    do
    {
        const int MV_VS_E_NOENOUGH_BUF = 0x8003000A;
        int nRetCode = 0;
        bRet = FileAccessRead(mvsfa, nRetCode);
        if (!bRet)
        {
            if (MV_VS_E_NOENOUGH_BUF == nRetCode || nMaxFileSize < mvsfa.nFileTotalLen)
            {//Insufficient memory
                free(mvsfa.pFile);

                nMaxFileSize = mvsfa.nFileTotalLen;
                memset(&mvsfa, 0, sizeof(MV_VS_FILE_ACCESS));
                mvsfa.pDevFileName = const_cast<char*>(strDevFile.c_str());
                mvsfa.nMaxFileSize = nMaxFileSize;
                mvsfa.pFile = (char*)malloc(mvsfa.nMaxFileSize + 1);
                memset(mvsfa.pFile, 0, mvsfa.nMaxFileSize + 1);
                mvsfa.nOffset = 0;

                bRet = FileAccessRead(mvsfa, nRetCode);
            }
        }
    }while(false);

    if (bRet)
    {
        fileData.append(mvsfa.pFile, mvsfa.nFileCurLen);
    }

    free(mvsfa.pFile);

    return bRet;
}

bool HKSmartCameraDevice::FileAccessRead(QIODevice& file, const char* pszDevFile)
{
    QByteArray data;
    if (FileAccessRead(data,pszDevFile))
    {
        file.write(data);
        return true;
    }
    return false;
}

bool HKSmartCameraDevice::FileAccessRead(MV_VS_FILE_ACCESS &stFileAccess, int& nRetCode)
{
    if (!m_pfnFileAccessRead || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve FileAccessRead function";
        return false;
    }

    int nRet = m_pfnFileAccessRead(m_pHandler, &stFileAccess);//0x8003000A
    nRetCode = nRet;
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("FileAccessRead fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::FileAccessWrite(const QByteArray& fileData, const char* pszDevFile)
{
    QDataStream file(fileData);

    std::string strDevFile(pszDevFile);
    bool bRet = true;
    const unsigned int nBufferSize = 102400;
    MV_VS_FILE_ACCESS mvsfa;
    memset(&mvsfa, 0, sizeof(MV_VS_FILE_ACCESS));
    mvsfa.pDevFileName = const_cast<char*>(strDevFile.c_str());
    mvsfa.nMaxFileSize = nBufferSize;
    mvsfa.pFile = (char*)malloc(mvsfa.nMaxFileSize);
    memset(mvsfa.pFile, 0, mvsfa.nMaxFileSize);
    mvsfa.nFileTotalLen = fileData.size();
    mvsfa.nOffset = 0;
    while (!file.atEnd())
    {
        int nSize = file.readRawData(mvsfa.pFile, nBufferSize);
        if (nSize > 0)
        {
            mvsfa.nMaxFileSize = nSize;
            if (!FileAccessWrite(mvsfa))
            {
                bRet = false;
                break;
            }
            mvsfa.nOffset += mvsfa.nFileCurLen;
        }
        else
        {
            break;
        }
    }
    free(mvsfa.pFile);
    return bRet;
}

bool HKSmartCameraDevice::FileAccessWrite(QIODevice& file, const char* pszDevFile)
{
    std::string strDevFile(pszDevFile);
    bool bRet = true;
    const unsigned int nBufferSize = 102400;
    MV_VS_FILE_ACCESS mvsfa;
    memset(&mvsfa, 0, sizeof(MV_VS_FILE_ACCESS));
    mvsfa.pDevFileName = const_cast<char*>(strDevFile.c_str());
    mvsfa.nMaxFileSize = nBufferSize;
    mvsfa.pFile = (char*)malloc(mvsfa.nMaxFileSize);
    memset(mvsfa.pFile, 0, mvsfa.nMaxFileSize);
    mvsfa.nFileTotalLen = file.size();
    mvsfa.nOffset = 0;
    while (!file.atEnd())
    {
        qint64 nSize = file.read(mvsfa.pFile, nBufferSize);
        if (nSize > 0)
        {
            mvsfa.nMaxFileSize = nSize;
            if (!FileAccessWrite(mvsfa))
            {
                bRet = false;
                break;
            }
            mvsfa.nOffset += mvsfa.nFileCurLen;
        }
        else
        {
            break;
        }
    }
    free(mvsfa.pFile);
    return bRet;
}

bool HKSmartCameraDevice::FileAccessWrite(MV_VS_FILE_ACCESS &stFileAccess)
{
    if (!m_pfnFileAccessWrite || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve FileAccessWrite function";
        return false;
    }

    int nRet = m_pfnFileAccessWrite(m_pHandler, &stFileAccess);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("FileAccessWrite fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKSmartCameraDevice::GetGenICamXML(unsigned char* pBuffer, unsigned int nBufferSize, unsigned int* pRetDataSize)
{
    if (!m_pfnGetGenICamXML || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetGenICamXML function";
        return false;
    }

    int nRet = m_pfnGetGenICamXML(m_pHandler, pBuffer, nBufferSize, pRetDataSize);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetGenICamXML fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}
