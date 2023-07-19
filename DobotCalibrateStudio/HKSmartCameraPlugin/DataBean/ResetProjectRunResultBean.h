#ifndef RESETPROJECTRUNRESULTBEAN_H
#define RESETPROJECTRUNRESULTBEAN_H

#include "JsonMessage.h"

struct CResetProjectRunResultRequestBean : public CJsonMessage
{
    virtual ~CResetProjectRunResultRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CResetProjectRunResultRequestParams : public CJsonMessage
{
public:
    CResetProjectRunResultRequestParams(){};
    virtual ~CResetProjectRunResultRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CResetProjectRunResultRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CResetProjectRunResultResponseBean : public CJsonMessage
{
    virtual ~CResetProjectRunResultResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CResetProjectRunResultResponseResult : public CJsonMessage
{
public:
    CResetProjectRunResultResponseResult(){};
    virtual ~CResetProjectRunResultResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // RESETPROJECTRUNRESULTBEAN_H
