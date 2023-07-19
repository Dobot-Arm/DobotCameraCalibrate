#ifndef COPYMODULEBEAN_H
#define COPYMODULEBEAN_H

#include "JsonMessage.h"

struct CCopyModuleRequestBean : public CJsonMessage
{
    virtual ~CCopyModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    int moduleId; //模块id值
};

class CCopyModuleRequestParams : public CJsonMessage
{
public:
    CCopyModuleRequestParams(){};
    virtual ~CCopyModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CCopyModuleRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CCopyModuleResponseBean : public CJsonMessage
{
    virtual ~CCopyModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CCopyModuleResponseResult : public CJsonMessage
{
public:
    CCopyModuleResponseResult(){};
    virtual ~CCopyModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // COPYMODULEBEAN_H
