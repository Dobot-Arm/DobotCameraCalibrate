#ifndef SETIPCONFIGBEAN_H
#define SETIPCONFIGBEAN_H

#include "JsonMessage.h"

struct CSetIpConfigRequestBean : public CJsonMessage
{
    virtual ~CSetIpConfigRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
    QString ip;
    QString subnetmask;
    QString gateway;
};

class CSetIpConfigRequestParams : public CJsonMessage
{
public:
    CSetIpConfigRequestParams(){};
    virtual ~CSetIpConfigRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CSetIpConfigRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CSetIpConfigResponseBean : public CJsonMessage
{
    virtual ~CSetIpConfigResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CSetIpConfigResponseResult : public CJsonMessage
{
public:
    CSetIpConfigResponseResult(){};
    virtual ~CSetIpConfigResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};


#endif // SETIPCONFIGBEAN_H
