#ifndef CDOBOTDEVICE_H
#define CDOBOTDEVICE_H

#include <QObject>
#include <QHash>
#include <QJsonObject>
#include <QMutex>

#include "JsonMessage.h"

class ICameraDevice;

class CDobotDevice : public QObject
{
    Q_OBJECT
public:
    explicit CDobotDevice(QObject *parent = nullptr);
    ~CDobotDevice();

    void doCmd(const CMessageRequest &msg);

    void closeNotResponse();

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

    QByteArray image2Base64Byte(const QImage& img, const char *format = "jpg", int quality = -1);
    QString fixSavePath(const QString& strPath);
    QString getMyCachePath() const;
    QString getLastTempCalibrateFile() const;
    void updateLastTempCalibrateFile(const QString& strSrcFile) const;

    /***********************************************************************************/
    void search(const CMessageRequest &msg);
    void setIpConfig(const CMessageRequest &msg);
    void open(const CMessageRequest &msg);
    void close(const CMessageRequest &msg);
    void startVideo(const CMessageRequest &msg);
    void stopVideo(const CMessageRequest &msg);
    void takePhoto(const CMessageRequest &msg);
    void getCalibratePos(const CMessageRequest &msg);
    void calcGetCalibrateResult(const CMessageRequest &msg);
    void generateCalibrateFile(const CMessageRequest &msg);
    void generateCalibrateFileV2(const CMessageRequest &msg);
    void createUserCoordinate(const CMessageRequest &msg);
    void createUserCoordinateV2(const CMessageRequest &msg);
    void beginCalibrate(const CMessageRequest &msg);
    void endCalibrate(const CMessageRequest &msg);
    void calibrateSampling(const CMessageRequest &msg);
    void updateCalibrateSampling(const CMessageRequest &msg);
    void getCameraParam(const CMessageRequest &msg);
    void setCameraParam(const CMessageRequest &msg);

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

    /*拍视频时，因为msguuid并没有删除，否则下一次无法主动推送给别人，所以当停止时，则需要删掉缓存，否则遗留了。*/
    QString m_strVideoLastMsgUuid;

    ICameraDevice* m_pCameraDevice;
};

#endif // CDOBOTDEVICE_H
