#include "DobotDevice.h"
#include <QDateTime>
#include <QDir>
#include <QBuffer>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QCryptographicHash>
#include <memory>
#ifdef Q_OS_WIN
#include <iphlpapi.h>
#endif
#include "yaml-cpp/yaml.h"


CDobotDevice::CDobotDevice(QObject *parent) : QObject(parent)
{
    initFunctionMapper();
    m_pCameraDevice = new HKSmartCameraDevice(this);
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
        dir.mkdir("cache_smart");
        dir.cd("cache_smart");
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
    QList<CameraInfo> retInfo;
    bool ret = m_pCameraDevice->search(retInfo);

    CSearchCameraResponseResult result;
    if (ret)
    {
        for(auto itr=retInfo.begin(); itr!=retInfo.end(); ++itr)
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
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
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

    bool ret = m_pCameraDevice->openCamera(request.m_data.identify, request.m_data.password);

    m_mapAttributeType.clear();
    m_mapTranslateString.clear();
    if (ret)
    {//登录成功时，获取一次相机类型属性
        ret = m_pCameraDevice->getCameraXmlAttribute(m_mapAttributeType);
        qDebug()<<"getCameraXmlAttribute:ret="<<ret;
        ret = m_pCameraDevice->getModuleTranslate(m_mapTranslateString);
        qDebug()<<"getModuleTranslate:ret="<<ret;
    }

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
    if (true)
    {
        //清空结果解决方案数据
        QMutexLocker guard(&m_mtxProjectRunResult);
        m_objProjectRunResult.clear();
    }
    m_pCameraDevice->closeCamera();
    CCloseCameraResponseResult result;
    sendResponseSuccess(msg.getMsgUuid(), result);
    deleteAllCacheId();
}

void CDobotDevice::startVideo(const CMessageRequest &msg)
{
    //if (m_pCameraDevice->inherits("HKSmartCameraDevice"))
    CStartVideoRequestParams request;
    request.fromJson(msg.getParams());

    const bool isReturnFrame = request.m_data.returnFrame;
    const bool isReturnResult = request.m_data.returnResult;

    QString strMsgUuid = msg.getMsgUuid();
    static_cast<HKSmartCameraDevice*>(m_pCameraDevice)->setVideoImageDataCallback([this,strMsgUuid,isReturnFrame,isReturnResult](const ProjectResultInfo& info){
        CStartVideoResponseResult result;
        result.setPrintLog(false); //视频图片不要打印，否则日志太多

        result.m_data.width = info.sz.width();
        result.m_data.height = info.sz.height();
        if (isReturnFrame)
        {
            result.m_data.frame = image2Base64Byte(info.img);
            parseProjectRunResult(info.strResultData, info.renderImg, result.m_data.result);
        }
        else
        {
            QHash<int,QImage> renderImg;
            parseProjectRunResult(info.strResultData, renderImg, result.m_data.result);
        }
        if (true)
        {
            QMutexLocker guard(&m_mtxProjectRunResult);
            m_objProjectRunResult = result.m_data.result;
        }
        if (!isReturnResult)
        {
            result.m_data.result.clear();
        }
        sendResponseSuccess(strMsgUuid, result, false);
    });
    bool ret = m_pCameraDevice->startVideo();
    if (ret)
    {
        m_strVideoLastMsgUuid = strMsgUuid;
        CStartVideoResponseResult result;
        result.m_data.frame = "";
        sendResponseSuccess(strMsgUuid, result, false);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::startVideoV2(const CMessageRequest &msg)
{
    CStartVideoV2RequestParams request;
    request.fromJson(msg.getParams());

    QString strMsgUuid = msg.getMsgUuid();
    static_cast<HKSmartCameraDevice*>(m_pCameraDevice)->setVideoImageDataCallback([this](const ProjectResultInfo& info){
        QMutexLocker guard(&m_mtxProjectRunResult);
        //info.renderImg
        QHash<int,QImage> renderImg;
        parseProjectRunResult(info.strResultData, renderImg, m_objProjectRunResult);
    });
    bool ret = m_pCameraDevice->startVideo();
    if (ret)
    {
        CStartVideoV2ResponseResult result;
        sendResponseSuccess(strMsgUuid, result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::startTestVideo(const CMessageRequest &msg)
{
    CStartTestVideoRequestParams request;
    request.fromJson(msg.getParams());

    const bool isReturnFrame = request.m_data.returnFrame;
    const bool isReturnResult = request.m_data.returnResult;

    QString strMsgUuid = msg.getMsgUuid();
    static_cast<HKSmartCameraDevice*>(m_pCameraDevice)->setVideoImageDataCallback([this,strMsgUuid,isReturnFrame,isReturnResult](const ProjectResultInfo& info){
        CStartVideoResponseResult result;
        result.setPrintLog(false); //视频图片不要打印，否则日志太多

        result.m_data.width = info.sz.width();
        result.m_data.height = info.sz.height();
        if (isReturnFrame)
        {
            result.m_data.frame = image2Base64Byte(info.img);
            parseProjectRunResult(info.strResultData, info.renderImg, result.m_data.result);
        }
        else
        {
            QHash<int,QImage> renderImg;
            parseProjectRunResult(info.strResultData, renderImg, result.m_data.result);
        }
        if (true)
        {
            QMutexLocker guard(&m_mtxProjectRunResult);
            m_objProjectRunResult = result.m_data.result;
        }
        if (!isReturnResult)
        {
            result.m_data.result.clear();
        }
        sendResponseSuccess(strMsgUuid, result, false);
    });
    bool ret = m_pCameraDevice->startTestVideo();
    if (ret)
    {
        m_strVideoLastMsgUuid = strMsgUuid;
        CStartTestVideoResponseResult result;
        result.m_data.frame = "";
        sendResponseSuccess(strMsgUuid, result, false);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
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
    CTakePhotoRequestParams request;
    request.fromJson(msg.getParams());

    const bool isReturnFrame = request.m_data.returnFrame;
    const bool isReturnResult = request.m_data.returnResult;

    ProjectResultInfo info;
    m_pCameraDevice->takePhoto(info);

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("takePhotoResult.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(info.strResultData.toUtf8());
            file.close();
        }
    }

    if (info.img.isNull())
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
    else
    {
        CTakePhotoResponseResult result;
        if (isReturnFrame)
        {
            result.m_data.frame = image2Base64Byte(info.img);
        }
        else
        {
            info.renderImg.clear();
        }
        result.m_data.width = info.sz.width();
        result.m_data.height = info.sz.height();
        parseProjectRunResult(info.strResultData, info.renderImg, result.m_data.result);
        if (true)
        {
            QMutexLocker guard(&m_mtxProjectRunResult);
            m_objProjectRunResult = result.m_data.result;
        }
        if (!isReturnResult)
        {
            result.m_data.result.clear();
        }
        if (request.m_data.savePath.isEmpty())
        {
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
            const QString strSavePath = fixSavePath(request.m_data.savePath) + strFileName;
            if (info.img.save(strSavePath))
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

void CDobotDevice::takeBasePhoto(const CMessageRequest &msg)
{
    CTakeBasePhotoRequestParams request;
    request.fromJson(msg.getParams());

    const bool isReturnFrame = request.m_data.returnFrame;
    const bool isReturnResult = request.m_data.returnResult;

    ProjectResultInfo info;
    m_pCameraDevice->takeBasePhoto(info,request.m_data.moduleId);

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("takeBasePhotoResult.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(info.strResultData.toUtf8());
            file.close();
        }
    }

    if (info.img.isNull())
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
    else
    {
        CTakeBasePhotoResponseResult result;
        if (isReturnFrame)
        {
            result.m_data.frame = image2Base64Byte(info.img);
        }
        else
        {
            info.renderImg.clear();
        }
        result.m_data.width = info.sz.width();
        result.m_data.height = info.sz.height();
        parseProjectRunResult(info.strResultData, info.renderImg, result.m_data.result);
        if (true)
        {
            QMutexLocker guard(&m_mtxProjectRunResult);
            m_objProjectRunResult = result.m_data.result;
        }
        if (!isReturnResult)
        {
            result.m_data.result.clear();
        }

        if (request.m_data.savePath.isEmpty())
        {
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
            const QString strSavePath = fixSavePath(request.m_data.savePath) + strFileName;
            if (info.img.save(strSavePath))
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
    ProjectResultInfo pictureInfo;
    bool ret = m_pCameraDevice->createUserCoordinate(strCalibrateFile,robotPos, coordinatePos, iId, pictureInfo);

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
        result.m_data.frame = image2Base64Byte(pictureInfo.img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (pictureInfo.img.save(strSave))
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
    ProjectResultInfo pictureInfo;
    bool ret = m_pCameraDevice->createUserCoordinate(strCalibrateFile,robotPos, coordinatePos, iId, pictureInfo);

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
        result.m_data.frame = image2Base64Byte(pictureInfo.img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (pictureInfo.img.save(strSave))
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

    ProjectResultInfo pictureInfo;
    bool ret = m_pCameraDevice->calibrateSampling(robotPos, pictureInfo);

    CCalibrateSamplingResultResponseResult result;
    if (isReturnFrame)
    {
        result.m_data.frame = image2Base64Byte(pictureInfo.img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (pictureInfo.img.save(strSave))
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

    ProjectResultInfo pictureInfo;
    bool ret = m_pCameraDevice->updateCalibrateSampling(robotPos, iUpdateIdx, pictureInfo);

    CCalibrateSamplingResultResponseResult result;
    if (isReturnFrame)
    {
        result.m_data.frame = image2Base64Byte(pictureInfo.img);
    }

    if (!request.m_data.savePath.isEmpty())
    {
        const QString strSavePath = fixSavePath(request.m_data.savePath);
        QString strFileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz")+".jpg";
        QString strSave = strSavePath + strFileName;
        if (pictureInfo.img.save(strSave))
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

void CDobotDevice::getCurrentProgress(const CMessageRequest &msg)
{
    MV_VS_ENUMVALUE pushType, pushState;
    MV_VS_INTVALUE pushRate;

    bool ret = m_pCameraDevice->GetEnumValue("ScPushType", pushType);
    ret = ret && m_pCameraDevice->GetEnumValue("ScPushState", pushState);//pushState.nCurValue==0表示成功，1表示失败
    ret = ret && m_pCameraDevice->GetIntValue("ScPushRate", pushRate);

    CCurrentProgressResponseResult result;
    if (ret)
    {
        result.m_data.progress = pushRate.nCurValue;
        result.m_data.status = (0==pushState.nCurValue);

        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getAllProjectList(const CMessageRequest &msg)
{
    CAllProjectListRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetCommandValue("CommandProjectList");
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ProjectList");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ProjectList");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getAllProjectList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CAllProjectListResponseResult result;

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }


    MV_VS_STRINGVALUE stStringValue;
    if (m_pCameraDevice->GetStringValue("ScDeviceCurrentSolutionName", stStringValue))
    {
        result.m_data.name = stStringValue.strValue;
    }

    QJsonArray jsonArr = jsonDoc.object().value("data").toArray();
    if (jsonArr.isEmpty())
    {
        qDebug()<<"has no project,status="<<jsonDoc.object().value("status").toString();
    }
    for(auto itr=jsonArr.begin();itr!=jsonArr.end();++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject obj = itr->toObject();

        CAllProjectListResponseBean bean;
        bean.name = obj.value("Name").toString();
        bean.createDateTime = obj.value("CreateDateTime").toString();
        bean.baseImageName = obj.value("BaseImageName").toString();

        result.m_data.all.append(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
    return ;
}

void CDobotDevice::getProjectShowImage(const CMessageRequest &msg)
{
    CProjectShowImageRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.baseImageName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QByteArray arrImage;
    bool ret = m_pCameraDevice->SetEnumValueByString("FileSelector", "BaseThumbnail");
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.baseImageName);
    ret = ret && m_pCameraDevice->FileAccessRead(arrImage, "BaseThumbnail");

    CProjectShowImageResponseResult result;
    if (ret)
    {
        QImage img = QImage::fromData(arrImage);
        if (!img.isNull())
        {
            result.m_data.frame = image2Base64Byte(img);
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        }
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getCurrentSelectedProject(const CMessageRequest &msg)
{
    MV_VS_STRINGVALUE stStringValue;
    bool ret = m_pCameraDevice->SetEnumValueByString("FileSelector", "Solution");
    ret = ret && m_pCameraDevice->GetStringValue("ScDeviceCurrentSolutionName", stStringValue);

    CCurrentSelectedProjectResponseResult result;
    if (ret)
    {
        result.m_data.name = stStringValue.strValue;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::importProject(const CMessageRequest &msg)
{
    CImportProjectRequestParams request;
    request.fromJson(msg.getParams());

    QFile file(request.m_data.file);
    if (!file.open(QFile::ReadOnly))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_OPEN_FILE, file.errorString());
        return ;
    }

    bool ret = m_pCameraDevice->SetEnumValueByString("FileSelector", "Solution");
    ret = ret && m_pCameraDevice->FileAccessWrite(file, "Solution");

    CImportProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::exportProject(const CMessageRequest &msg)
{
    CExportProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.solutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QFile file(request.m_data.saveFile);
    if (!file.open(QFile::WriteOnly|QFile::Truncate))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_CREATE_FILE, file.errorString());
        return ;
    }

    bool ret = m_pCameraDevice->SetEnumValueByString("FileSelector", "Solution");
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.solutionName);
    ret = ret && m_pCameraDevice->FileAccessRead(file, "Solution");

    CExportProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::createProject(const CMessageRequest &msg)
{
    bool ret = m_pCameraDevice->SetCommandValue("CommandProjectCreate");

    CCreateProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::deleteProject(const CMessageRequest &msg)
{
    CDeleteProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.solutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateSolutionName", request.m_data.solutionName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandProjectDel");

    CDeleteProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::copyProject(const CMessageRequest &msg)
{
    CCopyProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.solutionName.isEmpty() || request.m_data.newSolutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateSolutionName", request.m_data.solutionName);
    ret = ret && m_pCameraDevice->SetStringValue("DstOperateSolutionName", request.m_data.newSolutionName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandProjectCopy");

    CCopyProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::renameProject(const CMessageRequest &msg)
{
    CRenameProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.solutionName.isEmpty() || request.m_data.newSolutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateSolutionName", request.m_data.solutionName);
    ret = ret && m_pCameraDevice->SetStringValue("DstOperateSolutionName", request.m_data.newSolutionName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandEditSolutionName");

    CRenameProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::saveProject(const CMessageRequest &msg)
{
    CSaveProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.solutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateSolutionName", request.m_data.solutionName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandProjectSave");

    CSaveProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::saveAsProject(const CMessageRequest &msg)
{
    CSaveAsProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.newSolutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateSolutionName", request.m_data.newSolutionName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandProjectSaveAs");

    CSaveAsProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::switchProject(const CMessageRequest &msg)
{
    CSwitchProjectRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.solutionName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateSolutionName", request.m_data.solutionName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandProjectLoad");

    CSwitchProjectResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getAllSupportModuleList(const CMessageRequest &msg)
{
    CAllSupportModuleRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetCommandValue("CommandDeviceAbiList");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "DeviceAbiList");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getAllSupportModuleList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CAllSupportModuleResponseResult result;

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonArray jsonArr = jsonDoc.object().value("data").toArray();
    if (jsonArr.isEmpty())
    {
        qDebug()<<"has no data,status="<<jsonDoc.object().value("status").toString();
    }
    for(auto itr=jsonArr.begin();itr!=jsonArr.end();++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject obj = itr->toObject();

        CAllSupportModuleResponseBean bean;
        bean.moduleName = obj.value("ModuleName").toString();
        if (bean.moduleName.isEmpty()) continue;

        if (m_mapTranslateString.contains(bean.moduleName))
        {
            auto& vts = m_mapTranslateString.value(bean.moduleName);
            bean.displayNameCN = vts.strDisplayNameCN;
            bean.displayNameEN = vts.strDisplayNameEN;
        }
        bean.algoModuleMax = obj.value("AlgoModuleMax").toInt();
        result.m_data.append(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
    return ;
}

void CDobotDevice::getProjectModuleList(const CMessageRequest &msg)
{
    CProjectModuleRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetCommandValue("CommandAlgoModuleList");
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModuleList");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ModuleList");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QFile file("getProjectModuleList.json");
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CProjectModuleResponseResult result;

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonArray jsonArr = jsonDoc.object().value("data").toArray();
    if (jsonArr.isEmpty())
    {
        qDebug()<<"has no data,status="<<jsonDoc.object().value("status").toString();
    }
    for(auto itr=jsonArr.begin();itr!=jsonArr.end();++itr)
    {
        if (!itr->isObject()) continue;
        QJsonObject obj = itr->toObject();

        CProjectModuleResponseBean bean;
        QString strModuleName = obj.value("ModuleName").toString();
        if (strModuleName.isEmpty()) continue;

        bean.moduleName = strModuleName;
        bean.moduleId = obj.value("ModuleID").toInt();
        if ("logic" == bean.moduleName || "format" == bean.moduleName)
        {//这2个参数，特殊处理
            if (m_mapTranslateString.contains(bean.moduleName))
            {
                auto& vts = m_mapTranslateString.value(bean.moduleName);
                bean.showName = vts.strDisplayNameCN; //vts.strDisplayNameEN
            }
        }
        else
        {
            //规则就是moduleName首字母大写，然后拼接ModuleCustomName
            QString strKey = bean.moduleName.at(0).toUpper()+bean.moduleName.mid(1);
            strKey += "ModuleCustomName";

            MV_VS_STRINGVALUE stStringValue;
            bool ret = m_pCameraDevice->SetIntValue("ModuleID", bean.moduleId);
            ret = ret && m_pCameraDevice->GetStringValue(strKey, stStringValue);
            if (ret)
            {
                bean.showName = stStringValue.strValue;
                if (bean.showName.isEmpty())
                {
                    if (m_mapTranslateString.contains(bean.moduleName))
                    {
                        auto& vts = m_mapTranslateString.value(bean.moduleName);
                        bean.showName = vts.strDisplayNameCN;
                    }
                }
            }
            else
            {
                if (m_mapTranslateString.contains(bean.moduleName))
                {
                    auto& vts = m_mapTranslateString.value(bean.moduleName);
                    bean.showName = vts.strDisplayNameCN;
                }
            }
        }
        result.m_data.append(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
    return ;
}

void CDobotDevice::addModule(const CMessageRequest &msg)
{
    CAddModuleRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.moduleName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetStringValue("SrcOperateModuleName", request.m_data.moduleName);
    ret = ret && m_pCameraDevice->SetIntValue("PreModuleID",request.m_data.preModuleId);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandAlgoModuleAdd");

    CAddModuleResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::deleteModule(const CMessageRequest &msg)
{
    CDeleteModuleRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandAlgoModuleDel");

    CDeleteModuleResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::copyModule(const CMessageRequest &msg)
{
    CCopyModuleRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandAlgoModuleDup");

    CCopyModuleResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::setModuleShowName(const CMessageRequest &msg)
{
    CSetModuleShowNameRequestParams request;
    request.fromJson(msg.getParams());

    if (request.m_data.moduleName.isEmpty())
    {
        qDebug()<<"setModuleShowName fail,because module name may be is empty";
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    //规则就是moduleName首字母大写，然后拼接ModuleCustomName
    QString strKey = request.m_data.moduleName;
    strKey = strKey.replace(0,1,strKey.at(0).toUpper());
    strKey += "ModuleCustomName";

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue(strKey,request.m_data.showName);

    CSetModuleShowNameResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getModuleShowName(const CMessageRequest &msg)
{
    CGetModuleShowNameRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.moduleName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    //规则就是moduleName首字母大写，然后拼接ModuleCustomName
    QString strKey = request.m_data.moduleName;
    strKey = strKey.replace(0,1,strKey.at(0).toUpper());
    strKey += "ModuleCustomName";

    MV_VS_STRINGVALUE stStringValue;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetStringValue(strKey, stStringValue);

    CGetModuleShowNameResponseResult result;
    if (ret)
    {
        result.m_data.showName = stStringValue.strValue;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

static void ParseModuleUIAllParameters(const QJsonObject& jsonRoot, QList<CGetModuleUIAllParameterResponseBean>& beanUI)
{
    for(auto itr = jsonRoot.constBegin(); itr!=jsonRoot.constEnd(); ++itr)
    {
        if (itr.value().isObject())
        {
            ParseModuleUIAllParameters(itr.value().toObject(), beanUI);
            continue;
        }
        else if (itr.value().isArray())
        {
            const QJsonArray arr = itr.value().toArray();
            for (int i=0; i<arr.size();++i)
            {
                if (arr.at(i).isObject())
                {
                    ParseModuleUIAllParameters(arr.at(i).toObject(), beanUI);
                }
            }
            continue;
        }

        if (jsonRoot.contains("ui_type") && jsonRoot["ui_type"].toString()=="config_param")
        {
            if (itr.key() == "ui_param_name" && itr.value().toString().length()>0)
            {
                CGetModuleUIAllParameterResponseBean bean;
                bean.paramName = itr.value().toString();
                bean.displayNameCN = jsonRoot["ui_display_cn_name"].toString();
                bean.displayNameEN = jsonRoot["ui_display_en_name"].toString();
                beanUI.append(bean);
            }
        }
    }
    return ;
}
void CDobotDevice::getModuleUIAllParameters(const CMessageRequest &msg)
{
    CGetModuleUIAllParameterRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.moduleName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    CGetModuleUIAllParameterResponseResult result;

    if ("logic" == request.m_data.moduleName || "format" == request.m_data.moduleName)
    {//这2个参数不给获取，海康也是这么做的，测试后发现，如果操作这2个数，容易出问题。
        sendResponseSuccess(msg.getMsgUuid(), result);
        return ;
    }

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.moduleName);
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "Json");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("%1[%2].json").arg(request.m_data.moduleName).arg(request.m_data.moduleId);
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    ParseModuleUIAllParameters(jsonDoc.object(), result.m_data);

    //只获取部分参数
    if (request.m_data.parameters.size()>0)
    {
        for (auto itr=result.m_data.begin(); itr!=result.m_data.end();)
        {
            if (request.m_data.parameters.contains(itr->paramName))
            {
                ++itr;
            }
            else
            {
                itr = result.m_data.erase(itr);
            }
        }
    }
    for (auto itr=result.m_data.begin(); itr!=result.m_data.end(); ++itr)
    {
        auto itrAttr = m_mapAttributeType.find(itr->paramName);
        if (itrAttr == m_mapAttributeType.end())
        {
            UIParamUnknow paType;
            itr->visible = false;
            itr->paramType = paType.getType();
            itr->parameters = UIParamBase::createBase(itr->paramType);
        }
        else
        {
            if (!m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId))
            {
                qDebug()<<"SetIntValue(ModuleID)fail,Unable to get parameter("<<itr->paramName<<") info:"<<m_pCameraDevice->getErrMessage();

                UIParamUnknow paType;
                itr->visible = false;
                itr->paramType = paType.getType();
                itr->parameters = UIParamBase::createBase(itr->paramType);

                continue;
            }

            itr->visible = m_pCameraDevice->getNodeIsVisible(itrAttr.value());
            if (!(itr->visible))
            {//节点不可访问，就不用返回类型了
                qDebug()<<"the node("<<itr->paramName<<") can not accessing";

                UIParamUnknow paType;
                itr->visible = false;
                itr->paramType = paType.getType();
                itr->parameters = UIParamBase::createBase(itr->paramType);

                continue;
            }
            itr->paramType = itrAttr->strDataType;
            itr->parameters = UIParamBase::createBase(itr->paramType);
            if (UIParamInteger::isMine(itr->paramType))
            {
                auto pUI = static_cast<UIParamInteger*>(itr->parameters.get());
                MV_VS_INTVALUE stIntValue;
                pUI->success = m_pCameraDevice->GetIntValue(itr->paramName, stIntValue);
                pUI->errmsg = m_pCameraDevice->getErrMessage();
                if (pUI->success)
                {
                    pUI->value = stIntValue.nCurValue;
                    pUI->min = stIntValue.nMin;
                    pUI->max = stIntValue.nMax;
                    pUI->inc = stIntValue.nInc;
                }
            }
            else if (UIParamFloat::isMine(itr->paramType))
            {
                auto pUI = static_cast<UIParamFloat*>(itr->parameters.get());
                MV_VS_FLOATVALUE stFloatValue;
                pUI->success = m_pCameraDevice->GetFloatValue(itr->paramName, stFloatValue);
                pUI->errmsg = m_pCameraDevice->getErrMessage();
                if (pUI->success)
                {
                    pUI->value = stFloatValue.fCurValue;
                    pUI->min = stFloatValue.fMin;
                    pUI->max = stFloatValue.fMax;
                }
            }
            else if (UIParamBoolean::isMine(itr->paramType))
            {
                auto pUI = static_cast<UIParamBoolean*>(itr->parameters.get());
                bool bAttrType;
                pUI->success = m_pCameraDevice->GetBoolValue(itr->paramName, bAttrType);
                pUI->errmsg = m_pCameraDevice->getErrMessage();
                if (pUI->success)
                {
                    pUI->value = bAttrType;
                }
            }
            else if (UIParamString::isMine(itr->paramType))
            {
                auto pUI = static_cast<UIParamString*>(itr->parameters.get());
                MV_VS_STRINGVALUE stringValue;
                pUI->success = m_pCameraDevice->GetStringValue(itr->paramName, stringValue);
                pUI->errmsg = m_pCameraDevice->getErrMessage();
                if (pUI->success)
                {
                    pUI->value = stringValue.strValue;
                }
            }
            else if (UIParamEnumeration::isMine(itr->paramType))
            {
                auto pUI = static_cast<UIParamEnumeration*>(itr->parameters.get());
                MV_VS_ENUMVALUE stEnumValue;
                pUI->success = m_pCameraDevice->GetEnumValue(itr->paramName, stEnumValue);
                pUI->errmsg = m_pCameraDevice->getErrMessage();
                if (pUI->success)
                {
                    pUI->value = stEnumValue.nCurValue;
                    for (unsigned int i = 0; i < stEnumValue.nSupportNum; ++i)
                    {
                        pUI->supportValues.append(stEnumValue.nSupportValue[i]);
                    }
                }
            }
            else if (UIParamCommand::isMine(itr->paramType))
            {
                auto pUI = static_cast<UIParamCommand*>(itr->parameters.get());
                pUI->success = true;
                pUI->errmsg = "";
            }
            else
            {
                qDebug()<<"unknow param type:"<<itr->paramType;
            }
        }
    }
    sendResponseSuccess(msg.getMsgUuid(), result);

    return ;
}

void CDobotDevice::setModuleUIParameters(const CMessageRequest &msg)
{
    CSetModuleUIParameterRequestParams request;
    request.fromJson(msg.getParams());

    CSetModuleUIParameterResponseResult result;

    bool isSetIntId = false;
    for(auto itr=request.m_data.parameter.begin(); itr!=request.m_data.parameter.end(); ++itr)
    {
        CSetModuleUIParameterResponseBean bean;
        bean.paramName = itr.value().paramName;

        isSetIntId = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
        if (isSetIntId)
        {
            if (UIParamInteger::isMine(itr.value().paramType))
            {
                isSetIntId = m_pCameraDevice->SetIntValue(bean.paramName, itr.value().paramValue.toInt());
                bean.success = isSetIntId;
                bean.errmsg = m_pCameraDevice->getErrMessage();
            }
            else if (UIParamFloat::isMine(itr.value().paramType))
            {
                isSetIntId = m_pCameraDevice->SetFloatValue(bean.paramName, itr.value().paramValue.toDouble());
                bean.success = isSetIntId;
                bean.errmsg = m_pCameraDevice->getErrMessage();
            }
            else if (UIParamBoolean::isMine(itr.value().paramType))
            {
                isSetIntId = m_pCameraDevice->SetBoolValue(bean.paramName, itr.value().paramValue.toBool());
                bean.success = isSetIntId;
                bean.errmsg = m_pCameraDevice->getErrMessage();
            }
            else if (UIParamString::isMine(itr.value().paramType))
            {
                isSetIntId = m_pCameraDevice->SetStringValue(bean.paramName, itr.value().paramValue.toString());
                bean.success = isSetIntId;
                bean.errmsg = m_pCameraDevice->getErrMessage();
            }
            else if (UIParamEnumeration::isMine(itr.value().paramType))
            {
                isSetIntId = m_pCameraDevice->SetEnumValue(bean.paramName, itr.value().paramValue.toInt());
                bean.success = isSetIntId;
                bean.errmsg = m_pCameraDevice->getErrMessage();
            }
            else if (UIParamCommand::isMine(itr.value().paramType))
            {
                isSetIntId = m_pCameraDevice->SetCommandValue(bean.paramName);
                bean.success = isSetIntId;
                bean.errmsg = m_pCameraDevice->getErrMessage();
            }
            else
            {
                bean.success = false;
                bean.errmsg = "unknow parameter type";
            }
        }
        else
        {
            bean.success = false;
            bean.errmsg = m_pCameraDevice->getErrMessage();
            qDebug()<<"SetIntValue(ModuleID="<<request.m_data.moduleId<<")fail,Unable to set parameter("<<bean.paramName<<") error:"<<m_pCameraDevice->getErrMessage();
        }

        result.m_data.append(bean);
    }

    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::setCameraPassword(const CMessageRequest &msg)
{
    CSetCameraPwdRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetStringValue("ScDeviceOldPassword", request.m_data.oldPassword);
    ret = ret && m_pCameraDevice->SetStringValue("ScDeviceNewPassword", request.m_data.newPassword);
    ret = ret && m_pCameraDevice->SetStringValue("ScDeviceConfirmPassword", request.m_data.newPassword);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandConfirmPassword");

    CSetCameraPwdResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::cameraSoftReboot(const CMessageRequest &msg)
{
    CCameraSoftRebootResponseResult result;
    if (m_pCameraDevice->SetCommandValue("DeviceReboot"))
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::setCommunicateEnable(const CMessageRequest &msg)
{
    CSetCommunicateEnableRequestParams request;
    request.fromJson(msg.getParams());

    QString strKey = request.m_data.moduleName+"_enable";//key是由moduleName拼接_enable
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetBoolValue(strKey, request.m_data.enable);

    CSetCommunicateEnableResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getCommunicateEnable(const CMessageRequest &msg)
{
    CGetCommunicateEnableRequestParams request;
    request.fromJson(msg.getParams());

    bool bIsEnable = false;
    QString strKey = request.m_data.moduleName+"_enable";//key是由moduleName拼接_enable
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetBoolValue(strKey, bIsEnable);

    CGetCommunicateEnableResponseResult result;
    if (ret)
    {
        result.m_data.enable = bIsEnable;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::get25DCalibrateFileList(const CMessageRequest &msg)
{
    CGet25DCalibrateFileListRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModelMng");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ModelMng");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }
    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("get25DCalibrateFileList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CGet25DCalibrateFileListResponseResult result;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonObject jsObject = jsonDoc.object();
    QJsonArray arrFile = jsObject["model_list"].toArray();
    result.m_data.currentFile = jsObject["current_model_name"].toString();
    result.m_data.fileType = jsObject["upload_file_type"].toString();
    result.m_data.maxCount = jsObject["max_model_num"].toInt();
    for (int i=0; i<arrFile.size(); ++i)
    {
        QString str = arrFile.at(i).toObject()["model_name"].toString();
        if (str.size()>0)
        {
            result.m_data.fileList.append(str);
        }
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::get2DCalibrateFileList(const CMessageRequest &msg)
{
    CGet2DCalibrateFileListRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModelMng");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ModelMng");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("get2DCalibrateFileList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CGet2DCalibrateFileListResponseResult result;

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonObject jsObject = jsonDoc.object();
    QJsonArray arrFile = jsObject["model_list"].toArray();
    result.m_data.currentFile = jsObject["current_model_name"].toString();
    result.m_data.fileType = jsObject["upload_file_type"].toString();
    result.m_data.maxCount = jsObject["max_model_num"].toInt();
    for (int i=0; i<arrFile.size(); ++i)
    {
        QString str = arrFile.at(i).toObject()["model_name"].toString();
        if (str.size()>0)
        {
            result.m_data.fileList.append(str);
        }
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::delete25DCalibrateFile(const CMessageRequest &msg)
{
    CDelete25DCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("MacAprilTagDeleteModelName", request.m_data.fileName);

    CDelete25DCalibrateFileResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::delete2DCalibrateFile(const CMessageRequest &msg)
{
    CDelete2DCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("MatchLocateDeleteModelName", request.m_data.fileName);

    CDelete2DCalibrateFileResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::switch25DCalibrateFile(const CMessageRequest &msg)
{
    CSwitch25DCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.fileName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("MacAprilTagSwitchModelName", request.m_data.fileName);

    CSwitch25DCalibrateFileResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::switch2DCalibrateFile(const CMessageRequest &msg)
{
    CSwitch2DCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.fileName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("MatchLocateSwitchModelName", request.m_data.fileName);

    CSwitch2DCalibrateFileResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

static void checkCalibrateTextValidYaml(YAML::Node& node)
{
    if (!node.IsMap())
    {
        YAML::Mark mark;
        throw YAML::Exception(mark, "node is not Map");
    }
    YAML::Node rows = node["rows"];
    if (!rows.IsScalar()) {
        YAML::Mark mark;
        throw YAML::Exception(mark, "rows is not Scalar");
    }
    YAML::Node cols = node["cols"];
    if (!cols.IsScalar()) {
        YAML::Mark mark;
        throw YAML::Exception(mark, "cols is not Scalar");
    }
    YAML::Node dt = node["dt"];
    if (!dt.IsScalar()) {
        YAML::Mark mark;
        throw YAML::Exception(mark, "dt is not Scalar");
    }
    YAML::Node data = node["data"];
    if (!data.IsSequence()) {
        YAML::Mark mark;
        throw YAML::Exception(mark, "rows data not Sequence");
    }
}
static bool isValidCalibrateYaml(const std::string& str)
{
    try
    {
        YAML::Node doc = YAML::Load(str);
        YAML::Node cameToTipCv = doc["cameToTipCv"];
        checkCalibrateTextValidYaml(cameToTipCv);

        YAML::Node cameraMatrix = doc["cameraMatrix"];
        checkCalibrateTextValidYaml(cameraMatrix);

        YAML::Node distCoeffs = doc["distCoeffs"];
        checkCalibrateTextValidYaml(distCoeffs);
    }
    catch (const YAML::Exception& e)
    {
        qDebug()<< e.what() << "\n";
        return false;
    }
    return true;
}
void CDobotDevice::add25DCalibrateFile(const CMessageRequest &msg)
{
    CAdd25DCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.fileName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QFile file(request.m_data.fileFullPath);
    if (!file.open(QFile::ReadOnly))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_OPEN_FILE, file.errorString());
        return ;
    }
    QByteArray yamlData = file.readAll();
    file.seek(0);
    if (!isValidCalibrateYaml(yamlData.toStdString()))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.fileName);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "DlModel");
    ret = ret && m_pCameraDevice->FileAccessWrite(file, "DlModel");

    CAdd25DCalibrateFileResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::add25DCalibrateFileV2(const CMessageRequest &msg)
{
    CAdd25DCalibrateFileV2RequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.fileName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    if (request.m_data.fileContent.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    if (!isValidCalibrateYaml(request.m_data.fileContent.toStdString()))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QByteArray fileArr = request.m_data.fileContent.toUtf8();
    QBuffer buffer(&fileArr);
    buffer.open(QBuffer::ReadOnly);

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.fileName);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "DlModel");
    ret = ret && m_pCameraDevice->FileAccessWrite(buffer, "DlModel");

    CAdd25DCalibrateFileV2ResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::add2DCalibrateFile(const CMessageRequest &msg)
{
    CAdd2DCalibrateFileRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.fileName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QFile file(request.m_data.fileFullPath);
    if (!file.open(QFile::ReadOnly))
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_OPEN_FILE, file.errorString());
        return ;
    }

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.fileName);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "DlModel");
    ret = ret && m_pCameraDevice->FileAccessWrite(file, "DlModel");

    CAdd2DCalibrateFileResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::export2DCalibrateParam(const CMessageRequest &msg)
{
    CExport2DCalibrateParamRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ScAlgoCalibData");

    CExport2DCalibrateParamResponseResult result;
    if (ret)
    {
        QFile file(request.m_data.saveFileFullName);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            qDebug()<<"write file error:"<<file.errorString();
            sendResponseError(msg.getMsgUuid(), DT_ERR_WRITE_FILE);
        }
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

static QString encryptCalibrateParamData(QByteArray srcData)
{
    const QString strSrcData = srcData.toHex();
    QString strSign("dobot");
    strSign += strSrcData;
    QString strMd5 = QCryptographicHash::hash(strSign.toUtf8(), QCryptographicHash::Md5).toHex();
    QString strResult = strMd5+":"+strSrcData;
    return strResult;
}

static QByteArray decryptCalibrateParamData(const QString& strSrc)
{
    QByteArray fileData;
    if (strSrc.isEmpty()) return fileData;
    QStringList arrStr = strSrc.split(':',QString::SkipEmptyParts);
    if (arrStr.size() != 2) return fileData;

    QString strSign("dobot");
    strSign += arrStr[1];
    QString strMd5 = QCryptographicHash::hash(strSign.toUtf8(), QCryptographicHash::Md5).toHex();
    if (strMd5 != arrStr[0]) return fileData;

    fileData = QByteArray::fromHex(arrStr[1].toUtf8());
    return fileData;
}

void CDobotDevice::add2DCalibrateFileV2(const CMessageRequest &msg)
{
    CAdd2DCalibrateFileV2RequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData = decryptCalibrateParamData(request.m_data.content);
    if (request.m_data.fileName.isEmpty() ||
            request.m_data.content.isEmpty() ||
            fileData.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.fileName);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "DlModel");
    ret = ret && m_pCameraDevice->FileAccessWrite(fileData, "DlModel");

    CAdd2DCalibrateFileV2ResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::export2DCalibrateParamV2(const CMessageRequest &msg)
{
    CExport2DCalibrateParamV2RequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ScAlgoCalibData");

    CExport2DCalibrateParamV2ResponseResult result;
    if (ret)
    {
        result.m_data.content = encryptCalibrateParamData(fileData);
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getBaseImageHistroyImageInfoList(const CMessageRequest &msg)
{
    CBaseImageHistoryImageInfoListRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);

    //搜索开始和结束时间
    QDateTime startTime = QDateTime::currentDateTime();
    QDateTime endTime = startTime.addYears(-10);
    QString strStartDate = startTime.toString("yyyy-MM-dd HH:mm:ss");
    QString strEndDate = endTime.toString("yyyy-MM-dd HH:mm:ss");
    ret = ret && m_pCameraDevice->SetStringValue("SaveImageStartDate", strStartDate);
    ret = ret && m_pCameraDevice->SetStringValue("SaveImageEndDate", strEndDate);

    QString strImageType="ALL";//设置历史图像格式:JPG BMP ALL
    m_pCameraDevice->SetEnumValueByString("SaveImageType", strImageType);

    QString strImageResultType="ALL";//设置历史图像结果类型:OK NG ALL
    m_pCameraDevice->SetEnumValueByString("SaveImageResultType", strImageResultType);

    QString strImageKeyword="";//历史图像搜索关键字,可以不填
    ret = ret && m_pCameraDevice->SetStringValue("SaveImageKeyword", strImageKeyword);

    QString strImagePageNum="Page20";//设置历史图像每页条数: Page20 Page50 Page100 All
    ret = ret && m_pCameraDevice->SetEnumValueByString("SaveImagePageNumber", strImagePageNum);

    int iPageCount = 1;//设置历史图像页数
    ret = ret && m_pCameraDevice->SetIntValue("SaveImagePage", iPageCount);

    //设置命令
    ret = ret && m_pCameraDevice->SetCommandValue("SaveImageInquire");

    //读取历史图像文件列表
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ImageList");
    QByteArray arrImageList;
    ret = ret && m_pCameraDevice->FileAccessRead(arrImageList, "ImageList");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getBaseImageHistroyImageInfoList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(arrImageList);
            file.close();
        }
    }

    CBaseImageHistoryImageInfoListResponseResult result;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(arrImageList, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonObject jsObject = jsonDoc.object();
    QJsonArray arrFile = jsObject["stImageParamList"].toArray();
    for (int i=0; i<arrFile.size(); ++i)
    {
        QJsonObject imgJson = arrFile.at(i).toObject();
        QString str = imgJson["strImageName"].toString();
        if (!str.isEmpty())
        {
            CBaseImageHistoryImageInfoListResponseBean bean;
            bean.imageName = str;
            bean.imageDate = imgJson["strImageDate"].toString();
            bean.imageState = imgJson["strImageRunstatus"].toString()=="0";
            result.m_data.append(bean);
        }
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::getBaseImageHistroyImageData(const CMessageRequest &msg)
{
    CBaseImageHistroyImageDataRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.imageName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QByteArray arrImage;

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "SaveImage");
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.imageName);
    ret = ret && m_pCameraDevice->FileAccessRead(arrImage, "SaveImage");

    CBaseImageHistroyImageDataResponseResult result;
    if (ret)
    {
        QImage img = QImage::fromData(arrImage);
        if (!img.isNull())
        {
            result.m_data.frame = image2Base64Byte(img);
            sendResponseSuccess(msg.getMsgUuid(), result);
        }
        else
        {
            sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        }
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::setBaseImageFromCurrent(const CMessageRequest &msg)
{
    CSetBaseImageFromCurrentRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandDeviceBaseImageCurrent");

    CSetBaseImageFromCurrentResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::setBaseImageFromHistory(const CMessageRequest &msg)
{
    CSetBaseImageFromHistoryRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.imageName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.imageName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandSaveImgImportBaseImage");

    CSetBaseImageFromHistoryResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getCurrentProjectRunningState(const CMessageRequest &msg)
{
    MV_VS_INTVALUE stIntValue;
    bool ret = m_pCameraDevice->GetIntValue("ScDeviceSolutionRunningState", stIntValue);

    CGetCurrentProjectRunningStateResponseResult result;
    if (ret)
    {
        result.m_data.state = stIntValue.nCurValue!=0 ? true:false;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getOutputConfigProjectResultCategory(const CMessageRequest &msg)
{
    CGetOutputConfigProjectResultCategoryRequestParams request;
    request.fromJson(msg.getParams());

    MV_VS_ENUMVALUE stEnumValue;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetEnumValue("LogicType", stEnumValue);

    CGetOutputConfigProjectResultCategoryResponseResult result;
    if (ret)
    {
        result.m_data.value = stEnumValue.nCurValue;
        for (unsigned int i = 0; i < stEnumValue.nSupportNum; ++i)
        {
            result.m_data.supportValues.append(stEnumValue.nSupportValue[i]);
        }
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getOutputConfigProjectResultCustomLogicData(const CMessageRequest &msg)
{
    CGetOutputConfigProjectResultCustomLogicDataRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "AlgoPrivate");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "AlgoPrivate");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getOutputConfigProjectResultCustomLogicData.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }

    CGetOutputConfigProjectResultCustomLogicDataResponseResult result;

    QJsonObject jsObject = jsonDoc.object();
    QJsonArray arrFile = jsObject["LogicParamList"].toArray();
    result.m_data.moduleName = jsObject["ModuleName"].toString(request.m_data.moduleName);
    result.m_data.moduleId = jsObject["ModuleID"].toInt(request.m_data.moduleId);
    result.m_data.logicalMode = jsObject["LogicalMode"].toString();
    for (int i=0; i<arrFile.size(); ++i)
    {
        QJsonObject logicData = arrFile.at(i).toObject();
        CGetOutputConfigProjectResultCustomLogicDataResponseBean bean;
        bean.paramValue = logicData["ParamValue"].toString();
        bean.showValueCN = logicData["ShowValue_CN"].toString();
        bean.showValueEN = logicData["ShowValue_EN"].toString();
        result.m_data.logicParams.append(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::setOutputConfigProjectResultCustomLogicData(const CMessageRequest &msg)
{
    CSetOutputConfigProjectResultCustomLogicDataRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.logicalMode.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QJsonObject jsObject;
    jsObject.insert("ModuleName","logic");
    jsObject.insert("ModuleID",request.m_data.moduleId);
    jsObject.insert("LogicalMode",request.m_data.logicalMode);
    jsObject.insert("ModuleDispName","Logic Module");
    QJsonArray dataArray;
    for(auto itr=request.m_data.logicParams.begin(); itr != request.m_data.logicParams.end(); ++itr)
    {
        QJsonObject param;
        param.insert("ParamValue", itr->paramValue);
        param.insert("ShowValue_CN", itr->showValueCN);
        param.insert("ShowValue_EN", itr->showValueEN);
        dataArray.append(param);
    }
    jsObject.insert("LogicParamList",dataArray);
    QJsonDocument doc(jsObject);
    QByteArray fileData = doc.toJson();

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "AlgoPrivate");
    ret = ret && m_pCameraDevice->FileAccessWrite(fileData, "AlgoPrivate");

    CSetOutputConfigProjectResultCustomLogicDataResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getOutputConfigProjectResultCustomLogicSupportList(const CMessageRequest &msg)
{
    CGetOutputConfigProjectResultCustomLogicSupportListRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FilterSubType", "int");
    ret = ret && m_pCameraDevice->SetEnumValue("SubModuleStyle", 1);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandSubscribeSource");
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "SubscribeSource");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "SubscribeSource");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getOutputConfigProjectResultCustomLogicSupportList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonArray dataArray = jsonDoc.object()["data"].toArray();

    CGetOutputConfigProjectResultCustomLogicSupportListResponseResult result;
    for (int i=0; i<dataArray.size(); ++i)
    {
        QJsonObject logicData = dataArray.at(i).toObject();
        int moduleId = logicData["ModuleID"].toInt();
        QString moduleName = logicData["ModuleName"].toString();
        QJsonArray subObjectArray = logicData["SubObject"].toArray();
        if (moduleName.isEmpty() || subObjectArray.isEmpty())
        {
            continue;
        }
        QJsonObject subObject = subObjectArray[0].toObject();
        QString pubName = subObject["PubName"].toString();
        if (pubName.isEmpty())
        {
            continue;
        }

        QString strModuleNameCN,strModuleNameEn;
        if (m_mapTranslateString.contains(moduleName))
        {
            strModuleNameCN = m_mapTranslateString[moduleName].strDisplayNameCN;
            strModuleNameEn = m_mapTranslateString[moduleName].strDisplayNameEN;
        }
        else
        {
            strModuleNameCN = pubName;
            strModuleNameEn = pubName;
        }

        CGetOutputConfigProjectResultCustomLogicSupportListResponseBean bean;
        bean.paramValue = QString("%1 %2.%3").arg(moduleId).arg(moduleName).arg(pubName);
        if (m_mapTranslateString.contains(pubName))
        {
            bean.showValueCN = QString("%1 %2.%3").arg(moduleId).arg(strModuleNameCN).arg(m_mapTranslateString[pubName].strDisplayNameCN);
            bean.showValueEN = QString("%1 %2.%3").arg(moduleId).arg(strModuleNameEn).arg(m_mapTranslateString[pubName].strDisplayNameEN);
        }

        result.m_data.append(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::get2DInputPointSupportList(const CMessageRequest &msg)
{
    CGet2DInputPointSupportListRequestParams request;
    request.fromJson(msg.getParams());

    /*因为这3个POINT_x,POINT_y,SINGLE_angle对象的对应字段完全一样的，得到的结果也是一样的，所以不用获取3次
     * 这个获取方式，跟getOutputConfigProjectResultCustomLogicSupportList接口一模一样，就是参数值区别而已
    */
    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FilterSubType", "float"); //对应UIJson中的ui_param_sub_type字段
    ret = ret && m_pCameraDevice->SetEnumValue("SubModuleStyle", 1); //对应UIJson中的ui_param_sub_style字段
    ret = ret && m_pCameraDevice->SetCommandValue("CommandSubscribeSource");
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "SubscribeSource");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "SubscribeSource");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("get2DInputPointSupportList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonArray dataArray = jsonDoc.object()["data"].toArray();

    CGet2DInputPointSupportListResponseResult result;
    for (int i=0; i<dataArray.size(); ++i)
    {
        QJsonObject dataObject = dataArray.at(i).toObject();
        int moduleId = dataObject["ModuleID"].toInt();
        QString moduleName = dataObject["ModuleName"].toString();
        QJsonArray subObjectArray = dataObject["SubObject"].toArray();
        if (moduleName.isEmpty() || subObjectArray.isEmpty())
        {
            continue;
        }

        CGet2DInputPointSupportListResponseBean2 dataBean2D;
        dataBean2D.moduleName = moduleName;
        dataBean2D.moduleId = moduleId;
        if (m_mapTranslateString.contains(moduleName))
        {
            dataBean2D.displayNameCN = m_mapTranslateString[moduleName].strDisplayNameCN;
            dataBean2D.displayNameEN = m_mapTranslateString[moduleName].strDisplayNameEN;
        }
        else
        {
            dataBean2D.displayNameCN = moduleName;
            dataBean2D.displayNameEN = moduleName;
        }

        for (int j=0; j<subObjectArray.size(); ++j)
        {
            QJsonObject subObject = subObjectArray.at(j).toObject();
            QString pubName = subObject["PubName"].toString();
            if (pubName.isEmpty())
            {
                continue;
            }
            CGet2DInputPointSupportListResponseBean1 paramBean;
            paramBean.paramName = pubName;
            if (m_mapTranslateString.contains(pubName))
            {
                paramBean.paramNameCN = m_mapTranslateString[pubName].strDisplayNameCN;
                paramBean.paramNameEN = m_mapTranslateString[pubName].strDisplayNameEN;
            }
            else
            {
                paramBean.paramNameCN = pubName;
                paramBean.paramNameEN = pubName;
            }
            dataBean2D.subParamList.append(paramBean);
        }

        result.m_data.runPointX.append(dataBean2D);
    }
    result.m_data.runPointY = result.m_data.runPointX;
    result.m_data.runPointAngle = result.m_data.runPointX;
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::get2DInputPointValue(const CMessageRequest &msg)
{
    CGet2DInputPointValueRequestParams request;
    request.fromJson(msg.getParams());

    CGet2DInputPointValueResponseResult result;
    QList<QPair<QString,CGet2DInputPointValueResponseBean1*>> vcResult;
    vcResult.append(qMakePair<QString,CGet2DInputPointValueResponseBean1*>("POINT_x",&result.m_data.runPointX));
    vcResult.append(qMakePair<QString,CGet2DInputPointValueResponseBean1*>("POINT_y",&result.m_data.runPointY));
    vcResult.append(qMakePair<QString,CGet2DInputPointValueResponseBean1*>("SINGLE_angle",&result.m_data.runPointAngle));
    for(auto itr=vcResult.begin(); itr!=vcResult.end(); ++itr)
    {
        QByteArray fileData;
        bool ret = m_pCameraDevice->SetIntValue("SubModuleID", request.m_data.moduleId);
        ret = ret && m_pCameraDevice->SetStringValue("SubModuleName", itr->first);
        ret = ret && m_pCameraDevice->SetEnumValue("SubModuleStyle", 1);//对应UIJson中的ui_param_sub_style字段
        ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "FileSubscribeData");
        ret = ret && m_pCameraDevice->FileAccessRead(fileData, "FileSubscribeData");
        if (!ret)
        {
            qDebug()<<itr->first<<" error:"<<m_pCameraDevice->getErrMessage();
            continue;
        }

        //保存到文件方便查询吧
        if (request.m_data.isSaveDbgFile)
        {
            QString str=QString("get2DInputPointValue-%1.json").arg(itr->first);
            QFile file(str);
            if (file.open(QFile::WriteOnly|QFile::Truncate))
            {
                file.write(fileData);
                file.close();
            }
        }

        QJsonParseError err;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
        if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
        {
            qDebug()<<"the string is not json object,"<<err.errorString();
            continue ;
        }

        QJsonObject dataObj = jsonDoc.object()["data"].toObject();
        itr->second->moduleName = dataObj["PubModuleName"].toString();
        itr->second->moduleId = dataObj["PubModuleID"].toInt();
        if (itr->second->moduleName.size()>0 && m_mapTranslateString.contains(itr->second->moduleName))
        {
            itr->second->displayNameCN = m_mapTranslateString[itr->second->moduleName].strDisplayNameCN;
            itr->second->displayNameEN = m_mapTranslateString[itr->second->moduleName].strDisplayNameEN;
        }
        itr->second->paramName = dataObj["PubParamName"].toString();
        if (itr->second->paramName.size()>0 && m_mapTranslateString.contains(itr->second->paramName))
        {
            itr->second->paramNameCN = m_mapTranslateString[itr->second->paramName].strDisplayNameCN;
            itr->second->paramNameEN = m_mapTranslateString[itr->second->paramName].strDisplayNameEN;
        }
    }

    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::set2DInputPointValue(const CMessageRequest &msg)
{
    CSet2DInputPointValueRequestParams request;
    request.fromJson(msg.getParams());

    QString strSubModuleName="";
    if ("runPointX" == request.m_data.paramName)
    {
        strSubModuleName = "POINT_x";
    }
    else if ("runPointY" == request.m_data.paramName)
    {
        strSubModuleName = "POINT_y";
    }
    else if ("runPointAngle" == request.m_data.paramName)
    {
        strSubModuleName = "SINGLE_angle";
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }
    bool ret = m_pCameraDevice->SetIntValue("SubModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("SubModuleName", strSubModuleName);
    ret = ret && m_pCameraDevice->SetEnumValue("SubModuleStyle", 1);//对应UIJson中的ui_param_sub_style字段
    ret = ret && m_pCameraDevice->SetIntValue("PubModuleID", request.m_data.parameter.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("PubModuleName", request.m_data.parameter.paramName);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandSubscription");

    CSet2DInputPointValueResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getOneKeyAdjustRunState(const CMessageRequest &msg)
{
    CGetOneKeyAdjustRunStateRequestParams request;
    request.fromJson(msg.getParams());

    MV_VS_INTVALUE stIntValue;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetIntValue("FocusState", stIntValue);

    CGetOneKeyAdjustRunStateResponseResult result;
    if (ret)
    {
        result.m_data.state = stIntValue.nCurValue;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

static void ParseROISupportParameters(const QJsonObject& jsonRoot, QList<CGetSupportRoiInfoResponseBean>& beanUI, QString strDisplayCn, QString strDisplayEn)
{
    const QString strUiType = jsonRoot["ui_type"].toString();
    const QString strUIPrmDisplayType = jsonRoot["ui_param_display_type"].toString();
    
    if (strUiType=="config_param" && (strUIPrmDisplayType=="find_roi" || strUIPrmDisplayType=="mask_roi"))
    {//说明是ROI的父节点
        strDisplayCn = jsonRoot["ui_display_cn_name"].toString();
        strDisplayEn = jsonRoot["ui_display_en_name"].toString();
    }

    const QString strRoiPrmType = jsonRoot["ui_roi_param_type"].toString();
    if (strUiType=="roi_param" && !strRoiPrmType.isEmpty() &&
        (strUIPrmDisplayType=="find_roi" || strUIPrmDisplayType=="mask_roi"))
    {//找到了ROI
        CGetSupportRoiInfoResponseBean bean;
        bean.displayNameCN = strDisplayCn;
        bean.displayNameEN = strDisplayEn;
        bean.paramName = jsonRoot["ui_param_name"].toString();
        bean.roiFlag = bean.paramName.contains("ModelRoi");
        if ("find_roi" == strUIPrmDisplayType)
        {
            bean.roiEditType = "find";
        }
        else if ("mask_roi" == strUIPrmDisplayType)
        {
            bean.roiEditType = "mask";
        }
        QString strRoiAllSupport = strRoiPrmType;
        strRoiAllSupport.replace("point","annular");//点就是圆环的意思
        bean.supportRoiType = strRoiAllSupport.split(',', QString::SkipEmptyParts);
        bean.roiMinCount = jsonRoot["ui_roi_num_min"].toInt();
        bean.roiMaxCount = jsonRoot["ui_roi_num_max"].toInt();
        bean.matchPointXName = jsonRoot["ui_param_match_point_x"].toString();
        bean.matchPointYName = jsonRoot["ui_param_match_point_y"].toString();
        bean.matchPointReset = jsonRoot["ui_param_reset_match_point"].toString();
        beanUI.append(bean);
    }

    for(auto itr = jsonRoot.constBegin(); itr!=jsonRoot.constEnd(); ++itr)
    {
        if (itr.value().isObject())
        {
            ParseROISupportParameters(itr.value().toObject(), beanUI, strDisplayCn, strDisplayEn);
            continue;
        }
        else if (itr.value().isArray())
        {
            const QJsonArray arr = itr.value().toArray();
            for (int i=0; i<arr.size();++i)
            {
                if (arr.at(i).isObject())
                {
                    ParseROISupportParameters(arr.at(i).toObject(), beanUI, strDisplayCn, strDisplayEn);
                }
            }
            continue;
        }
    }
    return ;
}

void CDobotDevice::getSupportRoiInfo(const CMessageRequest &msg)
{
    CGetSupportRoiInfoRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.moduleName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetStringValue("FileAccessName", request.m_data.moduleName);
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "Json");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getSupportRoiInfo.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CGetSupportRoiInfoResponseResult result;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    ParseROISupportParameters(jsonDoc.object(), result.m_data,"","");

    sendResponseSuccess(msg.getMsgUuid(), result);
}

static void ParseROIData(const QJsonObject& jsonRoot, QHash<QString, QList<std::shared_ptr<BaseRoiData>>>& beanRoi)
{
    for (auto itr=jsonRoot.begin(); itr!=jsonRoot.end(); ++itr)
    {
        const QString strKey = itr.key();
        if ("BoxRoiParameter" == strKey)
        {
            QJsonArray arr = itr.value().toArray();
            if (arr.isEmpty()) continue;
            QList<std::shared_ptr<BaseRoiData>> roiAll;
            for (int i=0; i<arr.size(); ++i)
            {
                if (!arr[i].isObject()) continue;
                QJsonObject roiObj = arr[i].toObject();

                auto ptrRoi = new BoxRoiData;
                ptrRoi->centerX = roiObj.value("CenterX").toDouble();
                ptrRoi->centerY = roiObj.value("CenterY").toDouble();
                ptrRoi->width = roiObj.value("Width").toDouble();
                ptrRoi->height = roiObj.value("Height").toDouble();
                ptrRoi->angle = roiObj.value("Angle").toDouble();
                ptrRoi->roiEditType = roiObj.value("Sign").toBool()?"find":"mask";
                std::shared_ptr<BaseRoiData> sptr(ptrRoi);
                roiAll.append(sptr);
            }
            beanRoi.insert("boxRoi", roiAll);
        }
        else if ("CircleRoiParameter" == strKey)
        {
            QJsonArray arr = itr.value().toArray();
            if (arr.isEmpty()) continue;
            QList<std::shared_ptr<BaseRoiData>> roiAll;
            for (int i=0; i<arr.size(); ++i)
            {
                if (!arr[i].isObject()) continue;
                QJsonObject roiObj = arr[i].toObject();

                auto ptrRoi = new CircleRoiData;
                ptrRoi->centerX = roiObj.value("CenterX").toDouble();
                ptrRoi->centerY = roiObj.value("CenterY").toDouble();
                ptrRoi->radius = roiObj.value("Radius").toDouble();
                ptrRoi->roiEditType = roiObj.value("Sign").toBool()?"find":"mask";
                std::shared_ptr<BaseRoiData> sptr(ptrRoi);
                roiAll.append(sptr);
            }
            beanRoi.insert("circleRoi", roiAll);
        }
        else if ("PolygonRoiParameter" == strKey)
        {
            QJsonArray arr = itr.value().toArray();
            if (arr.isEmpty()) continue;
            QList<std::shared_ptr<BaseRoiData>> roiAll;
            for (int i=0; i<arr.size(); ++i)
            {
                if (!arr[i].isObject()) continue;
                QJsonObject roiObj = arr[i].toObject();
                QJsonArray arrPt = roiObj["PointInfo"].toArray();
                if (arrPt.isEmpty()) continue;

                auto ptrRoi = new PolygonRoiData;
                ptrRoi->roiEditType = roiObj.value("Sign").toBool()?"find":"mask";
                for (int j=0; j<arrPt.size(); ++j)
                {
                    PolygonRoiData::Point2D pt2d;
                    pt2d.pointX = arrPt[j].toObject().value("PointX").toDouble();
                    pt2d.pointY = arrPt[j].toObject().value("PointY").toDouble();
                    ptrRoi->points.append(pt2d);
                }
                std::shared_ptr<BaseRoiData> sptr(ptrRoi);
                roiAll.append(sptr);
            }
            beanRoi.insert("polygonRoi", roiAll);
        }
        else if ("AnnularRoiParameter" == strKey)
        {
            QJsonArray arr = itr.value().toArray();
            if (arr.isEmpty()) continue;
            QList<std::shared_ptr<BaseRoiData>> roiAll;
            for (int i=0; i<arr.size(); ++i)
            {
                if (!arr[i].isObject()) continue;
                QJsonObject roiObj = arr[i].toObject();

                auto ptrRoi = new AnnularRoiData;
                ptrRoi->centerX = roiObj.value("CenterX").toDouble();
                ptrRoi->centerY = roiObj.value("CenterY").toDouble();
                ptrRoi->inRadius = roiObj.value("InRadius").toDouble();
                ptrRoi->outRadius = roiObj.value("OutRadius").toDouble();
                ptrRoi->roiEditType = roiObj.value("Sign").toBool()?"find":"mask";
                std::shared_ptr<BaseRoiData> sptr(ptrRoi);
                roiAll.append(sptr);
            }
            beanRoi.insert("annularRoi", roiAll);
        }
    }
}

void CDobotDevice::getRoiModule(const CMessageRequest &msg)
{
    CGetRoiModuleRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModuleRoi");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ModuleRoi");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getRoiModule.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CGetRoiModuleResponseResult result;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    ParseROIData(jsonDoc.object(), result.m_data.roi);

    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::getRoiTemplate(const CMessageRequest &msg)
{
    CGetRoiTemplateRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModelRoi");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ModelRoi");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getRoiTemplate.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    CGetRoiTemplateResponseResult result;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    ParseROIData(jsonDoc.object(), result.m_data.roi);

    sendResponseSuccess(msg.getMsgUuid(), result);
}

static QByteArray convertRoi2JsonString(const QHash<QString, QList<std::shared_ptr<BaseRoiData>>>& roi)
{
    QJsonObject objRoiFile;
    for (auto itr=roi.begin(); itr!=roi.end(); ++itr)
    {
        if (BoxRoiData::isMine(itr.key()))
        {
            QJsonArray arrRoi;
            for (auto itrData=itr.value().begin(); itrData!=itr.value().end(); ++itrData)
            {
                auto pRoiData = static_cast<BoxRoiData*>(itrData->get());
                QJsonObject roiObj;
                roiObj.insert("CenterX",pRoiData->centerX);
                roiObj.insert("CenterY",pRoiData->centerY);
                roiObj.insert("Width",pRoiData->width);
                roiObj.insert("Height",pRoiData->height);
                roiObj.insert("Angle",pRoiData->angle);
                roiObj.insert("Sign",(pRoiData->roiEditType=="find"));
                arrRoi.append(roiObj);
            }
            objRoiFile.insert("BoxRoiParameter", arrRoi);
        }
        else if (CircleRoiData::isMine(itr.key()))
        {
            QJsonArray arrRoi;
            for (auto itrData=itr.value().begin(); itrData!=itr.value().end(); ++itrData)
            {
                auto pRoiData = static_cast<CircleRoiData*>(itrData->get());
                QJsonObject roiObj;
                roiObj.insert("CenterX",pRoiData->centerX);
                roiObj.insert("CenterY",pRoiData->centerY);
                roiObj.insert("Radius",pRoiData->radius);
                roiObj.insert("Sign",(pRoiData->roiEditType=="find"));
                arrRoi.append(roiObj);
            }
            objRoiFile.insert("CircleRoiParameter", arrRoi);
        }
        else if (AnnularRoiData::isMine(itr.key()))
        {
            QJsonArray arrRoi;
            for (auto itrData=itr.value().begin(); itrData!=itr.value().end(); ++itrData)
            {
                auto pRoiData = static_cast<AnnularRoiData*>(itrData->get());
                QJsonObject roiObj;
                roiObj.insert("CenterX",pRoiData->centerX);
                roiObj.insert("CenterY",pRoiData->centerY);
                roiObj.insert("InRadius",pRoiData->inRadius);
                roiObj.insert("OutRadius",pRoiData->outRadius);
                roiObj.insert("StartAngle",0);
                roiObj.insert("AngleExtend",360);
                roiObj.insert("Sign",(pRoiData->roiEditType=="find"));
                arrRoi.append(roiObj);
            }
            objRoiFile.insert("AnnularRoiParameter", arrRoi);
        }
        else if (PolygonRoiData::isMine(itr.key()))
        {
            QJsonArray arrRoi;
            for (auto itrData=itr.value().begin(); itrData!=itr.value().end(); ++itrData)
            {
                auto pRoiData = static_cast<PolygonRoiData*>(itrData->get());
                QJsonObject roiObj;
                roiObj.insert("Sign",(pRoiData->roiEditType=="find"));
                roiObj.insert("PointNum", pRoiData->points.size());
                QJsonArray arrPt;
                for (int pt=0; pt<pRoiData->points.size(); ++pt)
                {
                    QJsonObject opt;
                    opt.insert("PointX", pRoiData->points[pt].pointX);
                    opt.insert("PointY", pRoiData->points[pt].pointY);
                    arrPt.append(opt);
                }
                roiObj.insert("PointInfo", arrPt);
                arrRoi.append(roiObj);
            }
            objRoiFile.insert("PolygonRoiParameter", arrRoi);
        }
    }

    QJsonDocument doc(objRoiFile);
    return doc.toJson();
}

void CDobotDevice::setRoiModule(const CMessageRequest &msg)
{
    CSetRoiModuleRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData = convertRoi2JsonString(request.m_data.roi);
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModuleRoi");
    ret = ret && m_pCameraDevice->FileAccessWrite(fileData, "ModuleRoi");
    ret = ret && m_pCameraDevice->SetCommandValue("CommandAlgoModuleParamRoi");

    CSetRoiModuleResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::setRoiTemplate(const CMessageRequest &msg)
{
    CSetRoiTemplateRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData = convertRoi2JsonString(request.m_data.roi);
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ModelRoi");
    ret = ret && m_pCameraDevice->FileAccessWrite(fileData, "ModelRoi");
    ret = ret && m_pCameraDevice->SetCommandValue("CommandAlgoModelRoi");

    CSetRoiTemplateResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getRoiContourPoints(const CMessageRequest &msg)
{
    CGetRoiContourPointsRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "ImageMask");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ImageMask");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getRoiContourPoints.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    qDebug()<<"getRoiContourPoints:"<<fileData;

    CGetRoiContourPointsResponseResult result;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonArray arrPoints = jsonDoc.object().value("line_list").toArray();
    if (arrPoints.size()>0)
    {
        QJsonArray allPoints = arrPoints[0].toObject().value("point_list").toArray();
        for (int i=0; i<allPoints.size(); ++i)
        {
            QJsonObject objPt = allPoints[i].toObject();
            if (objPt.isEmpty()) continue;
            CGetRoiContourPointsResponseBean::Point2D pt;
            pt.x = objPt.value("x").toDouble();
            pt.y = objPt.value("y").toDouble();

            result.m_data.points.append(pt);
        }
    }

    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::setTemplateRoiMatchPoint(const CMessageRequest &msg)
{
    CSetTemplateRoiMatchPointRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetFloatValue(request.m_data.matchPointXName, request.m_data.pointX);
    ret = ret && m_pCameraDevice->SetFloatValue(request.m_data.matchPointYName, request.m_data.pointY);

    CSetTemplateRoiMatchPointResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getTemplateRoiMatchPoint(const CMessageRequest &msg)
{
    CGetTemplateRoiMatchPointRequestParams request;
    request.fromJson(msg.getParams());

    MV_VS_FLOATVALUE stFloatValueX;
    MV_VS_FLOATVALUE stFloatValueY;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetFloatValue(request.m_data.matchPointXName, stFloatValueX);
    ret = ret && m_pCameraDevice->GetFloatValue(request.m_data.matchPointYName, stFloatValueY);

    CGetTemplateRoiMatchPointResponseResult result;
    if (ret)
    {
        result.m_data.pointX = stFloatValueX.fCurValue;
        result.m_data.pointY = stFloatValueY.fCurValue;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::resetTemplateRoiMatchPoint(const CMessageRequest &msg)
{
    CResetTemplateRoiMatchPointRequestParams request;
    request.fromJson(msg.getParams());

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetBoolValue(request.m_data.matchPointReset, true);

    CResetTemplateRoiMatchPointResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::resetProjectRunResult(const CMessageRequest &msg)
{
    if (true)
    {
        //重置解决方案数据，清空结果
        QMutexLocker guard(&m_mtxProjectRunResult);
        m_objProjectRunResult.clear();
    }
    bool ret = m_pCameraDevice->SetCommandValue("ScDeviceCmdResetNumber");
    CResetProjectRunResultResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getProjectRunResult(const CMessageRequest &msg)
{
    CGetProjectRunResultRequestParams request;
    request.fromJson(msg.getParams());

    CGetProjectRunResultResponseResult result;
    {
        QMutexLocker guard(&m_mtxProjectRunResult);
        result.m_data = m_objProjectRunResult;
        m_objProjectRunResult.clear();
    }
    if (request.m_data.allModuleName.size() > 0)
    {//只保留需要的
        auto itr = result.m_data.data.begin();
        while (itr != result.m_data.data.end())
        {
            if (request.m_data.allModuleName.contains(itr->moduleName))
            {
                ++itr;
            }
            else
            {
                itr = result.m_data.data.erase(itr);
            }
        }
    }

    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::getCameraCalibratePoint(const CMessageRequest &msg)
{
    CGetCameraCalibratePointRequestParams request;
    request.fromJson(msg.getParams());

    MV_VS_INTVALUE stParamT,stParamR;
    memset(&stParamT, 0, sizeof(MV_VS_INTVALUE));
    memset(&stParamR, 0, sizeof(MV_VS_INTVALUE));
    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetIntValue("MatchCalibTranslationTimes", stParamT);
    ret = ret && m_pCameraDevice->GetIntValue("MatchCalibRotationTimes", stParamR);
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "ScAlgoCalibCoord");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getCameraCalibratePoint.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    qDebug()<<"getCameraCalibratePoint:"<<fileData;

    CGetCameraCalibratePointResponseResult result;
    QStringList allLines = QString(fileData).split(QRegExp("[\\r\\n]+"),QString::SkipEmptyParts); //按照\r \n分割
    if (allLines.size() >= stParamT.nCurValue)
    {
        for (int i=0; i<stParamT.nCurValue; ++i)
        {
            QStringList points = allLines.takeFirst().split(QRegExp("\\s+"),QString::SkipEmptyParts); //按照空白符分割
            if (points.size()>=5)
            {//数据依次为x坐标点、y坐标点、x物理坐标点、y物理坐标点、角度
                CGetCameraCalibratePointResponseBean bean;
                bean.imageX = points[0].toDouble();
                bean.imageY = points[1].toDouble();
                bean.physicalX = points[2].toDouble();
                bean.physicalY = points[3].toDouble();
                bean.angle = points[4].toDouble();
                result.m_data.transformPoints.push_back(bean);
            }
        }
    }
    if (allLines.size() >= stParamR.nCurValue)
    {
        for (int i=0; i<stParamR.nCurValue; ++i)
        {
            QStringList points = allLines.takeFirst().split(QRegExp("\\s+"),QString::SkipEmptyParts); //按照空白符分割
            if (points.size()>=5)
            {//数据依次为x坐标点、y坐标点、x物理坐标点、y物理坐标点、角度
                CGetCameraCalibratePointResponseBean bean;
                bean.imageX = points[0].toDouble();
                bean.imageY = points[1].toDouble();
                bean.physicalX = points[2].toDouble();
                bean.physicalY = points[3].toDouble();
                bean.angle = points[4].toDouble();
                result.m_data.rotaPoints.push_back(bean);
            }
        }
    }

    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::setCameraCalibratePoint(const CMessageRequest &msg)
{
    CSetCameraCalibratePointRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    for (int i=0; i<request.m_data.transformPoints.size(); ++i)
    {
        //保留6位小数，4个空格分开，\r\n换行
        auto& point = request.m_data.transformPoints[i];
        QString strData = QString::asprintf("%.6f    %.6f    %.6f    %.6f    %.6f    \r\n",
                                            point.imageX,point.imageY,point.physicalX,point.physicalY,point.angle);
        fileData.append(strData);
    }
    for (int i=0; i<request.m_data.rotaPoints.size(); ++i)
    {
        //保留6位小数，4个空格分开，\r\n换行
        auto& point = request.m_data.rotaPoints[i];
        QString strData = QString::asprintf("%.6f    %.6f    %.6f    %.6f    %.6f    \r\n",
                                            point.imageX,point.imageY,point.physicalX,point.physicalY,point.angle);
        fileData.append(strData);
    }


    MV_VS_INTVALUE stParamT,stParamR;
    memset(&stParamT, 0, sizeof(MV_VS_INTVALUE));
    memset(&stParamR, 0, sizeof(MV_VS_INTVALUE));
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->GetIntValue("MatchCalibTranslationTimes", stParamT);
    ret = ret && m_pCameraDevice->GetIntValue("MatchCalibRotationTimes", stParamR);
    if (request.m_data.transformPoints.size() < stParamT.nMin ||
            request.m_data.transformPoints.size() > stParamT.nMax ||
            request.m_data.rotaPoints.size() < stParamR.nMin ||
            request.m_data.rotaPoints.size() > stParamR.nMax)
    {
        qDebug()<<QString::asprintf("transformPoints.size=%d,range(%lld,%lld),rotaPoints.size=%d,range(%lld,%lld)",
                                    request.m_data.transformPoints.size(),stParamT.nMin,stParamT.nMax,
                                    request.m_data.rotaPoints.size(),stParamR.nMin,stParamR.nMax);
        sendResponseError(msg.getMsgUuid(), DT_ERR_PARAM_OUT_RANGE);
        return ;
    }
    ret = ret && m_pCameraDevice->SetIntValue("MatchCalibTranslationTimes", request.m_data.transformPoints.size());
    ret = ret && m_pCameraDevice->SetIntValue("MatchCalibRotationTimes", request.m_data.rotaPoints.size());
    ret = ret && m_pCameraDevice->FileAccessWrite(fileData, "ScAlgoCalibCoord");
    ret = ret && m_pCameraDevice->SetBoolValue("MatchCalibUploadCoord", true);
    CSetCameraCalibratePointResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}

void CDobotDevice::getOutputResultSupportList(const CMessageRequest &msg)
{
    CGetOutputResultSupportListRequestParams request;
    request.fromJson(msg.getParams());

    QString strFilterSubType="";
    if ("null" == request.m_data.filterSubType) strFilterSubType="FILTER_NULL";
    else if ("status" == request.m_data.filterSubType) strFilterSubType="status";
    else strFilterSubType="status";

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetStringValue("FilterSubType", strFilterSubType);
    ret = ret && m_pCameraDevice->SetEnumValue("SubModuleStyle", 1);
    ret = ret && m_pCameraDevice->SetCommandValue("CommandSubscribeSource");
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "SubscribeSource");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "SubscribeSource");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getOutputResultSupportList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }
    QJsonArray dataArray = jsonDoc.object()["data"].toArray();

    CGetOutputResultSupportListResponseResult result;
    for (int i=0; i<dataArray.size(); ++i)
    {
        QJsonObject dataObject = dataArray.at(i).toObject();
        int moduleId = dataObject["ModuleID"].toInt();
        QString moduleName = dataObject["ModuleName"].toString();
        QJsonArray subObjectArray = dataObject["SubObject"].toArray();
        if (moduleName.isEmpty() || subObjectArray.isEmpty())
        {
            continue;
        }

        CGetOutputResultSupportListResponseBean2 dataBean;
        dataBean.moduleName = moduleName;
        dataBean.moduleId = moduleId;
        if (m_mapTranslateString.contains(moduleName))
        {
            dataBean.displayNameCN = m_mapTranslateString[moduleName].strDisplayNameCN;
            dataBean.displayNameEN = m_mapTranslateString[moduleName].strDisplayNameEN;
        }
        else
        {
            dataBean.displayNameCN = moduleName;
            dataBean.displayNameEN = moduleName;
        }

        for (int j=0; j<subObjectArray.size(); ++j)
        {
            QJsonObject subObject = subObjectArray.at(j).toObject();
            QString pubName = subObject["PubName"].toString();
            if (pubName.isEmpty())
            {
                continue;
            }
            CGetOutputResultSupportListResponseBean1 paramBean;
            paramBean.paramName = pubName;
            paramBean.paramType = subObject["PubNameType"].toString();
            if (m_mapTranslateString.contains(pubName))
            {
                paramBean.paramNameCN = m_mapTranslateString[pubName].strDisplayNameCN;
                paramBean.paramNameEN = m_mapTranslateString[pubName].strDisplayNameEN;
            }
            else
            {
                paramBean.paramNameCN = pubName;
                paramBean.paramNameEN = pubName;
            }
            dataBean.subParamList.append(paramBean);
        }
        result.m_data.append(dataBean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::getOutputResultDataList(const CMessageRequest &msg)
{
    CGetOutputResultDataListRequestParams request;
    request.fromJson(msg.getParams());

    QByteArray fileData;
    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "AlgoPrivate");
    ret = ret && m_pCameraDevice->FileAccessRead(fileData, "AlgoPrivate");
    if (!ret)
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
        return ;
    }

    //保存到文件方便查询吧
    if (request.m_data.isSaveDbgFile)
    {
        QString str=QString("getOutputResultDataList.json");
        QFile file(str);
        if (file.open(QFile::WriteOnly|QFile::Truncate))
        {
            file.write(fileData);
            file.close();
        }
    }

    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData, &err);
    if (err.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug()<<"the string is not json object,"<<err.errorString();
        sendResponseError(msg.getMsgUuid(), DT_ERR_CONTENT);
        return ;
    }

    CGetOutputResultDataListResponseResult result;
    QJsonObject jsObject = jsonDoc.object();
    QJsonArray arrFile = jsObject["SubParamList"].toArray();
    result.m_data.moduleName = jsObject["ModuleName"].toString(request.m_data.moduleName);
    result.m_data.moduleId = jsObject["ModuleID"].toInt(request.m_data.moduleId);
    for (int i=0; i<arrFile.size(); ++i)
    {
        QJsonObject logicData = arrFile.at(i).toObject();
        bool bIsObject = logicData.contains("Array")?false:true;

        CGetOutputResultDataListResponseBean1 bean(bIsObject);
        bean.customEdit = logicData["IsCustomEdit"].toInt(false)!=0;
        bean.separator = logicData["Separator"].toString();
        bean.resultNGCustom = logicData["ResultNGCustom"].toString();
        bean.resultOKCustom = logicData["ResultOKCustom"].toString();
        if (bIsObject)
        {
            bean.dataObj.paramValue = logicData["ParamValue"].toString();
            bean.dataObj.showValueCN = logicData["ShowValue_CN"].toString();
            bean.dataObj.showValueEN = logicData["ShowValue_EN"].toString();
            bean.dataObj.separator = bean.separator;
        }
        else
        {
            QJsonArray arr = logicData["Array"].toArray();
            for(auto itr = arr.begin(); itr!=arr.end(); ++itr)
            {
                if (!itr->isObject())
                {
                    continue;
                }
                QJsonObject beanTmpObj = itr->toObject();
                CGetOutputResultDataListResponseBean beanTmp;
                beanTmp.paramValue = beanTmpObj["ParamValue"].toString();
                beanTmp.showValueCN = beanTmpObj["ShowValue_CN"].toString();
                beanTmp.showValueEN = beanTmpObj["ShowValue_EN"].toString();
                beanTmp.separator = beanTmpObj["Separator"].toString();
                bean.dataArr.append(beanTmp);
            }
        }
        result.m_data.subParamList.append(bean);
    }
    sendResponseSuccess(msg.getMsgUuid(), result);
}

void CDobotDevice::setOutputResultDataList(const CMessageRequest &msg)
{
    CSetOutputResultDataListRequestParams request;
    request.fromJson(msg.getParams());
    if (request.m_data.moduleName.isEmpty())
    {
        sendResponseError(msg.getMsgUuid(), DT_ERR_INVALID_PARAMS);
        return ;
    }

    static auto funcGetFmtString = [](QString paramType){
        QString strFmt;
        if ("int"==paramType) strFmt = "%0d";
        else if ("float"==paramType) strFmt = "%1.3f";
        else if ("string"==paramType) strFmt = "%s";
        return strFmt;
    };

    QJsonObject jsObject;
    jsObject.insert("ModuleName","format");
    jsObject.insert("ModuleID",request.m_data.moduleId);
    QJsonArray dataArray;
    for(auto itr=request.m_data.subParamList.begin(); itr != request.m_data.subParamList.end(); ++itr)
    {
        QJsonObject param;
        if (itr->isObject())
        {
            if (itr->dataObj.paramName=="\\r" || itr->dataObj.paramName=="\\n" ||
                itr->dataObj.paramName=="\\r\\n")
            {
                param.insert("IsCustomEdit", 0);
                param.insert("ParamValue", itr->dataObj.paramName);
                param.insert("ResultNGCustom", "");
                param.insert("ResultOKCustom", "");
                param.insert("Separator", "");
                param.insert("ShowValue_CN", itr->dataObj.paramName);
                param.insert("ShowValue_EN", itr->dataObj.paramName);
            }
            else if (itr->customEdit)
            {
                param.insert("IsCustomEdit", 1);
                param.insert("ParamValue", itr->dataObj.paramName);
                param.insert("ResultNGCustom", "");
                param.insert("ResultOKCustom", "");
                param.insert("Separator", "");
                param.insert("ShowValue_CN", itr->dataObj.paramName);
                param.insert("ShowValue_EN", itr->dataObj.paramName);
            }
            else
            {
                QString strModuleNameCN = itr->dataObj.moduleName;
                QString strModuleNameEN = itr->dataObj.moduleName;
                if (m_mapTranslateString.contains(itr->dataObj.moduleName))
                {
                    strModuleNameCN = m_mapTranslateString[itr->dataObj.moduleName].strDisplayNameCN;
                    strModuleNameEN = m_mapTranslateString[itr->dataObj.moduleName].strDisplayNameEN;
                }
                QString strParamNameCN = itr->dataObj.paramName;
                QString strParamNameEN = itr->dataObj.paramName;
                if (m_mapTranslateString.contains(itr->dataObj.paramName))
                {
                    strParamNameCN = m_mapTranslateString[itr->dataObj.paramName].strDisplayNameCN;
                    strParamNameEN = m_mapTranslateString[itr->dataObj.paramName].strDisplayNameEN;
                }
                QString strFmt = funcGetFmtString(itr->dataObj.paramType);

                param.insert("IsCustomEdit", 0);
                param.insert("ParamValue", QString("<%1 %2.%3(%4)>[0]").arg(itr->dataObj.moduleId).arg(itr->dataObj.moduleName).arg(itr->dataObj.paramName).arg(strFmt));
                param.insert("ResultNGCustom", itr->resultNGCustom);
                param.insert("ResultOKCustom", itr->resultOKCustom);
                param.insert("Separator", itr->separator);
                param.insert("ShowValue_CN", QString("<%1 %2.%3(%4)>[0]").arg(itr->dataObj.moduleId).arg(strModuleNameCN).arg(strParamNameCN).arg(strFmt));
                param.insert("ShowValue_EN", QString("<%1 %2.%3(%4)>[0]").arg(itr->dataObj.moduleId).arg(strModuleNameEN).arg(strParamNameEN).arg(strFmt));
            }
        }
        else
        {
            QJsonArray arrjson;
            for (auto itrArr = itr->dataArr.begin(); itrArr!=itr->dataArr.end(); ++itrArr)
            {
                QString strModuleNameCN = itrArr->moduleName;
                QString strModuleNameEN = itrArr->moduleName;
                if (m_mapTranslateString.contains(itrArr->moduleName))
                {
                    strModuleNameCN = m_mapTranslateString[itrArr->moduleName].strDisplayNameCN;
                    strModuleNameEN = m_mapTranslateString[itrArr->moduleName].strDisplayNameEN;
                }
                QString strParamNameCN = itrArr->paramName;
                QString strParamNameEN = itrArr->paramName;
                if (m_mapTranslateString.contains(itrArr->paramName))
                {
                    strParamNameCN = m_mapTranslateString[itrArr->paramName].strDisplayNameCN;
                    strParamNameEN = m_mapTranslateString[itrArr->paramName].strDisplayNameEN;
                }
                QString strFmt = funcGetFmtString(itrArr->paramType);
                QJsonObject arrObj;
                arrObj.insert("ParamValue", QString("<%1 %2.%3(%4)>[*]").arg(itrArr->moduleId).arg(itrArr->moduleName).arg(itrArr->paramName).arg(strFmt));
                arrObj.insert("Separator", itrArr->separator);
                arrObj.insert("ShowValue_CN", QString("<%1 %2.%3(%4)>[*]").arg(itrArr->moduleId).arg(strModuleNameCN).arg(strParamNameCN).arg(strFmt));
                arrObj.insert("ShowValue_EN", QString("<%1 %2.%3(%4)>[*]").arg(itrArr->moduleId).arg(strModuleNameEN).arg(strParamNameEN).arg(strFmt));
                arrjson.append(arrObj);
            }
            param.insert("Array", arrjson);
            param.insert("Separator", itr->separator);
        }
        dataArray.append(param);
    }
    jsObject.insert("SubParamList",dataArray);
    QJsonDocument doc(jsObject);
    QByteArray fileData = doc.toJson();

    bool ret = m_pCameraDevice->SetIntValue("ModuleID", request.m_data.moduleId);
    ret = ret && m_pCameraDevice->SetEnumValueByString("FileSelector", "AlgoPrivate");
    ret = ret && m_pCameraDevice->FileAccessWrite(fileData, "AlgoPrivate");

    CSetOutputResultDataListResponseResult result;
    if (ret)
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), m_pCameraDevice->getErrCode(), m_pCameraDevice->getErrMessage());
    }
}
