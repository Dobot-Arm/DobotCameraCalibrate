#ifndef SETMODULESHOWNAMEBEAN_H
#define SETMODULESHOWNAMEBEAN_H

#include "JsonMessage.h"

struct CSetModuleShowNameRequestBean : public CJsonMessage
{
    virtual ~CSetModuleShowNameRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString moduleName; //模块名称
    int moduleId; //模块id值
    QString showName;//显示的名称
};

class CSetModuleShowNameRequestParams : public CJsonMessage
{
public:
    CSetModuleShowNameRequestParams(){};
    virtual ~CSetModuleShowNameRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetModuleShowNameRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetModuleShowNameResponseBean : public CJsonMessage
{
    virtual ~CSetModuleShowNameResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetModuleShowNameResponseResult : public CJsonMessage
{
public:
    CSetModuleShowNameResponseResult(){};
    virtual ~CSetModuleShowNameResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // SETMODULESHOWNAMEBEAN_H
