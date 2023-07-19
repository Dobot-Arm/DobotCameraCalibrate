#ifndef GETMODULESHOWNAMEBEAN_H
#define GETMODULESHOWNAMEBEAN_H

#include "JsonMessage.h"

struct CGetModuleShowNameRequestBean : public CJsonMessage
{
    virtual ~CGetModuleShowNameRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
};

class CGetModuleShowNameRequestParams : public CJsonMessage
{
public:
    CGetModuleShowNameRequestParams(){};
    virtual ~CGetModuleShowNameRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetModuleShowNameRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CGetModuleShowNameResponseBean : public CJsonMessage
{
    virtual ~CGetModuleShowNameResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString showName;
};

class CGetModuleShowNameResponseResult : public CJsonMessage
{
public:
    CGetModuleShowNameResponseResult(){};
    virtual ~CGetModuleShowNameResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CGetModuleShowNameResponseBean m_data;
};

#endif // GETMODULESHOWNAMEBEAN_H
