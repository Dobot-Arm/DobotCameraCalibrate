#ifndef PROJECTMODULEBEAN_H
#define PROJECTMODULEBEAN_H

#include "JsonMessage.h"

struct CProjectModuleRequestBean : public CJsonMessage
{
    virtual ~CProjectModuleRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    bool isSaveDbgFile = false;//调试用的
};

class CProjectModuleRequestParams : public CJsonMessage
{
public:
    CProjectModuleRequestParams(){};
    virtual ~CProjectModuleRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CProjectModuleRequestBean m_data;
};


/*********************************************************************************************************/
/*********************************************************************************************************/
struct CProjectModuleResponseBean : public CJsonMessage
{
    virtual ~CProjectModuleResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString moduleName;
    int moduleId;
    QString showName;
};

class CProjectModuleResponseResult : public CJsonMessage
{
public:
    CProjectModuleResponseResult(){};
    virtual ~CProjectModuleResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    QList<CProjectModuleResponseBean> m_data;
};

#endif // PROJECTMODULEBEAN_H
