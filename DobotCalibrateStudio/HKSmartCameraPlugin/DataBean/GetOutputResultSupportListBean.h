#ifndef GETOUTPUTRESULTSUPPORTLISTBEAN_H
#define GETOUTPUTRESULTSUPPORTLISTBEAN_H

#include "JsonMessage.h"

struct CGetOutputResultSupportListRequestBean : public CJsonMessage
{
    virtual ~CGetOutputResultSupportListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString filterSubType;
};

class CGetOutputResultSupportListRequestParams : public CJsonMessage
{
public:
    CGetOutputResultSupportListRequestParams(){};
    virtual ~CGetOutputResultSupportListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputResultSupportListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetOutputResultSupportListResponseBean1 : public CJsonMessage
{
    virtual ~CGetOutputResultSupportListResponseBean1(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramName;
    QString paramType;
    QString paramNameCN;
    QString paramNameEN;
};

struct CGetOutputResultSupportListResponseBean2 : public CJsonMessage
{
    virtual ~CGetOutputResultSupportListResponseBean2(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString displayNameCN;
    QString displayNameEN;
    QList<CGetOutputResultSupportListResponseBean1> subParamList;
};

class CGetOutputResultSupportListResponseResult : public CJsonMessage
{
public:
    CGetOutputResultSupportListResponseResult(){};
    virtual ~CGetOutputResultSupportListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetOutputResultSupportListResponseBean2> m_data;
};

#endif // GETOUTPUTRESULTSUPPORTLISTBEAN_H
