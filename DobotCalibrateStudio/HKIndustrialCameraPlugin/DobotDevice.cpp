#include "DobotDevice.h"
#include <QDateTime>
#include <QDir>
#include <QBuffer>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <memory>
#ifdef Q_OS_WIN
#include <iphlpapi.h>
#endif
#include "DError.h"
#include "HKIndustrialCameraDevice.h"
#include "NullDataBean.h"
#include "DataBean/SearchCameraBean.h"
#include "DataBean/OpenCameraBean.h"
#include "DataBean/CloseCameraBean.h"
#include "DataBean/StartVideoBean.h"
#include "DataBean/StopVideoBean.h"
#include "DataBean/TakePhotoBean.h"
#include "DataBean/GetCalibratePos.h"
#include "DataBean/CalcGetCalibrateResult.h"
#include "DataBean/GenerateCalibrateFile.h"
#include "DataBean/GenerateCalibrateFileV2.h"
#include "DataBean/CreateUserCoordinate.h"
#include "DataBean/CreateUserCoordinateV2.h"
#include "DataBean/BeginCalibrateBean.h"
#include "DataBean/EndCalibrateBean.h"
#include "DataBean/CalibrateSampling.h"
#include "DataBean/SetIpConfigBean.h"
#include "DataBean/CameraParamBean.h"

CDobotDevice::CDobotDevice(QObject *parent) : QObject(parent)
{
    initFunctionMapper();
    m_pCameraDevice = new HKIndustrialCameraDevice(this);
}

CDobotDevice::~CDobotDevice()
{
    closeNotResponse();
    m_pCameraDevice->deleteLater();
}

/*************************************************************************************************
 *************************************************************************************************/
void CDobotDevice::doCmd(const CMessageRequest &msg)
{
    if (m_mapperFunction.contains(msg.getApi()))
    {
        RequestJsonRpc rpc;
        rpc.strSenderId = msg.getSenderId();
        rpc.rpcId = msg.getId();
        rpc.strApi = msg.getApi();

        m_mtxRequestCacheId.lock();
        m_requestCacheId.insert(msg.getMsgUuid(),rpc);
        m_mtxRequestCacheId.unlock();

        auto pfn = m_mapperFunction.value(msg.getApi());
        (this->*pfn)(msg);
    }
    else
    {
        qDebug()<<"not find api:"<<msg.getApi();
        CNullDataBean result;
        CMessageResponse response(msg);
        response.setCode(DT_ERR_INVALID_METHOD);
        response.setErrMsg(DError::getErrMsg(response.getCode()));
        response.setResult(result.toJsonObject());
        emitResponseMsg(response);
    }
}

void CDobotDevice::emitResponseMsg(const CMessageResponse& msg)
{
    emit doResponseMsg(msg.toJsonObject(), QPrivateSignal());
}

void CDobotDevice::sendResponseSuccess(const QString &strMsgUuid, const CJsonMessage &responseData, bool bAutoDeleteCacheId/*=true*/)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    auto itr = m_requestCacheId.find(strMsgUuid);
    if (itr != m_requestCacheId.end())
    {
        CMessageResponse msg;
        msg.setId(itr.value().rpcId);
        msg.setCode(DT_NO_ERROR);
        msg.setErrMsg("");
        msg.setSenderId(itr.value().strSenderId);
        msg.setMsgUuid(strMsgUuid);
        msg.setResult(responseData.toJsonObject());
        msg.setPrintLog(responseData.isPrintLog());

        if (bAutoDeleteCacheId) m_requestCacheId.erase(itr);

        emitResponseMsg(msg);
    }
    else
    {
        qCritical()<<"not found msguuid("<<strMsgUuid<<"),can not response!!!!";
    }
}

void CDobotDevice::sendResponseError(const QString &strMsgUuid, const int iErrCode, const QString &strErrMsg, bool bAutoDeleteCacheId/*=true*/)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    auto itr = m_requestCacheId.find(strMsgUuid);
    if (itr != m_requestCacheId.end())
    {
        CNullDataBean result;
        CMessageResponse msg;
        msg.setId(itr.value().rpcId);
        msg.setCode(iErrCode);
        msg.setErrMsg(DError::getErrMsg(msg.getCode(), strErrMsg));
        msg.setSenderId(itr.value().strSenderId);
        msg.setMsgUuid(strMsgUuid);
        msg.setResult(result.toJsonObject());

        if (bAutoDeleteCacheId) m_requestCacheId.erase(itr);

        emitResponseMsg(msg);
    }
    else
    {
        qCritical()<<"not found msguuid("<<strMsgUuid<<"),can not response!!!!";
    }
}

void CDobotDevice::sendResponseError(const QString &strMsgUuid, const CJsonMessage& responseData, const int iErrCode, const QString &strErrMsg, bool bAutoDeleteCacheId/*=true*/)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    auto itr = m_requestCacheId.find(strMsgUuid);
    if (itr != m_requestCacheId.end())
    {
        CMessageResponse msg;
        msg.setId(itr.value().rpcId);
        msg.setCode(iErrCode);
        msg.setErrMsg(DError::getErrMsg(msg.getCode(), strErrMsg));
        msg.setSenderId(itr.value().strSenderId);
        msg.setMsgUuid(strMsgUuid);
        msg.setResult(responseData.toJsonObject());
        msg.setPrintLog(responseData.isPrintLog());

        if (bAutoDeleteCacheId) m_requestCacheId.erase(itr);

        emitResponseMsg(msg);
    }
    else
    {
        qCritical()<<"not found msguuid("<<strMsgUuid<<"),can not response!!!!";
    }
}

void CDobotDevice::deleteAllCacheId()
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    m_requestCacheId.clear();
}

void CDobotDevice::deleteCacheId(const QString &strMsgUuid)
{
    QMutexLocker guard(&m_mtxRequestCacheId);
    m_requestCacheId.remove(strMsgUuid);
}

bool CDobotDevice::checkIpAddressValid(const QString &strIp)
{
    QRegExp reg("^((25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)\\.){3}(25[0-5]|2[0-4]\\d|1\\d{2}|[1-9]?\\d)$");
    if (!strIp.isEmpty() && reg.exactMatch(strIp))
    {
        return true;
    }
    return false;
}

void CDobotDevice::closeNotResponse()
{
    m_pCameraDevice->closeCamera();
    deleteAllCacheId();
}

QByteArray CDobotDevice::image2Base64Byte(const QImage& img, const char *format/* = "jpg"*/, int quality)
{
    QByteArray data;
    QBuffer buffer(&data);
    img.save(&buffer, format, quality);
    return data.toBase64();
}

QString CDobotDevice::fixSavePath(const QString &strPath)
{
    QString strTmp;
    if (strPath.isEmpty())
    {
        return strTmp;
        /*//路径为空就不处理吧
        static QString strSavePath;
        if (strSavePath.isEmpty())
        {
            QDir dir(QCoreApplication::applicationDirPath());
            dir.mkdir("temp_image");
            dir.cd("temp_image");
            strSavePath = dir.absolutePath()+"/";
            strSavePath = QDir::toNativeSeparators(strSavePath);
        }
        strTmp = strSavePath;
         */
    }
    else
    {
        strTmp = strPath;
        if (!strPath.endsWith('/') && !strPath.endsWith('\\'))
        {
            strTmp += '/';
        }
        strTmp = QDir::toNativeSeparators(strTmp);
        QDir dir(strTmp);
        if (!dir.exists()){
            dir.mkpath(strTmp);
        }
    }
    return strTmp;
}

QString CDobotDevice::getMyCachePath() const
{
    static QString strSavePath;
    QFileInfo info(strSavePath);
    if (strSavePath.isEmpty() || !info.isDir())
    {
        QDir dir(QCoreApplication::applicationDirPath());
        dir.mkdir("cache_ind");
        dir.cd("cache_ind");
        strSavePath = dir.absolutePath()+"/";
        strSavePath = QDir::toNativeSeparators(strSavePath);
    }
    return strSavePath;
}

QString CDobotDevice::getLastTempCalibrateFile() const
{
    QDir dir(getMyCachePath());
    QStringList files = dir.entryList(QStringList()<<"dobotLastTempCalFile.*", QDir::Filter::Files);
    if (files.isEmpty())
    {
        return "";
    }
    while (files.size()>1)
    {
        QFile::remove(dir.absoluteFilePath(files.takeLast()));
    }
    return QDir::toNativeSeparators(dir.absoluteFilePath(files[0]));
}

void CDobotDevice::updateLastTempCalibrateFile(const QString &strSrcFile) const
{
    QFileInfo fi(strSrcFile);
    QString strFile = getLastTempCalibrateFile();
    if (strFile.isEmpty())
    {
        QDir dir(getMyCachePath());
        strFile = QDir::toNativeSeparators(dir.absoluteFilePath(QString("dobotLastTempCalFile.%1").arg(fi.suffix())));
    }
    else
    {
        QFile::remove(strFile);
        QFileInfo fiTmp(strFile);
        if (fiTmp.suffix() != fi.suffix())
        {
            QDir dir(getMyCachePath());
            strFile = QDir::toNativeSeparators(dir.absoluteFilePath(QString("dobotLastTempCalFile.%1").arg(fi.suffix())));
        }
    }
    QFile::copy(strSrcFile, strFile);
}

static QString getDefaultGateWayByNetIp(const QString& strNetIp)
{
    QString strGateWay="0.0.0.0";
#ifdef Q_OS_WIN
    PIP_ADAPTER_INFO pIpAdapterInfo = new(std::nothrow) IP_ADAPTER_INFO();
    if (!pIpAdapterInfo) return strGateWay;
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
        // DT_ERR_BUFFER_OVERFLOW：内存空间不够
        delete pIpAdapterInfo;
        // 重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        if (!pIpAdapterInfo) return strGateWay;
        // 再次调用GetAdaptersInfo
        nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);
    }
    if (ERROR_SUCCESS != nRel)
    {
        delete pIpAdapterInfo;
        return strGateWay;
    }
    std::shared_ptr<IP_ADAPTER_INFO> sptr(pIpAdapterInfo,[](PIP_ADAPTER_INFO p){
        delete p;
    });
    while (pIpAdapterInfo)
    {
        switch(pIpAdapterInfo->Type)
        {
        case MIB_IF_TYPE_OTHER:
            qDebug()<<"MIB_IF_TYPE_OTHER";
            break;
        case MIB_IF_TYPE_ETHERNET:
            qDebug()<<"MIB_IF_TYPE_ETHERNET";
            break;
        case MIB_IF_TYPE_TOKENRING:
            qDebug()<<"MIB_IF_TYPE_TOKENRING";
            break;
        case MIB_IF_TYPE_FDDI:
            qDebug()<<"MIB_IF_TYPE_FDDI";
            break;
        case MIB_IF_TYPE_PPP:
            qDebug()<<"MIB_IF_TYPE_PPP";
            break;
        case MIB_IF_TYPE_LOOPBACK:
            qDebug()<<"MIB_IF_TYPE_LOOPBACK";
            break;
        case MIB_IF_TYPE_SLIP:
            qDebug()<<"MIB_IF_TYPE_SLIP";
            break;
        default:
            qDebug()<<"MIB_IF_TYPE_XXXXXX:"<<pIpAdapterInfo->Type;
            break;
        }
        /*
         * 网卡的mac地址
         * pIpAdapterInfo->AddressLength;
         * pIpAdapterInfo->Address;
         *
         *
         * 网卡名称
         * pIpAdapterInfo->AdapterName
         *
         * 网卡描述
         * pIpAdapterInfo->Description
         *
         * 网关
         * pIpAdapterInfo->GatewayList.IpAddress.String
        */
        //可能网卡有多IP
        IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
        do{
            if (QString(pIpAddrString->IpAddress.String) == strNetIp)
            {
                strGateWay = QString(pIpAdapterInfo->GatewayList.IpAddress.String);
                return strGateWay;
            }
            pIpAddrString=pIpAddrString->Next;
        } while (pIpAddrString);
        pIpAdapterInfo = pIpAdapterInfo->Next;
    }
#endif
    return strGateWay;
}

static CNetcardInfoBean getNetcardInfo(const QString& strNet)
{
    quint32 iNetIp = QHostAddress(strNet).toIPv4Address();
    CNetcardInfoBean bean;
    foreach (QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        if (/*netInterface.isValid() && */
                !netInterface.flags().testFlag(QNetworkInterface::IsLoopBack)
                && netInterface.flags().testFlag(QNetworkInterface::IsRunning))
        {
            QList<QNetworkAddressEntry> entryList = netInterface.addressEntries();
            foreach(QNetworkAddressEntry entry, entryList)
            {
                if (QAbstractSocket::IPv4Protocol != entry.ip().protocol())
                    continue;

                if (entry.ip().toIPv4Address() == iNetIp)
                {
                    bean.name = netInterface.humanReadableName();
                    bean.ip = strNet;
                    bean.subnetmask = entry.netmask().toString();
                    bean.gateway = getDefaultGateWayByNetIp(strNet);
                    bean.mac = netInterface.hardwareAddress();
                    return bean;
                }
            }
        }
    }
    return bean;
}

void CDobotDevice::search(const CMessageRequest &msg)
{
    QList<CameraInfo> ret = m_pCameraDevice->search();

    //还要将该设备所在的网卡信息加进去

    CSearchCameraResponseResult result;
    for(auto itr=ret.begin(); itr!=ret.end(); ++itr)
    {
        CSearchCameraResponseBean bean;
        bean.identify = itr->strIdentify;
        bean.ip = itr->strIpAddress;
        bean.mac = itr->strMacAddress;
        bean.subnetmask = itr->strSubNetMask;
        bean.gateway = itr->strGateWay;
        bean.sn = itr->strSerialNumber;
        bean.manufacturer = itr->strManufacturerName;
        bean.version = itr->strVersion;
        bean.modelname = itr->strModelName;
        bean.accessible = itr->bDeviceAccessible;
        bean.netcardinfo = getNetcardInfo(itr->strNetExportAddress);
        result.m_data.push_back(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::setIpConfig(const CMessageRequest &msg)
{
    CSetIpConfigRequestParams request;
    request.fromJson(msg.getParams());

    if (!checkIpAddressValid(request.m_data.ip) ||
            !checkIpAddressValid(request.m_data.subnetmask) ||
            !checkIpAddressValid(request.m_data.gateway))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    MyCameraIpInfo info;
    info.strIpAddress = request.m_data.ip;
    info.strSubNetMask = request.m_data.subnetmask;
    info.strGateWay = request.m_data.gateway;
    bool ret = m_pCameraDevice->setCameraIp(request.m_data.identify, info);

    CSetIpConfigResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::open(const CMessageRequest &msg)
{
    COpenCameraRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->openCamera(request.m_data.identify);

    COpenCameraResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::close(const CMessageRequest &msg)
{
    m_pCameraDevice->closeCamera();
    CCloseCameraResponseResult result;
    sendResponseSuccess(msg.getMsgUuid(), result);
    deleteAllCacheId();
}

void CDobotDevice::startVideo(const CMessageRequest &msg)
{
    //if (m_pCameraDevice->inherits("HKIndustrialCameraDevice"))
    QString strMsgUuid = msg.getMsgUuid();
    static_cast<HKIndustrialCameraDevice*>(m_pCameraDevice)->setVideoImageDataCallback([this,strMsgUuid](const QImage& img){
        CStartVideoResponseResult result;
        result.setPrintLog(false); //视频图片不要打印，否则日志太多
        result.m_data.frame = image2Base64Byte(img);
        sendResponseSuccess(strMsgUuid, result, false);
    });
    bool ret = m_pCameraDevice->startVideo();
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
    else
    {
        m_strVideoLastMsgUuid = strMsgUuid;
        CStartVideoResponseResult result;
        result.m_data.frame = "";
        sendResponseSuccess(strMsgUuid, result, false);
    }
}

void CDobotDevice::stopVideo(const CMessageRequest &msg)
{
    /*拍视频时，因为msguuid并没有删除，否则下一次无法主动推送给别人，所以当停止时，则需要删掉缓存，否则遗留了。*/
    if (!m_strVideoLastMsgUuid.isEmpty())
    {
        deleteCacheId(m_strVideoLastMsgUuid);
        m_strVideoLastMsgUuid = "";
    }

    m_pCameraDevice->stopVideo();
    CStopVideoResponseBean result;
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::takePhoto(const CMessageRequest &msg)
{
    QImage img = m_pCameraDevice->takePhoto();
    if (img.isNull())
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
    else
    {
        CTakePhotoRequestParams request;
        request.fromJson(msg.getParams());

        CTakePhotoResponseResult result;
        result.m_data.frame = image2Base64Byte(img);

        if (request.m_data.savePath.isEmpty())
        {
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
            const QString strSavePath = fixSavePath(request.m_data.savePath) + strFileName;
            if (img.save(strSavePath))
            {
                result.m_data.fileName = strFileName;
                sendResponseSuccess(msg.getMsgUuid(), result);
            }
            else
            {
                sendResponseError(msg.getMsgUuid(), DT_ERR_SAVE_FILE);
            }
        }
    }
}

void CDobotDevice::getCalibratePos(const CMessageRequest &msg)
{
    CGetCalibratePosRequestParams request;
    request.fromJson(msg.getParams());

    MyPointF3D f3d;
    f3d.x = request.m_data.flangleCenter.x;
    f3d.y = request.m_data.flangleCenter.y;
    f3d.z = request.m_data.flangleCenter.z;

    MyPointF6D f6d;
    f6d.x = request.m_data.robot.x;
    f6d.y = request.m_data.robot.y;
    f6d.z = request.m_data.robot.z;
    f6d.rx = request.m_data.robot.rx;
    f6d.ry = request.m_data.robot.ry;
    f6d.rz = request.m_data.robot.rz;

    QList<MyPointF6D> ret = m_pCameraDevice->getCalibratePos(f3d, f6d);

    CGetCalibratePosResponseResult result;
    for(auto itr=ret.begin(); itr!=ret.end(); ++itr)
    {
        CGetCalibratePosResponseBean bean;
        bean.x = itr->x;
        bean.y = itr->y;
        bean.z = itr->z;
        bean.rx = itr->rx;
        bean.ry = itr->ry;
        bean.rz = itr->rz;
        result.m_data.push_back(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::calcGetCalibrateResult(const CMessageRequest &msg)
{
    MyPointF6D avgValue,maxValue;
    bool ret = m_pCameraDevice->calcGetCalibrateResult(avgValue, maxValue);

    CCalcGetCalibrateResultResponseResult result;
    if (ret)
    {
        result.m_data.avg.x = avgValue.x;
        result.m_data.avg.y = avgValue.y;
        result.m_data.avg.z = avgValue.z;
        result.m_data.avg.ang0 = avgValue.rx;
        result.m_data.avg.ang1 = avgValue.ry;
        result.m_data.avg.ang2 = avgValue.rz;

        result.m_data.max.x = maxValue.x;
        result.m_data.max.y = maxValue.y;
        result.m_data.max.z = maxValue.z;
        result.m_data.max.ang0 = maxValue.rx;
        result.m_data.max.ang1 = maxValue.ry;
        result.m_data.max.ang2 = maxValue.rz;

        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::generateCalibrateFile(const CMessageRequest &msg)
{
    CGenerateCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());

    QString strSaveFile = QDir::toNativeSeparators(request.m_data.saveFileFullName);
    bool ret = m_pCameraDevice->generateCalibrateFile(strSaveFile);

    CGenerateCalibrateFileResponseResult result;
    if (ret)
    {
        //保存标定文件为临时文件，有用途
        updateLastTempCalibrateFile(strSaveFile);

        /*******************************************************/
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::generateCalibrateFileV2(const CMessageRequest &msg)
{
    CGenerateCalibrateFileV2RequestParams request;
    request.fromJson(msg.getParams());

    QString strSaveTmpFile = fixSavePath(getMyCachePath())+QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")+"."+request.m_data.type;
    bool ret = m_pCameraDevice->generateCalibrateFile(strSaveTmpFile);

    CGenerateCalibrateFileV2ResponseResult result;
    if (ret)
    {
        //保存标定文件为临时文件，有用途
        updateLastTempCalibrateFile(strSaveTmpFile);

        /*******************************************************/
        QFile file(strSaveTmpFile);
        if (file.open(QFile::ReadOnly))
        {
            result.m_data.content = file.readAll();
            file.close();
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            sendResponseError(msg.getMsgUuid(), DT_ERR_SAVE_FILE);
        }
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
    QFile::remove(strSaveTmpFile);
}

void CDobotDevice::createUserCoordinate(const CMessageRequest &msg)
{
    CCreateUserCoordinateRequestParams request;
    request.fromJson(msg.getParams());
    const QString strCalibrateFile = QDir::toNativeSeparators(request.m_data.calibrateFile);
    const bool isReturnFrame = request.m_data.returnFrame;

    MyPointF6D robotPos;
    robotPos.x = request.m_data.x;
    robotPos.y = request.m_data.y;
    robotPos.z = request.m_data.z;
    robotPos.rx = request.m_data.rx;
    robotPos.ry = request.m_data.ry;
    robotPos.rz = request.m_data.rz;

    MyPointF6D coordinatePos;
    int iId = -1;
    QImage img;

    bool ret = m_pCameraDevice->createUserCoordinate(strCalibrateFile,robotPos, coordinatePos, iId, img);

    CCreateUserCoordinateResultResponseResult result;
    result.m_data.x = coordinatePos.x;
    result.m_data.y = coordinatePos.y;
    result.m_data.z = coordinatePos.z;
    result.m_data.rx = coordinatePos.rx;
    result.m_data.ry = coordinatePos.ry;
    result.m_data.rz = coordinatePos.rz;
    result.m_data.id = iId;
    if (isReturnFrame)
    {
        result.m_data.frame = image2Base64Byte(img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (img.save(strSave))
        {
            result.m_data.fileName = strFileName;
        }
        else
        {
            qDebug()<<"create user coordinate result is ok,but save image file failed,msgid:"<<msg.getMsgUuid();
        }
    }

    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), result, m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::createUserCoordinateV2(const CMessageRequest &msg)
{
    CCreateUserCoordinateV2RequestParams request;
    request.fromJson(msg.getParams());

    if (request.m_data.calibrateFileContent.isEmpty())
    {
        QString strFile = getLastTempCalibrateFile();
        QFile file(strFile);
        if (file.open(QFile::ReadOnly))
        {
            request.m_data.calibrateFileContent = file.readAll();
            request.m_data.type = QFileInfo(strFile).suffix();
            file.close();
        }
        else
        {
            sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
            return ;
        }
    }

    const QString strCalibrateFile = fixSavePath(getMyCachePath())+QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz")+"."+request.m_data.type;
    QFile file(strCalibrateFile);
    if (file.open(QFile::WriteOnly))
    {
        file.write(request.m_data.calibrateFileContent.toUtf8());
        file.close();
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_SAVE_FILE);
        return ;
    }
    const bool isReturnFrame = request.m_data.returnFrame;

    MyPointF6D robotPos;
    robotPos.x = request.m_data.x;
    robotPos.y = request.m_data.y;
    robotPos.z = request.m_data.z;
    robotPos.rx = request.m_data.rx;
    robotPos.ry = request.m_data.ry;
    robotPos.rz = request.m_data.rz;

    MyPointF6D coordinatePos;
    int iId = -1;
    QImage img;

    bool ret = m_pCameraDevice->createUserCoordinate(strCalibrateFile,robotPos, coordinatePos, iId, img);

    CCreateUserCoordinateV2ResultResponseResult result;
    result.m_data.x = coordinatePos.x;
    result.m_data.y = coordinatePos.y;
    result.m_data.z = coordinatePos.z;
    result.m_data.rx = coordinatePos.rx;
    result.m_data.ry = coordinatePos.ry;
    result.m_data.rz = coordinatePos.rz;
    result.m_data.id = iId;
    if (isReturnFrame)
    {
        result.m_data.frame = image2Base64Byte(img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (img.save(strSave))
        {
            result.m_data.fileName = strFileName;
        }
        else
        {
            qDebug()<<"create user coordinate result is ok,but save image file failed,msgid:"<<msg.getMsgUuid();
        }
    }
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), result, m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
    QFile::remove(strCalibrateFile);
}

void CDobotDevice::beginCalibrate(const CMessageRequest &msg)
{
    bool ret = m_pCameraDevice->beginCalibrate();
    CBeginCalibrateResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::endCalibrate(const CMessageRequest &msg)
{
    int retCount = m_pCameraDevice->endCalibrate();
    CEndCalibrateResponseResult result;
    result.m_data.pointCount = retCount;
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::calibrateSampling(const CMessageRequest &msg)
{
    CCalibrateSamplingRequestParams request;
    request.fromJson(msg.getParams());
    const bool isReturnFrame = request.m_data.returnFrame;

    MyPointF6D robotPos;
    robotPos.x = request.m_data.x;
    robotPos.y = request.m_data.y;
    robotPos.z = request.m_data.z;
    robotPos.rx = request.m_data.rx;
    robotPos.ry = request.m_data.ry;
    robotPos.rz = request.m_data.rz;

    QImage img;

    bool ret = m_pCameraDevice->calibrateSampling(robotPos, img);

    CCalibrateSamplingResultResponseResult result;
    if (isReturnFrame)
    {
        result.m_data.frame = image2Base64Byte(img);
    }
    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (img.save(strSave))
        {
            result.m_data.fileName = strFileName;
        }
        else
        {
            qDebug()<<"calibreate sampling result is ok,but save image file failed,msgid:"<<msg.getMsgUuid();
        }
    }
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), result, m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::updateCalibrateSampling(const CMessageRequest &msg)
{
    CCalibrateSamplingRequestParams request;
    request.fromJson(msg.getParams());
    const bool isReturnFrame = request.m_data.returnFrame;
    int iUpdateIdx = request.m_data.index;

    MyPointF6D robotPos;
    robotPos.x = request.m_data.x;
    robotPos.y = request.m_data.y;
    robotPos.z = request.m_data.z;
    robotPos.rx = request.m_data.rx;
    robotPos.ry = request.m_data.ry;
    robotPos.rz = request.m_data.rz;

    QImage img;

    bool ret = m_pCameraDevice->updateCalibrateSampling(robotPos, iUpdateIdx, img);

    CCalibrateSamplingResultResponseResult result;
    if (isReturnFrame)
    {
        result.m_data.frame = image2Base64Byte(img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (img.save(strSave))
        {
            result.m_data.fileName = strFileName;
        }
        else
        {
            qDebug()<<"update calibreate sampling result is ok,but save image file failed,msgid:"<<msg.getMsgUuid();
        }
    }
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), result, m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getCameraParam(const CMessageRequest &msg)
{
    GetCameraParamRequestParams request;
    request.fromJson(msg.getParams());

    QJsonObject objResult;
    bool ret = m_pCameraDevice->getCameraParam(request.m_data.toJsonObject(), objResult);

    GetCameraParamResponseResult result;
    if (ret)
    {
        result.fromJson(objResult);
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::setCameraParam(const CMessageRequest &msg)
{
    SetCameraParamRequestParams request;
    request.fromJson(msg.getParams());

    QJsonObject objResult;
    bool ret = m_pCameraDevice->setCameraParam(request.m_data.toJsonObject(), objResult);

    SetCameraParamResponseResult result;
    if (ret)
    {
        result.fromJson(objResult);
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}
