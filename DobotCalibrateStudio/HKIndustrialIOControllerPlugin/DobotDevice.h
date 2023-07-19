#ifndef CDOBOTDEVICE_H
#define CDOBOTDEVICE_H

#include <QObject>
#include <QHash>
#include <QJsonObject>
#include <QMutex>
#include <atomic>

#include "JsonMessage.h"

class HKIndustrialIODevice;

class CDobotDevice : public QObject
{
    Q_OBJECT
public:
    explicit CDobotDevice(QObject *parent = nullptr);
    ~CDobotDevice();

    void doCmd(const CMessageRequest &msg);

    bool isDeviceOpen() const;
    void closeNotResponse();

signals:
    void doResponseMsg(QJsonObject obj, QPrivateSignal);

private:
    void initFunctionMapper();
    void emitResponseMsg(const CMessageResponse& msg);
    void sendResponseSuccess(const QString& strMsgUuid, const CJsonMessage& responseData, bool bAutoDeleteCacheId=true);
    void sendResponseError(const QString& strMsgUuid, const int iErrCode, const QString& strErrMsg="", bool bAutoDeleteCacheId=true);
    void deleteAllCacheId();
    void deleteCacheId(const QString& strMsgUuid);

    void open(const CMessageRequest &msg);
    void close(const CMessageRequest &msg);
    void lightTurnOn(const CMessageRequest &msg);
    void lightTurnOff(const CMessageRequest &msg);
    void getLightParam(const CMessageRequest &msg);

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

    std::atomic_bool m_bIsDeviceOpen;
    HKIndustrialIODevice* m_pIODevice;
};

#endif // CDOBOTDEVICE_H
