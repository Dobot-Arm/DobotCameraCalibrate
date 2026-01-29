#ifndef SWITCHMODULECALIBRATEFILEBEAN_H
#define SWITCHMODULECALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CSwitchModuleCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CSwitchModuleCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString paramName;
};

class CSwitchModuleCalibrateFileRequestParams : public CJsonMessage
{
public:
    CSwitchModuleCalibrateFileRequestParams(){};
    virtual ~CSwitchModuleCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSwitchModuleCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSwitchModuleCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CSwitchModuleCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSwitchModuleCalibrateFileResponseResult : public CJsonMessage
{
public:
    CSwitchModuleCalibrateFileResponseResult(){};
    virtual ~CSwitchModuleCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SWITCHMODULECALIBRATEFILEBEAN_H
