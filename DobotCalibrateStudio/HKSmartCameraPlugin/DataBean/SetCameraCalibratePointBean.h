#ifndef SETCAMERACALIBRATEPOINTBEAN_H
#define SETCAMERACALIBRATEPOINTBEAN_H

#include "JsonMessage.h"

struct CSetCameraCalibratePointRequestBean : public CJsonMessage
{
    virtual ~CSetCameraCalibratePointRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    double imageX = 0.0;
    double imageY = 0.0;
    double physicalX = 0.0;
    double physicalY = 0.0;
    double angle = 0.0;
};

struct CSetCameraCalibratePointRequestBean2 : public CJsonMessage
{
    virtual ~CSetCameraCalibratePointRequestBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QList<CSetCameraCalibratePointRequestBean> transformPoints;
    QList<CSetCameraCalibratePointRequestBean> rotaPoints;
};

class CSetCameraCalibratePointRequestParams : public CJsonMessage
{
public:
    CSetCameraCalibratePointRequestParams(){};
    virtual ~CSetCameraCalibratePointRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetCameraCalibratePointRequestBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetCameraCalibratePointResponseBean : public CJsonMessage
{
    virtual ~CSetCameraCalibratePointResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetCameraCalibratePointResponseResult : public CJsonMessage
{
public:
    CSetCameraCalibratePointResponseResult(){};
    virtual ~CSetCameraCalibratePointResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETCAMERACALIBRATEPOINTBEAN_H
