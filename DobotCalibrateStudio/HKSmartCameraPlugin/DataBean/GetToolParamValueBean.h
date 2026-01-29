#ifndef GETTOOLPARAMVALUEBEAN_H
#define GETTOOLPARAMVALUEBEAN_H

#include "JsonMessage.h"

struct CGetToolParamValueRequestBean : public CJsonMessage
{
    virtual ~CGetToolParamValueRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString paramName;
    int subModuleStyle;
};

class CGetToolParamValueRequestParams : public CJsonMessage
{
public:
    CGetToolParamValueRequestParams(){};
    virtual ~CGetToolParamValueRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetToolParamValueRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetToolParamValueResponseBean1 : public CJsonMessage
{
    virtual ~CGetToolParamValueResponseBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString displayNameCN;
    QString displayNameEN;
    QString paramName;
    QString paramNameCN;
    QString paramNameEN;
};

class CGetToolParamValueResponseResult : public CJsonMessage
{
public:
    CGetToolParamValueResponseResult(){};
    virtual ~CGetToolParamValueResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetToolParamValueResponseBean1 m_data;
};
#endif // GETTOOLPARAMVALUEBEAN_H
