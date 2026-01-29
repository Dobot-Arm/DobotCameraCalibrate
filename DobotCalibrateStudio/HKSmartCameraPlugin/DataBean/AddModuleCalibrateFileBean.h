#ifndef ADDMODULECALIBRATEFILEBEAN_H
#define ADDMODULECALIBRATEFILEBEAN_H

#include "JsonMessage.h"

struct CAddModuleCalibrateFileRequestBean : public CJsonMessage
{
    virtual ~CAddModuleCalibrateFileRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString fileName;
    QString fileFullPath;
};

class CAddModuleCalibrateFileRequestParams : public CJsonMessage
{
public:
    CAddModuleCalibrateFileRequestParams(){};
    virtual ~CAddModuleCalibrateFileRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAddModuleCalibrateFileRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAddModuleCalibrateFileResponseBean : public CJsonMessage
{
    virtual ~CAddModuleCalibrateFileResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CAddModuleCalibrateFileResponseResult : public CJsonMessage
{
public:
    CAddModuleCalibrateFileResponseResult(){};
    virtual ~CAddModuleCalibrateFileResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // ADDMODULECALIBRATEFILEBEAN_H
