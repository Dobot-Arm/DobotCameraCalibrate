#ifndef GETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICSUPPORTLISTBEAN_H
#define GETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICSUPPORTLISTBEAN_H

#include "JsonMessage.h"

struct CGetOutputConfigProjectResultCustomLogicSupportListRequestBean : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCustomLogicSupportListRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetOutputConfigProjectResultCustomLogicSupportListRequestParams : public CJsonMessage
{
public:
    CGetOutputConfigProjectResultCustomLogicSupportListRequestParams(){};
    virtual ~CGetOutputConfigProjectResultCustomLogicSupportListRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetOutputConfigProjectResultCustomLogicSupportListRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetOutputConfigProjectResultCustomLogicSupportListResponseBean : public CJsonMessage
{
    virtual ~CGetOutputConfigProjectResultCustomLogicSupportListResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString paramValue;
    QString showValueCN;
    QString showValueEN;
};

class CGetOutputConfigProjectResultCustomLogicSupportListResponseResult : public CJsonMessage
{
public:
    CGetOutputConfigProjectResultCustomLogicSupportListResponseResult(){};
    virtual ~CGetOutputConfigProjectResultCustomLogicSupportListResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CGetOutputConfigProjectResultCustomLogicSupportListResponseBean> m_data;
};

#endif // GETOUTPUTCONFIGPROJECTRESULTCUSTOMLOGICSUPPORTLISTBEAN_H
