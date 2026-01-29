#ifndef CDOBOTDEVICE_H
#define CDOBOTDEVICE_H

#include <QObject>

#include "JsonMessage.h"
#include "DataBeanHeaderConfig.h"
#include <SFtpFileClient.h>
#include <tuple>

struct SafeFtp;
class CDobotDevice : public QObject
{
    Q_OBJECT
public:
    explicit CDobotDevice(QObject *parent = nullptr);
    ~CDobotDevice();
    static QByteArray image2Base64Byte(const QImage& img, const char *format = "jpg", int quality = -1);

    void doCmd(const CMessageRequest &msg);

signals:
    void doResponseMsg(QJsonObject obj, QPrivateSignal);

private:
    void initFunctionMapper();
    void emitResponseMsg(const CMessageResponse& msg);
    void sendResponseSuccess(const QString& strMsgUuid, const CJsonMessage& responseData, bool bAutoDeleteCacheId=true);
    void sendResponseError(const QString& strMsgUuid, const int iErrCode, const QString& strErrMsg="", bool bAutoDeleteCacheId=true);
    void sendResponseError(const QString& strMsgUuid, const CJsonMessage& responseData, const int iErrCode, const QString& strErrMsg="", bool bAutoDeleteCacheId=true);
    void deleteAllCacheId();
    void deleteCacheId(const QString& strMsgUuid);
    bool checkIpAddressValid(const QString& strIp);

    QString fixSavePath(const QString& strPath);
    QSharedPointer<SafeFtp> connectFtpIf(const QString strIp, int port);
    void closeFtpIf(QSharedPointer<SafeFtp> sptr);

    /************************************************************************/
    void getInfoList(const CMessageRequest &msg);
    std::tuple<bool, int, QString> innerGetInfoList(const QString ip, int port, const QString strRemoteDir, QList<QSsh::SftpFileInfo>& retData);
    void downloadFile(const CMessageRequest &msg);
    std::tuple<bool, int, QString> inneDownloadFile(const QString ip, int port, const QString strLocalFile, const QString strRemoteFile);
    void uploadFile(const CMessageRequest &msg);
    std::tuple<bool, int, QString> innerUploadFile(const QString ip, int port, const QString strLocalFile, const QString strRemoteFile);

    void getAllProject(const CMessageRequest &msg);
    void getProjectFiles(const CMessageRequest &msg);
    void readProjectFile(const CMessageRequest &msg);
    std::tuple<bool, int, QString> innerReadFile(const QString ip, int port, const QString strRemoteFile, QByteArray& buffer);
    void writeProjectFile(const CMessageRequest &msg);
    std::tuple<bool, int, QString> innerWriteFile(const QString ip, int port, const QString strRemoteFile, QByteArray* buffer);
private:
    typedef void (CDobotDevice::*pfnCmdCallback)(const CMessageRequest &msg);
    QHash<QString,      //method name
        pfnCmdCallback  //callback
    > m_mapperFunction;

    //msg request cache
    QHash<QString, //msg uuid
        RequestJsonRpc
    > m_requestCacheId;
    QMutex m_mtxRequestCacheId;
};

#endif // CDOBOTDEVICE_H
