#include "DobotDevice.h"
#include<QStandardPaths>
#include <QEventLoop>
#include <QThread>
#include <QtGlobal>
#include <QCoreApplication>

struct SafeFtp
{
    QEventLoop loop;
    CSFtpFileClient* pFtp;
    SafeFtp(){
        pFtp = new CSFtpFileClient;
    }
    ~SafeFtp(){
        loop.quit();
        pFtp->deleteLater();
    }
};

CDobotDevice::CDobotDevice(QObject *parent) : QObject(parent)
{
    initFunctionMapper();
}

CDobotDevice::~CDobotDevice()
{
    deleteAllCacheId();
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

QString CDobotDevice::fixSavePath(const QString &strPath)
{
    QString strTmp;
    if (strPath.isEmpty())
    {
        return strTmp;
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

QSharedPointer<SafeFtp> CDobotDevice::connectFtpIf(const QString strIp, int port)
{
    SFtpConnectParam prm;
    prm.iPort = port;
    prm.strPwd = "dobot";
    prm.strHost = strIp;
    prm.strUserName = "root";
    prm.iTimeoutSeconds = 3;

    QSharedPointer<SafeFtp> sptr = QSharedPointer<SafeFtp>::create();
    connect(sptr->pFtp, &CSFtpFileClient::signalConnected, this, [sptr]{
        qDebug()<<"sftp has connected!";
        sptr->loop.quit();
    }, Qt::ConnectionType::QueuedConnection);
    connect(sptr->pFtp, &CSFtpFileClient::signalDisconnected, this, [sptr]{
        qDebug()<<"sftp has disconnected!";
        sptr->loop.quit();
    }, Qt::ConnectionType::QueuedConnection);
    connect(sptr->pFtp, &CSFtpFileClient::signalConnectError, this, [sptr](QString strErr){
        qDebug()<<"sftp has a error:"<<strErr;
        sptr->loop.quit();
    }, Qt::ConnectionType::QueuedConnection);

    sptr->pFtp->connectHost(prm);
    sptr->loop.exec();
    if (sptr->pFtp->isConnected()) return sptr;
    return QSharedPointer<SafeFtp>();
}

void CDobotDevice::closeFtpIf(QSharedPointer<SafeFtp> sptr)
{
    if (sptr.isNull()) return;
    if (sptr->pFtp->isConnected())
    {
        sptr->pFtp->disconnectHost();
        sptr->loop.exec();
    }
}

void CDobotDevice::getInfoList(const CMessageRequest &msg)
{
    CGetInfoListRequestParams request;
    request.fromJson(msg.getParams());

    QList<QSsh::SftpFileInfo> retData;
    auto data = innerGetInfoList(request.m_data.ip, request.m_data.port, request.m_data.directory, retData);
    CGetInfoListResponseResult result;
    if (std::get<0>(data))
    {
        for (int i=0; i<retData.size(); ++i)
        {
            CGetInfoListBean bean;
            bean.name = retData[i].name;
            if (request.m_data.type=="file")
            {
                if (retData[i].type==QSsh::SftpFileType::FileTypeRegular){
                    bean.type = "file";
                    bean.size = retData[i].size;
                    result.m_data.append(bean);
                }
            }
            else if (request.m_data.type=="dir")
            {
                if (retData[i].type==QSsh::SftpFileType::FileTypeDirectory){
                    bean.type = "dir";
                    bean.size = 0;
                    result.m_data.append(bean);
                }
            }
            else
            {
                if (retData[i].type==QSsh::SftpFileType::FileTypeRegular){
                    bean.type = "file";
                    bean.size = retData[i].size;
                    result.m_data.append(bean);
                }
                else if (retData[i].type==QSsh::SftpFileType::FileTypeDirectory){
                    bean.type = "dir";
                    bean.size = 0;
                    result.m_data.append(bean);
                }
            }
        }
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

std::tuple<bool, int, QString> CDobotDevice::innerGetInfoList(const QString ip, int port, const QString strRemoteDir, QList<QSsh::SftpFileInfo>& retData)
{
    if (!checkIpAddressValid(ip) || port<=0 || port>=65535 || strRemoteDir.isEmpty())
    {
        return std::make_tuple(false, DT_ERR_INVALID_PARAMS, QString("invalid parameter"));
    }
    auto ftp = connectFtpIf(ip, port);
    if (ftp.isNull())
    {
        return std::make_tuple(false, DT_ERR_NOT_CONNECT, QString("connect sftp error"));
    }

    SFtpOptFile opt;
    opt.strLocalPath = "";
    opt.strRemotePath = strRemoteDir;
    opt.opt = SFtpOption::OPT_LIST_REMOTE_DIR;

    QEventLoop loop;
    QMetaObject::Connection lambda =
    connect(ftp->pFtp, &CSFtpFileClient::signalFinishedListRemoteDir, this, [&loop,&retData](QString strRemoteDir,QList<QSsh::SftpFileInfo> fileInfoList,QString strErrMsg){
            qDebug()<<"list remote path:"<<strRemoteDir<<",errmsg:"<<strErrMsg<<",size="<<fileInfoList.size();
            loop.setProperty("errmsg",strErrMsg);
            for (int i=0; i<fileInfoList.size(); ++i)
            {
                retData.push_back(fileInfoList[i]);
            }
            loop.quit();
        },Qt::ConnectionType::QueuedConnection);
    ftp->pFtp->ssh(opt);
    loop.exec();
    ftp->pFtp->disconnect(lambda);

    closeFtpIf(ftp);

    QString strErr = loop.property("errmsg").toString();
    if (strErr.isEmpty())
    {
        return std::make_tuple(true, DT_NO_ERROR, strErr);
    }
    return std::make_tuple(false, DT_ERR_READ_FILE, strErr);
}

void CDobotDevice::downloadFile(const CMessageRequest &msg)
{
    CDownloadFileRequestParams request;
    request.fromJson(msg.getParams());
    auto data = inneDownloadFile(request.m_data.ip, request.m_data.port, request.m_data.localFilePath, request.m_data.remoteFilePath);
    CDownloadFileResponseResult result;
    if (std::get<0>(data))
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

std::tuple<bool, int, QString> CDobotDevice::inneDownloadFile(const QString ip, int port, const QString strLocalFile, const QString strRemoteFile)
{
    if (!checkIpAddressValid(ip) || port<=0 || port>=65535 || strLocalFile.isEmpty() || strRemoteFile.isEmpty())
    {
        return std::make_tuple(false, DT_ERR_INVALID_PARAMS, QString("invalid parameter"));
    }
    auto ftp = connectFtpIf(ip, port);
    if (ftp.isNull())
    {
        return std::make_tuple(false, DT_ERR_NOT_CONNECT, QString("connect sftp error"));
    }

    SFtpOptFile opt;
    opt.strLocalPath = strLocalFile;
    opt.strRemotePath = strRemoteFile;
    opt.opt = SFtpOption::OPT_DOWNLOAD_FILE;

    QEventLoop loop;
    QMetaObject::Connection lambda =
    connect(ftp->pFtp, &CSFtpFileClient::signalFinishedDownloadFile, this, [&loop](QString strLocalFile, QString strRemoteFile,QString strErrMsg){
            qDebug()<<"download file:"<<strLocalFile<<",remotefile:"<<strRemoteFile<<",errmsg:"<<strErrMsg;
            loop.setProperty("errmsg",strErrMsg);
            loop.quit();
        },Qt::ConnectionType::QueuedConnection);
    ftp->pFtp->ssh(opt);
    loop.exec();
    ftp->pFtp->disconnect(lambda);

    closeFtpIf(ftp);

    QString strErr = loop.property("errmsg").toString();
    if (strErr.isEmpty())
    {
        return std::make_tuple(true, DT_NO_ERROR, strErr);
    }
    return std::make_tuple(false, DT_ERR_READ_FILE, strErr);
}

void CDobotDevice::uploadFile(const CMessageRequest &msg)
{
    CUploadFileRequestParams request;
    request.fromJson(msg.getParams());
    auto data = innerUploadFile(request.m_data.ip, request.m_data.port, request.m_data.localFilePath, request.m_data.remoteFilePath);
    CUploadFileResponseResult result;
    if (std::get<0>(data))
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

std::tuple<bool, int, QString> CDobotDevice::innerUploadFile(const QString ip, int port, const QString strLocalFile, const QString strRemoteFile)
{
    if (!checkIpAddressValid(ip) || port<=0 || port>=65535 || strLocalFile.isEmpty() || strRemoteFile.isEmpty())
    {
        return std::make_tuple(false, DT_ERR_INVALID_PARAMS, QString("invalid parameter"));
    }
    QFileInfo fi(strLocalFile);
    if (!fi.exists() || !fi.isFile())
    {
        qDebug()<<"the local file is not exist,file="<<strLocalFile;
        return std::make_tuple(false, DT_ERR_FILE_NOT_EXIST, QString("the local file does not exist"));
    }
    auto ftp = connectFtpIf(ip, port);
    if (ftp.isNull())
    {
        return std::make_tuple(false, DT_ERR_NOT_CONNECT, QString("connect sftp error"));
    }

    SFtpOptFile opt;
    opt.strLocalPath = strLocalFile;
    opt.strRemotePath = strRemoteFile;
    opt.opt = SFtpOption::OPT_UPLOAD_FILE;

    QEventLoop loop;
    QMetaObject::Connection lambda =
    connect(ftp->pFtp, &CSFtpFileClient::signalFinishedUploadFile, this, [&loop](QString strLocalFile, QString strRemoteFile,QString strErrMsg){
        qDebug()<<"upload file:"<<strLocalFile<<",remotefile:"<<strRemoteFile<<",errmsg:"<<strErrMsg;
        loop.setProperty("errmsg",strErrMsg);
        loop.quit();
    },Qt::ConnectionType::QueuedConnection);
    ftp->pFtp->ssh(opt);
    loop.exec();
    ftp->pFtp->disconnect(lambda);

    closeFtpIf(ftp);

    QString strErr = loop.property("errmsg").toString();
    if (strErr.isEmpty())
    {
        return std::make_tuple(true, DT_NO_ERROR, strErr);
    }
    return std::make_tuple(false, DT_ERR_WRITE_FILE, strErr);
}

void CDobotDevice::getAllProject(const CMessageRequest &msg)
{
    CGetAllProjectRequestParams request;
    request.fromJson(msg.getParams());

    QList<QSsh::SftpFileInfo> retData;
    std::tuple<bool, int, QString> data;
    for (int i=0; i<3; ++i)
    {
        data = innerGetInfoList(request.m_data.ip, request.m_data.port, "/dobot/userdata/project/project/", retData);
        if (std::get<0>(data)) break;
        else
        {
            QThread::msleep(200);
        }
    }

    CGetAllProjectResponseResult result;
    if (std::get<0>(data))
    {
        for (int i=0; i<retData.size(); ++i)
        {
            if (retData[i].type==QSsh::SftpFileType::FileTypeDirectory)
            {
                CGetAllProjectBean bean;
                bean.projectName = retData[i].name;
                result.m_data.append(bean);
            }
        }
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

void CDobotDevice::getProjectFiles(const CMessageRequest &msg)
{
    CGetProjectFilesRequestParams request;
    request.fromJson(msg.getParams());

    QString strRemoteFile = QString("/dobot/userdata/project/project/%1").arg(request.m_data.projectName);

    QList<QSsh::SftpFileInfo> retData;
    std::tuple<bool, int, QString> data;
    for (int i=0; i<3; ++i)
    {
        data = innerGetInfoList(request.m_data.ip, request.m_data.port, strRemoteFile, retData);
        if (std::get<0>(data)) break;
        else
        {
            QThread::msleep(200);
        }
    }
    CGetProjectFilesResponseResult result;
    if (std::get<0>(data))
    {
        for (int i=0; i<retData.size(); ++i)
        {
            if (retData[i].type==QSsh::SftpFileType::FileTypeRegular)
            {
                CGetProjectFilesBean bean;
                bean.fileName = retData[i].name;
                result.m_data.append(bean);
            }
        }
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

void CDobotDevice::readProjectFile(const CMessageRequest &msg)
{
    CReadProjectFileRequestParams request;
    request.fromJson(msg.getParams());

    QString strRemoteFile = QString("/dobot/userdata/project/project/%1/%2")
            .arg(request.m_data.projectName).arg(request.m_data.fileName);
    QByteArray buffer;
    std::tuple<bool, int, QString> data;
    for (int i=0; i<3; ++i)
    {
        data = innerReadFile(request.m_data.ip, request.m_data.port, strRemoteFile, buffer);
        if (std::get<0>(data)) break;
        else
        {
            QThread::msleep(200);
        }
    }
    CReadProjectFileResponseResult result;
    if (std::get<0>(data))
    {
        result.m_data.content = buffer;
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

std::tuple<bool, int, QString> CDobotDevice::innerReadFile(const QString ip, int port, const QString strRemoteFile, QByteArray& buffer)
{
    if (!checkIpAddressValid(ip) || port<=0 || port>=65535 || strRemoteFile.isEmpty())
    {
        return std::make_tuple(false, DT_ERR_INVALID_PARAMS, QString("invalid parameter"));
    }
    auto ftp = connectFtpIf(ip, port);
    if (ftp.isNull())
    {
        return std::make_tuple(false, DT_ERR_NOT_CONNECT, QString("connect sftp error"));
    }

    SFtpOptFile opt;
    opt.strLocalPath = "";
    opt.strRemotePath = strRemoteFile;
    opt.opt = SFtpOption::OPT_READ_FILE;
    opt.bufferLocal = QSharedPointer<QBuffer>::create(&buffer);

    QEventLoop loop;
    QMetaObject::Connection lambda =
    connect(ftp->pFtp, &CSFtpFileClient::signalFinishedDownloadFile, this, [&loop](QString strLocalFile, QString strRemoteFile,QString strErrMsg){
            qDebug()<<"read file:"<<strLocalFile<<",remotefile:"<<strRemoteFile<<",errmsg:"<<strErrMsg;
            loop.setProperty("errmsg",strErrMsg);
            loop.quit();
    },Qt::ConnectionType::QueuedConnection);
    ftp->pFtp->ssh(opt);
    loop.exec();
    ftp->pFtp->disconnect(lambda);

    closeFtpIf(ftp);

    QString strErr = loop.property("errmsg").toString();
    if (strErr.isEmpty())
    {
        return std::make_tuple(true, DT_NO_ERROR, strErr);
    }
    return std::make_tuple(false, DT_ERR_READ_FILE, strErr);
}

void CDobotDevice::writeProjectFile(const CMessageRequest &msg)
{
    CWriteProjectFileRequestParams request;
    request.fromJson(msg.getParams());

    QString strRemoteFile = QString("/dobot/userdata/project/project/%1/%2")
            .arg(request.m_data.projectName).arg(request.m_data.fileName);
    QByteArray buffer = request.m_data.content.toUtf8();

    std::tuple<bool, int, QString> data;
    for (int i=0; i<3; ++i)
    {
        data = innerWriteFile(request.m_data.ip, request.m_data.port, strRemoteFile, &buffer);
        if (std::get<0>(data)) break;
        else
        {
            QThread::msleep(200);
        }
    }
    CWriteProjectFileResponseResult result;
    if (std::get<0>(data))
    {
        sendResponseSuccess(msg.getMsgUuid(), result);
    }
    else
    {
        sendResponseError(msg.getMsgUuid(), std::get<1>(data), std::get<2>(data));
    }
}

std::tuple<bool, int, QString> CDobotDevice::innerWriteFile(const QString ip, int port, const QString strRemoteFile, QByteArray *buffer)
{
    if (!checkIpAddressValid(ip) || port<=0 || port>=65535)
    {
        return std::make_tuple(false, DT_ERR_INVALID_PARAMS, QString("invalid parameter"));
    }
    auto ftp = connectFtpIf(ip, port);
    if (ftp.isNull())
    {
        return std::make_tuple(false, DT_ERR_NOT_CONNECT, QString("connect sftp error"));
    }

    SFtpOptFile opt;
    opt.strLocalPath = "";
    opt.strRemotePath = strRemoteFile;
    opt.opt = SFtpOption::OPT_WRITE_FILE;
    opt.bufferLocal = QSharedPointer<QBuffer>::create(buffer);

    QEventLoop loop;
    QMetaObject::Connection lambda =
    connect(ftp->pFtp, &CSFtpFileClient::signalFinishedUploadFile, this, [&loop](QString strLocalFile, QString strRemoteFile,QString strErrMsg){
        qDebug()<<"write file:"<<strLocalFile<<",remotefile:"<<strRemoteFile<<",errmsg:"<<strErrMsg;
        loop.setProperty("errmsg",strErrMsg);
        loop.quit();
    },Qt::ConnectionType::QueuedConnection);
    ftp->pFtp->ssh(opt);
    loop.exec();
    ftp->pFtp->disconnect(lambda);

    closeFtpIf(ftp);

    QString strErr = loop.property("errmsg").toString();
    if (strErr.isEmpty())
    {
        return std::make_tuple(true, DT_NO_ERROR, strErr);
    }
    return std::make_tuple(false, DT_ERR_WRITE_FILE, strErr);
}

