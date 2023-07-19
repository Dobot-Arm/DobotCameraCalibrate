#ifndef DELETEMODULEBEAN_H
#define DELETEMODULEBEAN_H

#include "JsonMessage.h"

struct CDeleteModuleRequestBean : public CJsonMessage
{
    virtual ~CDeleteModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    int moduleId; //模块id值
};

class CDeleteModuleRequestParams : public CJsonMessage
{
public:
    CDeleteModuleRequestParams(){};
    virtual ~CDeleteModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CDeleteModuleRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CDeleteModuleResponseBean : public CJsonMessage
{
    virtual ~CDeleteModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CDeleteModuleResponseResult : public CJsonMessage
{
public:
    CDeleteModuleResponseResult(){};
    virtual ~CDeleteModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // DELETEMODULEBEAN_H
