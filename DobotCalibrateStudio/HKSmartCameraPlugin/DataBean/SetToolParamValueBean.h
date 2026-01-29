#ifndef SETTOOLPARAMVALUEBEAN_H
#define SETTOOLPARAMVALUEBEAN_H

#include "JsonMessage.h"

struct CSetToolParamValueRequestBean : public CJsonMessage
{
    virtual ~CSetToolParamValueRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int moduleId; //模块id值
    QString paramName;
};

struct CSetToolParamValueRequestBean1 : public CJsonMessage
{
    virtual ~CSetToolParamValueRequestBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString paramName;
    int subModuleStyle;
    CSetToolParamValueRequestBean parameter;
};

class CSetToolParamValueRequestParams : public CJsonMessage
{
public:
    CSetToolParamValueRequestParams(){};
    virtual ~CSetToolParamValueRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetToolParamValueRequestBean1 m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetToolParamValueResponseBean : public CJsonMessage
{
    virtual ~CSetToolParamValueResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetToolParamValueResponseResult : public CJsonMessage
{
public:
    CSetToolParamValueResponseResult(){};
    virtual ~CSetToolParamValueResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETTOOLPARAMVALUEBEAN_H
