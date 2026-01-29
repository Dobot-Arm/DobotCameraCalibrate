#ifndef DELETEMODULECALIBRATEFILEBEAN_H
#define DELETEMODULECALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CDeleteModuleCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CDeleteModuleCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString paramName;
};

class CDeleteModuleCalibrateFileRequestParams : public CJsonMessage
{
public:
    CDeleteModuleCalibrateFileRequestParams(){};
    virtual ~CDeleteModuleCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CDeleteModuleCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CDeleteModuleCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CDeleteModuleCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CDeleteModuleCalibrateFileResponseResult : public CJsonMessage
{
public:
    CDeleteModuleCalibrateFileResponseResult(){};
    virtual ~CDeleteModuleCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // DELETEMODULECALIBRATEFILEBEAN_H
