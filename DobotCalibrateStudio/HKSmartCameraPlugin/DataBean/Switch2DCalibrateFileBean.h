#ifndef SWITCH2DCALIBRATEFILEBEAN_H
#define SWITCH2DCALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CSwitch2DCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CSwitch2DCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
};

class CSwitch2DCalibrateFileRequestParams : public CJsonMessage
{
public:
    CSwitch2DCalibrateFileRequestParams(){};
    virtual ~CSwitch2DCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSwitch2DCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSwitch2DCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CSwitch2DCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSwitch2DCalibrateFileResponseResult : public CJsonMessage
{
public:
    CSwitch2DCalibrateFileResponseResult(){};
    virtual ~CSwitch2DCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SWITCH2DCALIBRATEFILEBEAN_H
