#ifndef SWITCH25DCALIBRATEFILEBEAN_H
#define SWITCH25DCALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CSwitch25DCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CSwitch25DCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
};

class CSwitch25DCalibrateFileRequestParams : public CJsonMessage
{
public:
    CSwitch25DCalibrateFileRequestParams(){};
    virtual ~CSwitch25DCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSwitch25DCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSwitch25DCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CSwitch25DCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSwitch25DCalibrateFileResponseResult : public CJsonMessage
{
public:
    CSwitch25DCalibrateFileResponseResult(){};
    virtual ~CSwitch25DCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SWITCH25DCALIBRATEFILEBEAN_H
