#ifndef GETTOOLSUPPORTPARAMLISTBEAN_H
#define GETTOOLSUPPORTPARAMLISTBEAN_H

#include "JsonMessage.h"

struct CGetToolSupportParamListRequestBean : public CJsonMessage
{
    virtual ~CGetToolSupportParamListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString filterSubType;
    int subModuleStyle;
};

class CGetToolSupportParamListRequestParams : public CJsonMessage
{
public:
    CGetToolSupportParamListRequestParams(){};
    virtual ~CGetToolSupportParamListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetToolSupportParamListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetToolSupportParamListResponseBean1 : public CJsonMessage
{
    virtual ~CGetToolSupportParamListResponseBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    QString paramNameCN;
    QString paramNameEN;
};

struct CGetToolSupportParamListResponseBean2 : public CJsonMessage
{
    virtual ~CGetToolSupportParamListResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString displayNameCN;
    QString displayNameEN;
    QList<CGetToolSupportParamListResponseBean1> subParamList;
};

class CGetToolSupportParamListResponseResult : public CJsonMessage
{
public:
    CGetToolSupportParamListResponseResult(){};
    virtual ~CGetToolSupportParamListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetToolSupportParamListResponseBean2> m_data;
};
#endif // GETTOOLSUPPORTPARAMLISTBEAN_H
