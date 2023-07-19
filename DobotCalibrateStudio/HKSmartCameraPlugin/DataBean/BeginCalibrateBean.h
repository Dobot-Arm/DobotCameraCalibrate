#ifndef CBEGINCALIBRATEBEAN_H
#define CBEGINCALIBRATEBEAN_H

#include "JsonMessage.h"

struct CBeginCalibrateRequestBean : public CJsonMessage
{
    virtual ~CBeginCalibrateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CBeginCalibrateRequestParams : public CJsonMessage
{
public:
    CBeginCalibrateRequestParams(){};
    virtual ~CBeginCalibrateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CBeginCalibrateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CBeginCalibrateResponseBean : public CJsonMessage
{
    virtual ~CBeginCalibrateResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

class CBeginCalibrateResponseResult : public CJsonMessage
{
public:
    CBeginCalibrateResponseResult(){};
    virtual ~CBeginCalibrateResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;
};

#endif // CBEGINCALIBRATEBEAN_H
