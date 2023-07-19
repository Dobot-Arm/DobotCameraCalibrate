#ifndef CCALIBRATESAMPLING_H
#define CCALIBRATESAMPLING_H

#include "JsonMessage.h"

struct CCalibrateSamplingRequestBean : public CJsonMessage
{
    virtual ~CCalibrateSamplingRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString savePath; //图片保存的目录，比如E:\test\img\，最后面有斜杠
    bool returnFrame = false; //是否返回图像帧数据
    int index = -1;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double rx = 0.0;
    double ry = 0.0;
    double rz = 0.0;
};

class CCalibrateSamplingRequestParams : public CJsonMessage
{
public:
    CCalibrateSamplingRequestParams(){};
    virtual ~CCalibrateSamplingRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCalibrateSamplingRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCalibrateSamplingResultResponseBean : public CJsonMessage
{
    virtual ~CCalibrateSamplingResultResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString frame; //图片数据流帧，base64编码
    QString fileName; //生成的图片名称，比如 a.bmp
};

class CCalibrateSamplingResultResponseResult : public CJsonMessage
{
public:
    CCalibrateSamplingResultResponseResult(){};
    virtual ~CCalibrateSamplingResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCalibrateSamplingResultResponseBean m_data;
};
#endif // CCALIBRATESAMPLING_H
