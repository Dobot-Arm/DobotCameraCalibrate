#ifndef SETMODULEUIPARAMETERBEAN_H
#define SETMODULEUIPARAMETERBEAN_H

#include "JsonMessage.h"

struct CSetModuleUIParameterRequestBean : public CJsonMessage
{
    virtual ~CSetModuleUIParameterRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    QString paramType;
    QJsonValue paramValue;
};

struct CSetModuleUIParameterRequestBean2 : public CJsonMessage
{
    virtual ~CSetModuleUIParameterRequestBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QHash<QString, CSetModuleUIParameterRequestBean> parameter;
};

class CSetModuleUIParameterRequestParams : public CJsonMessage
{
public:
    CSetModuleUIParameterRequestParams(){};
    virtual ~CSetModuleUIParameterRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetModuleUIParameterRequestBean2 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetModuleUIParameterResponseBean : public CJsonMessage
{
    virtual ~CSetModuleUIParameterResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    bool success = true;
    QString errmsg;
};

class CSetModuleUIParameterResponseResult : public CJsonMessage
{
public:
    CSetModuleUIParameterResponseResult(){};
    virtual ~CSetModuleUIParameterResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CSetModuleUIParameterResponseBean> m_data;
};

#endif // SETMODULEUIPARAMETERBEAN_H
