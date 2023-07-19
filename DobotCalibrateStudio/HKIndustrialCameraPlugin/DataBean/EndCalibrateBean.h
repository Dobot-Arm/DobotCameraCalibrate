#ifndef CENDCALIBRATEBEAN_H
#define CENDCALIBRATEBEAN_H

#include "JsonMessage.h"

struct CEndCalibrateRequestBean : public CJsonMessage
{
    virtual ~CEndCalibrateRequestBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    QString identify; //相机标识，在连接打开相机时用到这个参数
};

class CEndCalibrateRequestParams : public CJsonMessage
{
public:
    CEndCalibrateRequestParams(){};
    virtual ~CEndCalibrateRequestParams() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CEndCalibrateRequestBean m_data;
};

/*********************************************************************************************************/
/*********************************************************************************************************/
struct CEndCalibrateResponseBean : public CJsonMessage
{
    virtual ~CEndCalibrateResponseBean(){}
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

    int pointCount;
};

class CEndCalibrateResponseResult : public CJsonMessage
{
public:
    CEndCalibrateResponseResult(){};
    virtual ~CEndCalibrateResponseResult() {};
    bool fromJson(const QJsonObject& obj) Q_DECL_OVERRIDE;
    QJsonObject toJsonObject()const Q_DECL_OVERRIDE;

public:
    CEndCalibrateResponseBean m_data;
};

#endif // CENDCALIBRATEBEAN_H
