#include "HKIndustrialCameraDevice.h"
#include <QCoreApplication>
#include "Logger.h"
#include "DError.h"
#include "DataBean/CameraParamBean.h"

static void copyValueFrom(const ErrorValueIndustrial& src, MyPointF6D& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.rx = src.ang0; dest.ry = src.ang1; dest.rz = src.ang2;
}
/*
static void copyValueFrom(const MyPointF6D& src, ErrorValueIndustrial& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.ang0 = src.rx; dest.ang1 = src.ry; dest.ang2 = src.rz;
}
*/
static void copyValueFrom(const MyPointIndustrial& src, MyPointF6D& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.rx = src.rx; dest.ry = src.ry; dest.rz = src.rz;
}
static void copyValueFrom(const MyPointF6D& src, MyPointIndustrial& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
    dest.rx = src.rx; dest.ry = src.ry; dest.rz = src.rz;
}
/*
static void copyValueFrom(const Point3DIndustrial& src, MyPointF3D& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
}
*/
static void copyValueFrom(const MyPointF3D& src, Point3DIndustrial& dest)
{
    dest.x = src.x; dest.y = src.y; dest.z = src.z;
}

HKIndustrialCameraDevice::HKIndustrialCameraDevice(QObject *parent) : ICameraDevice(parent)
{
    uninitLib();
    initLib();

    m_OnEventVideoImage = nullptr;

    m_pHandler = nullptr;
    if (m_pfnCreateCamera)
    {
#ifdef Q_OS_WIN
        QString strDll = QCoreApplication::applicationDirPath()+QDir::separator()+"MvCameraControl.dll";
        strDll = QDir::toNativeSeparators(strDll);
#else
        QString strDll = "/opt/MVS/lib/armhf/libMvCameraControl.so.3.1.3.0";
#endif
        m_pHandler = m_pfnCreateCamera(strDll.toStdString().c_str());
    }
}

HKIndustrialCameraDevice::~HKIndustrialCameraDevice()
{
    if (m_pHandler && m_pfnDestroyCamera)
    {
        m_pfnDestroyCamera(m_pHandler);
    }
    m_pHandler = nullptr;

    uninitLib();
}

void HKIndustrialCameraDevice::setVideoImageDataCallback(const std::function<void(const QImage&)> &callback)
{
    std::lock_guard<std::mutex> guard(m_mtxEventVideoImage);
    m_OnEventVideoImage = callback;
}

void HKIndustrialCameraDevice::initLib()
{
    if (!m_lib.isLoaded())
    {
        m_lib.setFileName("HKIndustrialCameraLibrary");
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
    HKICD_FUNC_LOAD(IsDeviceConnected);
    HKICD_FUNC_LOAD(StartCamera);
    HKICD_FUNC_LOAD(StopCamera);
    HKICD_FUNC_LOAD(TakePhoto);
    HKICD_FUNC_LOAD(BeginCalibrate);
    HKICD_FUNC_LOAD(EndCalibrate);
    HKICD_FUNC_LOAD(GetCalibratePos);
    HKICD_FUNC_LOAD(CalibrateSampling);
    HKICD_FUNC_LOAD(UpdateCalibrateSampling);
    HKICD_FUNC_LOAD(CalcGetCalibrateResult);
    HKICD_FUNC_LOAD(GenerateCalibrateFile);
    HKICD_FUNC_LOAD(CreateUserCoordinate);
    HKICD_FUNC_LOAD(GetIntValueEx);
    HKICD_FUNC_LOAD(SetIntValueEx);
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
}

void HKIndustrialCameraDevice::uninitLib()
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
    HKICM_FUNC_PTR_MEM_NULL(IsDeviceConnected);
    HKICM_FUNC_PTR_MEM_NULL(StartCamera);
    HKICM_FUNC_PTR_MEM_NULL(StopCamera);
    HKICM_FUNC_PTR_MEM_NULL(TakePhoto);
    HKICM_FUNC_PTR_MEM_NULL(BeginCalibrate);
    HKICM_FUNC_PTR_MEM_NULL(EndCalibrate);
    HKICM_FUNC_PTR_MEM_NULL(GetCalibratePos);
    HKICM_FUNC_PTR_MEM_NULL(CalibrateSampling);
    HKICM_FUNC_PTR_MEM_NULL(UpdateCalibrateSampling);
    HKICM_FUNC_PTR_MEM_NULL(CalcGetCalibrateResult);
    HKICM_FUNC_PTR_MEM_NULL(GenerateCalibrateFile);
    HKICM_FUNC_PTR_MEM_NULL(CreateUserCoordinate);
    HKICM_FUNC_PTR_MEM_NULL(GetIntValueEx);
    HKICM_FUNC_PTR_MEM_NULL(SetIntValueEx);
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
}

bool HKIndustrialCameraDevice::IsDeviceAccessible(const QString& strIdetify)
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

QList<CameraInfo> HKIndustrialCameraDevice::search()
{
    QList<CameraInfo> ret;
    if (!m_pfnSearchCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve SearchCamera function";
        return ret;
    }

    CameraDeviceInfoIndustrial info[256];
    memset(info, 0, sizeof(CameraDeviceInfoIndustrial)*256);
    int iCount = m_pfnSearchCamera(m_pHandler, info);
    for (int i=0; i<iCount; ++i)
    {
        CameraInfo ci;
        ci.strIdentify = info[i].szIdentifyName;
        ci.bDeviceAccessible = IsDeviceAccessible(ci.strIdentify);

        MV_CC_DEVICE_INFO_INDUSTRIAL* pDeviceInfo = &(info[i].info);

        int nMac1 = ((pDeviceInfo->nMacAddrHigh & 0x0000ff00) >> 8);
        int nMac2 = (pDeviceInfo->nMacAddrHigh & 0x000000ff);
        int nMac3 = ((pDeviceInfo->nMacAddrLow & 0xff000000) >> 24);
        int nMac4 = ((pDeviceInfo->nMacAddrLow & 0x00ff0000) >> 16);
        int nMac5 = ((pDeviceInfo->nMacAddrLow & 0x0000ff00) >> 8);
        int nMac6 = (pDeviceInfo->nMacAddrLow & 0x000000ff);
        ci.strMacAddress = QString::asprintf("%02X:%02X:%02X:%02X:%02X:%02X",nMac1, nMac2, nMac3, nMac4, nMac5, nMac6);

        if (MV_GIGE_DEVICE_INDUSTRIAL == pDeviceInfo->nTLayerType)
        {
            int nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            int nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            int nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            int nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);
            ci.strIpAddress = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

            nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentSubNetMask & 0xff000000) >> 24);
            nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentSubNetMask & 0x00ff0000) >> 16);
            nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentSubNetMask & 0x0000ff00) >> 8);
            nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nCurrentSubNetMask & 0x000000ff);
            ci.strSubNetMask = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

            nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nDefultGateWay & 0xff000000) >> 24);
            nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nDefultGateWay & 0x00ff0000) >> 16);
            nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nDefultGateWay & 0x0000ff00) >> 8);
            nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nDefultGateWay & 0x000000ff);
            ci.strGateWay = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

            nIp1 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nNetExport & 0xff000000) >> 24);
            nIp2 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nNetExport & 0x00ff0000) >> 16);
            nIp3 = ((pDeviceInfo->SpecialInfo.stGigEInfo.nNetExport & 0x0000ff00) >> 8);
            nIp4 = (pDeviceInfo->SpecialInfo.stGigEInfo.nNetExport & 0x000000ff);
            ci.strNetExportAddress = QString::asprintf("%d.%d.%d.%d",nIp1, nIp2, nIp3, nIp4);

            ci.strSerialNumber = (const char*)(pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
            ci.strManufacturerName = (const char*)(pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName);
            ci.strVersion = (const char*)(pDeviceInfo->SpecialInfo.stGigEInfo.chDeviceVersion);
            ci.strModelName = (const char*)(pDeviceInfo->SpecialInfo.stGigEInfo.chModelName);
        }
        else if (MV_USB_DEVICE_INDUSTRIAL == pDeviceInfo->nTLayerType)
        {
            ci.strSerialNumber = (const char*)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
            ci.strManufacturerName = (const char*)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chManufacturerName);
            ci.strVersion = (const char*)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chDeviceVersion);
            ci.strModelName = (const char*)(pDeviceInfo->SpecialInfo.stUsb3VInfo.chModelName);
        }
        ret.push_back(ci);
    }
    m_iErrCode = DT_NO_ERROR;
    m_strErrMsg = "";

    return ret;
}

bool HKIndustrialCameraDevice::setCameraIp(const QString& strConnect,const MyCameraIpInfo &info)
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

bool HKIndustrialCameraDevice::openCamera(const QString &strConnect)
{
    if (!m_pfnConnectCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve ConnectCamera function";
        return false;
    }
    int nRet = m_pfnConnectCamera(m_pHandler, strConnect.toStdString().c_str());
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

void HKIndustrialCameraDevice::closeCamera()
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

bool HKIndustrialCameraDevice::isConnected()
{
    if (!m_pfnIsDeviceConnected || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve IsDeviceConnected function";
        return false;
    }
    int nRet = m_pfnIsDeviceConnected(m_pHandler);
    m_iErrCode = DT_NO_ERROR;
    m_strErrMsg = "";
    return 0 == nRet;
}

void HKIndustrialVideoCallback(const ImageDataIndustrial* pData, void* pArgs)
{
    HKIndustrialCameraDevice* pCamera = (HKIndustrialCameraDevice*)pArgs;
    if (pData->pImageData)
    {
        QImage picture(pData->pImageData, pData->iWidth, pData->iHeight, pData->iImgStep, QImage::Format_RGB888);
        if(!picture.isNull())
        {
            std::lock_guard<std::mutex> guard(pCamera->m_mtxEventVideoImage);
            if (pCamera->m_OnEventVideoImage)
            {
                pCamera->m_OnEventVideoImage(picture);
            }
        }
        else
        {
            qDebug()<<"HKIndustrialVideoCallback-->load image data fail";
        }
    }
}

bool HKIndustrialCameraDevice::startVideo()
{
    if (!m_pfnStartCamera || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve StartCamera function";
        return false;
    }
    int nRet = m_pfnStartCamera(m_pHandler, &HKIndustrialVideoCallback, this);
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

void HKIndustrialCameraDevice::stopVideo()
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

static void HKIndustrialTakePictureCallback(const ImageDataIndustrial* pData, void* pArgs)
{
    QImage* pImage = (QImage*)pArgs;
    if (pData->pImageData)
    {
        QImage img(pData->pImageData, pData->iWidth, pData->iHeight, pData->iImgStep, QImage::Format_RGB888);
        *pImage = img.copy();
    }
}
QImage HKIndustrialCameraDevice::takePhoto()
{
    if (!m_pfnTakePhoto || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve TakePhoto function";
        return QImage();
    }

    QImage picture;
    int nRet = m_pfnTakePhoto(m_pHandler, &HKIndustrialTakePictureCallback, &picture);
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
    }
    return picture;
}

QList<MyPointF6D> HKIndustrialCameraDevice::getCalibratePos(const MyPointF3D &flangleCenter, const MyPointF6D &robotPos)
{
    QList<MyPointF6D> retPoint;
    if (!m_pfnGetCalibratePos || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve GetCalibratePos function";
        return retPoint;
    }

    Point3DIndustrial flangle;
    copyValueFrom(flangleCenter, flangle);

    MyPointIndustrial robot;
    copyValueFrom(robotPos, robot);

    MyPointIndustrial outPos[256];
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

bool HKIndustrialCameraDevice::calcGetCalibrateResult(MyPointF6D &avgValue, MyPointF6D &maxValue)
{
    if (!m_pfnCalcGetCalibrateResult || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve CalcGetCalibrateResult function";
        return false;
    }
    ErrorValueIndustrial avgErr;
    ErrorValueIndustrial maxErr;
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

bool HKIndustrialCameraDevice::generateCalibrateFile(const QString &strSaveFileFullName)
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

bool HKIndustrialCameraDevice::createUserCoordinate(const QString &strCalibrateFile, const MyPointF6D &robotPos,
                                              MyPointF6D& coordinatePos, int& iId, QImage& retImg)
{
    if (!m_pfnCreateUserCoordinate || !m_pHandler)
    {
        m_iErrCode = DT_ERR_LIB_FUNC_DT_ERR_LOAD;
        m_strErrMsg = "can not resolve CreateUserCoordinate function";
        return false;
    }

    MyPointIndustrial robot,coordinate;
    copyValueFrom(robotPos, robot);
    QByteArray arrName = strCalibrateFile.toLocal8Bit();
    int nRet = m_pfnCreateUserCoordinate(m_pHandler, arrName.constData(), &robot, &coordinate,&iId,
                                         &HKIndustrialTakePictureCallback, &retImg);
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

bool HKIndustrialCameraDevice::beginCalibrate()
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

int HKIndustrialCameraDevice::endCalibrate()
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

bool HKIndustrialCameraDevice::calibrateSampling(const MyPointF6D &robotPos, QImage& retImg)
{
    if (!m_pfnCalibrateSampling || !m_pHandler)
    {
        m_iErrCode = DT_ERR_CALIBRATE_SAMPLING;
        m_strErrMsg = "can not resolve CalibrateSampling function";
        return false;
    }

    MyPointIndustrial robot;
    copyValueFrom(robotPos, robot);
    int nRet = m_pfnCalibrateSampling(m_pHandler, &robot, &HKIndustrialTakePictureCallback, &retImg);
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

bool HKIndustrialCameraDevice::updateCalibrateSampling(const MyPointF6D &robotPos, int idxUpdate, QImage &retImg)
{
    if (!m_pfnUpdateCalibrateSampling || !m_pHandler)
    {
        m_iErrCode = DT_ERR_UPDATE_CALIBRATE_SAMPLING;
        m_strErrMsg = "can not resolve CalibrateSampling function";
        return false;
    }

    MyPointIndustrial robot;
    copyValueFrom(robotPos, robot);
    int nRet = m_pfnUpdateCalibrateSampling(m_pHandler, &robot, idxUpdate, &HKIndustrialTakePictureCallback, &retImg);
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

bool HKIndustrialCameraDevice::GetIntValueEx(const QString& strKey, MVCC_INTVALUE_EX& stIntValue)
{
    if (!m_pfnGetIntValueEx || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetIntValueEx function";
        return false;
    }

    int nRet = m_pfnGetIntValueEx(m_pHandler, strKey.toStdString().c_str(), &stIntValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetIntValueEx fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }
    return true;
}

bool HKIndustrialCameraDevice::SetIntValueEx(const QString& strKey, int64_t nValue)
{
    if (!m_pfnSetIntValueEx || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve SetIntValueEx function";
        return false;
    }

    int nRet = m_pfnSetIntValueEx(m_pHandler, strKey.toStdString().c_str(), nValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("SetIntValueEx fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::GetEnumValue(const QString& strKey, MVCC_ENUMVALUE& stEnumValue)
{
    if (!m_pfnGetEnumValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetEnumValue function";
        return false;
    }

    int nRet = m_pfnGetEnumValue(m_pHandler, strKey.toStdString().c_str(), &stEnumValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetEnumValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::SetEnumValue(const QString& strKey, unsigned int nValue)
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
        m_strErrMsg = QString::asprintf("SetEnumValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::SetEnumValueByString(const QString& strKey, const QString& strValue)
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
        m_strErrMsg = QString::asprintf("SetEnumValueByString fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::GetFloatValue(const QString& strKey, MVCC_FLOATVALUE& stFloatValue)
{
    if (!m_pfnGetFloatValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetFloatValue function";
        return false;
    }

    int nRet = m_pfnGetFloatValue(m_pHandler, strKey.toStdString().c_str(), &stFloatValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetFloatValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::SetFloatValue(const QString& strKey, float fValue)
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
        m_strErrMsg = QString::asprintf("SetFloatValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::GetBoolValue(const QString& strKey, bool& bValue)
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
        m_strErrMsg = QString::asprintf("GetBoolValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::SetBoolValue(const QString& strKey, bool bValue)
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
        m_strErrMsg = QString::asprintf("SetBoolValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::GetStringValue(const QString& strKey, MVCC_STRINGVALUE& stStringValue)
{
    if (!m_pfnGetStringValue || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve GetStringValue function";
        return false;
    }

    int nRet = m_pfnGetStringValue(m_pHandler, strKey.toStdString().c_str(), &stStringValue);
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("GetStringValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::SetStringValue(const QString& strKey, const QString& strValue)
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
        m_strErrMsg = QString::asprintf("SetStringValue fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::CommandExecute(const QString& strKey)
{
    if (!m_pfnCommandExecute || !m_pHandler)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        m_strErrMsg = "can not resolve CommandExecute function";
        return false;
    }

    int nRet = m_pfnCommandExecute(m_pHandler, strKey.toStdString().c_str());
    if (0 != nRet)
    {
        m_iErrCode = DT_ERR_GSET_TYPE_VALUE;
        char szMsg[1024]="";
        m_pfnGetErrMsg(m_pHandler, szMsg);
        m_strErrMsg = QString::asprintf("CommandExecute fail,%s",szMsg);

        return false;
    }
    else
    {
        m_iErrCode = DT_NO_ERROR;
        m_strErrMsg = "";
    }

    return true;
}

bool HKIndustrialCameraDevice::getCameraParam(const QJsonObject& property, QJsonObject& result)
{
    GetCameraParamRequestBean req;
    req.fromJson(property);
    GetCameraParamResponseResult response;

    for(auto itr=req.property.begin(); itr!=req.property.end(); ++itr)
    {
        GetCameraParamResponseBean bean;
        if (itr->compare("Gain")==0)
        {
            MVCC_FLOATVALUE stFloatValue;
            memset(&stFloatValue, 0, sizeof(stFloatValue));
            GetFloatValue("Gain", stFloatValue);
            bean.code = m_iErrCode;
            bean.errmsg = m_strErrMsg;
            bean.value = stFloatValue.fCurValue;
        }
        else if (itr->compare("ExposureTime")==0)
        {
            MVCC_FLOATVALUE stFloatValue;
            memset(&stFloatValue, 0, sizeof(stFloatValue));
            GetFloatValue("ExposureTime", stFloatValue);
            bean.code = m_iErrCode;
            bean.errmsg = m_strErrMsg;
            bean.value = stFloatValue.fCurValue;
        }
        else if (itr->compare("ExposureAuto")==0)
        {
            MVCC_ENUMVALUE stEnumValue;
            memset(&stEnumValue, 0, sizeof(stEnumValue));
            GetEnumValue("ExposureAuto", stEnumValue);
            bean.code = m_iErrCode;
            bean.errmsg = m_strErrMsg;
            bean.value = (stEnumValue.nCurValue!=MV_GAIN_MODE_OFF);
        }
        else
        {
            bean.code = DT_ERR_INVALID_PARAMS;
            bean.errmsg = DError::getErrMsg(bean.code);
        }
        response.m_data.propertyValue.insert(*itr, bean);
    }

    result = response.toJsonObject();

    return true;
}

bool HKIndustrialCameraDevice::setCameraParam(const QJsonObject& property, QJsonObject& result)
{
    SetCameraParamRequestBean2 req;
    req.fromJson(property);
    SetCameraParamResponseResult response;

    for(auto itr=req.propertyValue.begin(); itr!=req.propertyValue.end(); ++itr)
    {
        SetCameraParamResponseBean bean;
        if (itr.key().compare("Gain")==0)
        {
            //设置增益前先把自动增益关闭，失败无需返回
            do
            {
                if(!SetEnumValue("GainAuto", MV_GAIN_MODE_OFF)){
                    m_strErrMsg.prepend("GainAuto(off):");
                    break;
                }
                if(!SetFloatValue("Gain", itr.value().value.toDouble())){
                    m_strErrMsg.prepend("Gain:");
                    break;
                }
            }while(false);
            bean.code = m_iErrCode;
            bean.errmsg = m_strErrMsg;
        }
        else if (itr.key().compare("ExposureTime")==0)
        {
            //设置曝光时间，调节这两个曝光模式，才能让曝光时间生效：（每个函数都要判断返回值是否MV_OK）
            do
            {
                /*if (!SetEnumValue("ExposureMode", MV_EXPOSURE_MODE_TIMED)){
                    m_strErrMsg.prepend("ExposureMode:");
                    break;
                }*/
                if (!SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF)){
                    m_strErrMsg.prepend("ExposureAuto(off):");
                    break;
                }
                if (!SetFloatValue("ExposureTime", itr.value().value.toDouble())){
                    m_strErrMsg.prepend("ExposureTime:");
                    break;
                }
            }while(false);

            bean.code = m_iErrCode;
            bean.errmsg = m_strErrMsg;
        }
        else if (itr.key().compare("ExposureAuto")==0)
        {
            unsigned int iValue = itr.value().value.toBool()?MV_EXPOSURE_AUTO_MODE_CONTINUOUS:MV_EXPOSURE_AUTO_MODE_OFF;
            do
            {
                if (!SetEnumValue("ExposureAuto", iValue)){
                    m_strErrMsg.prepend("ExposureAuto:");
                    break;
                }
                if (iValue == MV_EXPOSURE_AUTO_MODE_CONTINUOUS)
                {//连续曝光模式需要打开连续增益模式
                    if (!SetEnumValue("GainAuto", MV_GAIN_MODE_CONTINUOUS)){
                        m_strErrMsg.prepend("GainAuto(continuous):");
                        break;
                    }
                }
                else
                {//关闭曝光时则关闭自动增益模式
                    if (!SetEnumValue("GainAuto", MV_GAIN_MODE_OFF)){
                        m_strErrMsg.prepend("GainAuto(off):");
                        break;
                    }
                    if (!SetFloatValue("Gain", 0.0f)){
                        m_strErrMsg.prepend("Gain:");
                        break;
                    }
                }
            }while(false);
            bean.code = m_iErrCode;
            bean.errmsg = m_strErrMsg;
        }
        else
        {
            bean.code = DT_ERR_INVALID_PARAMS;
            bean.errmsg = DError::getErrMsg(bean.code);
        }
        response.m_data.propertyValue.insert(itr.key(), bean);
    }

    result = response.toJsonObject();

    return true;
}
