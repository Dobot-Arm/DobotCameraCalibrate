#ifndef ALLSUPPORTMODULEBEAN_H
#define ALLSUPPORTMODULEBEAN_H

#include "JsonMessage.h"

struct CAllSupportModuleRequestBean : public CJsonMessage
{
    virtual ~CAllSupportModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
};

class CAllSupportModuleRequestParams : public CJsonMessage
{
public:
    CAllSupportModuleRequestParams(){};
    virtual ~CAllSupportModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CAllSupportModuleRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CAllSupportModuleResponseBean : public CJsonMessage
{
    virtual ~CAllSupportModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    QString displayNameCN;
    QString displayNameEN;
    int algoModuleMax;
};

class CAllSupportModuleResponseResult : public CJsonMessage
{
public:
    CAllSupportModuleResponseResult(){};
    virtual ~CAllSupportModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CAllSupportModuleResponseBean> m_data;
};

#endif // ALLSUPPORTMODULEBEAN_H
