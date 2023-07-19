#ifndef ICAMERADEVICE_H
#define ICAMERADEVICE_H

#include <QObject>
#include <QList>
#include <QImage>

#include "CameraInfo.h"

class ICameraDevice : public QObject
{
    Q_OBJECT
public:
    explicit ICameraDevice(QObject *parent = nullptr);
    virtual ~ICameraDevice();

    virtual int getErrCode() const{return m_iErrCode;};
    virtual QString getErrMessage() const{return m_strErrMsg;};
    virtual QList<CameraInfo> search() = 0;
    virtual bool setCameraIp(const QString& strConnect,const MyCameraIpInfo& info) = 0;
    virtual bool openCamera(const QString& strConnect) = 0;
    virtual void closeCamera() = 0;
    virtual bool isConnected() = 0;
    virtual bool startVideo() = 0;
    virtual void stopVideo() = 0;
    virtual QImage takePhoto() = 0;
    virtual QList<MyPointF6D> getCalibratePos(const MyPointF3D& flangleCenter, const MyPointF6D& robotPos) = 0;
    virtual bool calcGetCalibrateResult(MyPointF6D& avgValue, MyPointF6D& maxValue) = 0;
    virtual bool generateCalibrateFile(const QString& strSaveFileFullName) = 0;
    virtual bool createUserCoordinate(const QString& strCalibrateFile, const MyPointF6D& robotPos,
                                      MyPointF6D& coordinatePos, int& iId, QImage& retImg) = 0;
    virtual bool beginCalibrate() = 0;
    virtual int endCalibrate() = 0; //返回标定点个数
    virtual bool calibrateSampling(const MyPointF6D& robotPos, QImage& retImg) = 0;
    virtual bool updateCalibrateSampling(const MyPointF6D& robotPos, int idxUpdate, QImage& retImg) = 0;

    virtual bool getCameraParam(const QJsonObject& property, QJsonObject& result) = 0;
    virtual bool setCameraParam(const QJsonObject& property, QJsonObject& result) = 0;
signals:

protected:
    int m_iErrCode;
    QString m_strErrMsg;
};

#endif // CAMERADEVICE_H
