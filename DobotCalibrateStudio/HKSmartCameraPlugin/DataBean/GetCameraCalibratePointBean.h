#ifndef GETCAMERACALIBRATEPOINTBEAN_H
#define GETCAMERACALIBRATEPOINTBEAN_H

#include "JsonMessage.h"

struct CGetCameraCalibratePointRequestBean : public CJsonMessage
{
    virtual ~CGetCameraCalibratePointRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetCameraCalibratePointRequestParams : public CJsonMessage
{
public:
    CGetCameraCalibratePointRequestParams(){};
    virtual ~CGetCameraCalibratePointRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCameraCalibratePointRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetCameraCalibratePointResponseBean : public CJsonMessage
{
    virtual ~CGetCameraCalibratePointResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double imageX = 0.0;
    double imageY = 0.0;
    double physicalX = 0.0;
    double physicalY = 0.0;
    double angle = 0.0;
};

struct CGetCameraCalibratePointResponseBean2 : public CJsonMessage
{
    virtual ~CGetCameraCalibratePointResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QList<CGetCameraCalibratePointResponseBean> transformPoints;
    QList<CGetCameraCalibratePointResponseBean> rotaPoints;
};

class CGetCameraCalibratePointResponseResult : public CJsonMessage
{
public:
    CGetCameraCalibratePointResponseResult(){};
    virtual ~CGetCameraCalibratePointResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetCameraCalibratePointResponseBean2 m_data;
};

#endif // GETCAMERACALIBRATEPOINTBEAN_H
